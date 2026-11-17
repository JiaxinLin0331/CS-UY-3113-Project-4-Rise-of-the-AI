/**

* Author: Jiaxin Lin

* Assignment: Rise of the AI

* Date due: 11/16/2026

* I pledge that I have completed this assignment without

* collaborating with anyone else, in conformance with the

* NYU School of Engineering Policies and Procedures on

* Academic Misconduct.

**/

#include "Scene.h"

void Scene::addPlatform(
    Vector2 position,
    Vector2 scale,
    const char *filepath
)
{
    Entity *platform = new Entity(
        position,
        scale,
        PLATFORM,
        WHITE,
        filepath
    );

    mPlatforms.push_back(platform);
}

void Scene::addEnemy(
    Vector2 position,
    EntityType type,
    float patrolDistance
)
{
    Entity *enemy = nullptr;

    if (type == PATROL)
    {
        enemy = new Entity(
            position, { 80.0f, 80.0f }, PATROL
        );

        enemy->setAIType(WANDERER);
        enemy->setSpeed(90);
        enemy->setColliderDimensions({ 40.0f, 46.0f });
    }
    else if (type == HUNTER)
    {
        enemy = new Entity(
            position, { 80.0f, 80.0f }, HUNTER
        );

        enemy->setAIType(FOLLOWER);
        enemy->setSpeed(145);
        enemy->setColliderDimensions({ 36.0f, 66.0f });
    }
    else if (type == DRONE)
    {
        enemy = new Entity(
            position, { 90.0f, 90.0f }, DRONE
        );

        enemy->setAIType(FLYER);
        enemy->setSpeed(110);
        enemy->setColliderDimensions({ 55.0f, 45.0f });
    }

    if (enemy)
    {
        enemy->setPatrolDistance(patrolDistance);
        enemy->moveRight();

        mEnemies.push_back(enemy);
    }
}

Scene::~Scene()
{
    shutdown();
}

void Scene::initialiseLevel(int levelNumber, float mapWidth, const char *backgroundPath)
{
    mState = {};
    mLevelNumber = levelNumber;

    if (FileExists(backgroundPath))
        mBackground = LoadTexture(backgroundPath);

    mMap = new Map(mapWidth);

    // Player
    mPlayer = new Entity(
        { 100.0f, 482.0f },
        { 80.0f, 80.0f },
        PLAYER
    );

    mPlayer->setColliderDimensions({ 35.0f, 60.0f });
    mPlayer->setJumpingPower(560.0f);
    mPlayer->setGrounded(true);

    mCamera.target   = ORIGIN;
    mCamera.offset   = ORIGIN;
    mCamera.rotation = 0.0f;
    mCamera.zoom     = 1.0f;
}

void Scene::processInput()
{
    if (!mPlayer) return;

    mPlayer->resetMovement();

    if      (IsKeyDown(KEY_A)) mPlayer->moveLeft();
    else if (IsKeyDown(KEY_D)) mPlayer->moveRight();

    if (IsKeyPressed(KEY_SPACE) && mPlayer->isGrounded())
    {
        mPlayer->jump();
        PlaySound(gJumpSound);
    }
}

void Scene::update(float deltaTime)
{
    if (!mPlayer || !mMap) return;

    Vector2 previousPosition = mPlayer->getPosition();

    mPlayer->update(deltaTime, nullptr);

    Vector2 position   = mPlayer->getPosition();
    Vector2 velocity   = mPlayer->getVelocity();
    Vector2 dimensions = mPlayer->getColliderDimensions();

    float halfWidth  = dimensions.x / 2.0f;
    float halfHeight = dimensions.y / 2.0f;

    std::vector<Rectangle> colliders = mMap->getGround();

    // Platform colliders
    for (Entity *platform : mPlatforms)
    {
        if (platform->getEntityType() == SPIKES ||
            platform->getEntityType() == JUMP_PAD)
            continue;

        Vector2 p = platform->getPosition();
        Vector2 s = platform->getColliderDimensions();

        colliders.push_back({
            p.x - s.x / 2.0f,
            p.y - s.y / 2.0f,
            s.x,
            s.y
        });
    }

    mPlayer->setGrounded(false);

    // Horizontal collision
    float horizontalVelocity = velocity.x;

    for (Rectangle collider : colliders)
    {
        bool verticalOverlap =
            previousPosition.y + halfHeight > collider.y &&
            previousPosition.y - halfHeight <
                collider.y + collider.height;

        if (!verticalOverlap) continue;

        if (horizontalVelocity > 0.0f &&
            previousPosition.x + halfWidth <= collider.x &&
            position.x + halfWidth >= collider.x)
        {
            position.x = collider.x - halfWidth;
            velocity.x = 0.0f;
        }
        else if (horizontalVelocity < 0.0f &&
                 previousPosition.x - halfWidth >=
                     collider.x + collider.width &&
                 position.x - halfWidth <=
                     collider.x + collider.width)
        {
            position.x = collider.x +
                         collider.width + halfWidth;

            velocity.x = 0.0f;
        }
    }

    // Vertical collision
    float landingY = 100000.0f;
    float ceilingY = -100000.0f;

    for (Rectangle collider : colliders)
    {
        bool horizontalOverlap =
            position.x + halfWidth > collider.x &&
            position.x - halfWidth <
                collider.x + collider.width;

        if (!horizontalOverlap) continue;

        if (velocity.y >= 0.0f &&
            previousPosition.y + halfHeight <= collider.y + 0.01f &&
            position.y + halfHeight >= collider.y)
        {
            landingY = fminf(landingY, collider.y);
        }
        else if (velocity.y < 0.0f &&
                 previousPosition.y - halfHeight >=
                     collider.y + collider.height - 0.01f &&
                 position.y - halfHeight <=
                     collider.y + collider.height)
        {
            ceilingY = fmaxf(
                ceilingY,
                collider.y + collider.height
            );
        }
    }

    // Jump pad collision
    bool bounce = false;

    for (Entity *platform : mPlatforms)
    {
        if (platform->getEntityType() != JUMP_PAD)
            continue;

        Vector2 p = platform->getPosition();
        Vector2 s = platform->getColliderDimensions();

        float platformTop = p.y - s.y / 2.0f;

        bool horizontalOverlap =
            position.x + halfWidth > p.x - s.x / 2.0f &&
            position.x - halfWidth < p.x + s.x / 2.0f;

        if (horizontalOverlap &&
            velocity.y >= 0.0f &&
            previousPosition.y + halfHeight <= platformTop &&
            position.y + halfHeight >= platformTop &&
            platformTop < landingY)
        {
            landingY = platformTop;
            bounce = true;
        }
    }

    if (landingY < 100000.0f)
    {
        position.y = landingY - halfHeight;

        if (bounce)
        {
            velocity.y = -700.0f;
            PlaySound(gJumpSound);
        }
        else
        {
            velocity.y = 0.0f;
            mPlayer->setGrounded(true);
        }
    }

    if (ceilingY > -100000.0f)
    {
        position.y = ceilingY + halfHeight;
        velocity.y = 0.0f;
    }

    // Map boundaries
    position.x = Clamp(
        position.x,
        halfWidth,
        mMap->getWidth() - halfWidth
    );

    mPlayer->setPosition(position);
    mPlayer->setVelocity(velocity);

    // Enemy collision
    for (Entity *enemy : mEnemies)
    {
        enemy->update(deltaTime, mPlayer);

        if (mPlayer->isColliding(enemy))
            mState.playerHit = true;
    }

    // Spike collision
    for (Entity *platform : mPlatforms)
    {
        if (platform->getEntityType() == SPIKES &&
            mPlayer->isColliding(platform))
        {
            mState.playerHit = true;
        }
    }

    // Falling into a pit
    if (mPlayer->getPosition().y > SCREEN_HEIGHT + 100.0f)
        mState.playerHit = true;

    // Level completion
    if (!mState.playerHit && mPlayer->isColliding(mExit))
    {
        if      (mLevelNumber == 1) mState.nextSceneID = LEVEL2;
        else if (mLevelNumber == 2) mState.nextSceneID = LEVEL3;
        else                       mState.nextSceneID = WIN;
    }

    // Camera
    float cameraX = Clamp(
        mPlayer->getPosition().x,
        SCREEN_WIDTH / 2.0f,
        mMap->getWidth() - SCREEN_WIDTH / 2.0f
    );

    mCamera.target = { cameraX, ORIGIN.y };
}

void Scene::render()
{
    if (mBackground.id != 0)
    {
        float backgroundWidth =
            SCREEN_HEIGHT *
            (float) mBackground.width /
            mBackground.height;

        backgroundWidth = fmaxf(
            backgroundWidth, (float) SCREEN_WIDTH
        );

        float progress =
            (mCamera.target.x - SCREEN_WIDTH / 2.0f) /
            (mMap->getWidth() - SCREEN_WIDTH);

        float backgroundX =
            -progress * (backgroundWidth - SCREEN_WIDTH);

        DrawTexturePro(
            mBackground,
            {
                0.0f, 0.0f,
                (float) mBackground.width,
                (float) mBackground.height
            },
            {
                backgroundX, 0.0f,
                backgroundWidth,
                (float) SCREEN_HEIGHT
            },
            { 0.0f, 0.0f },
            0.0f,
            WHITE
        );
    }

    BeginMode2D(mCamera);

    if (mMap) mMap->render();

    for (Entity *platform : mPlatforms)
        platform->render();

    if (mExit)
    {
        mExit->render();

        Vector2 position = mExit->getPosition();

        const char *message =
            mLevelNumber == 3 ? "ESCAPE SHUTTLE" : "EXIT";

        DrawText(
            message,
            (int) position.x - MeasureText(message, 18) / 2,
            (int) (position.y - mExit->getScale().y / 2.0f - 25),
            18,
            SKYBLUE
        );
    }

    for (Entity *enemy : mEnemies)
        enemy->render();

    if (mPlayer) mPlayer->render();

    EndMode2D();

    const char *levelName = "";

    if (mLevelNumber == 1)
        levelName = "LEVEL 1 - Research Laboratory";
    else if (mLevelNumber == 2)
        levelName = "LEVEL 2 - Automated Factory";
    else
        levelName = "LEVEL 3 - Emergency Hangar";

    DrawRectangle(0, 0, SCREEN_WIDTH, 65, Fade(BLACK, 0.8f));
    DrawRectangle(0, 64, SCREEN_WIDTH, 1, SKYBLUE);

    DrawText(levelName, 20, 14, 24, RAYWHITE);
    DrawText("A / D: Move    SPACE: Jump", 20, 42, 14, LIGHTGRAY);
}

void Scene::shutdown()
{
    delete mPlayer;
    mPlayer = nullptr;

    delete mExit;
    mExit = nullptr;

    delete mMap;
    mMap = nullptr;

    for (Entity *enemy : mEnemies)
        delete enemy;

    mEnemies.clear();

    for (Entity *platform : mPlatforms)
        delete platform;

    mPlatforms.clear();

    if (mBackground.id != 0)
        UnloadTexture(mBackground);

    mBackground = { 0 };
}
