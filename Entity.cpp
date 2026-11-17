/**

* Author: Jiaxin Lin

* Assignment: Rise of the AI

* Date due: 11/16/2026

* I pledge that I have completed this assignment without

* collaborating with anyone else, in conformance with the

* NYU School of Engineering Policies and Procedures on

* Academic Misconduct.

**/

#include "Entity.h"

Entity::Entity(
    Vector2 position,
    Vector2 scale,
    EntityType entityType,
    Color color,
    const char *texturePath
) :
    mPosition{ position },
    mStartPosition{ position },
    mMovement{ 0.0f, 0.0f },
    mVelocity{ 0.0f, 0.0f },
    mAcceleration{ 0.0f, 0.0f },
    mScale{ scale },
    mColliderDimensions{ scale },
    mTexture{},
    mColor{ color },
    mEntityType{ entityType },
    mEntityStatus{ ACTIVE },
    mAIType{ NO_AI },
    mDirection{ RIGHT },
    mSpeed{ DEFAULT_SPEED },
    mCurrentFrameIndex{ 0 },
    mJumpingPower{ 480.0f },
    mAnimationTime{ 0.0f },
    mAITime{ 0.0f },
    mPatrolDistance{ 120.0f },
    mIsJumping{ false },
    mIsGrounded{ false },
    mIsAnimated{ false }
{
    const char *filepath = texturePath;

    switch (mEntityType)
    {
        case PLAYER:
            filepath = "assets/player.png";
            mIsAnimated = true;
            mAcceleration.y = 900.0f;
            break;

        case PATROL:
            filepath = "assets/patrol.png";
            mIsAnimated = true;
            break;

        case HUNTER:
            filepath = "assets/hunter.png";
            mIsAnimated = true;
            break;

        case DRONE:
            filepath = "assets/drone.png";
            mIsAnimated = true;
            break;

        case PLATFORM:
            if (!filepath)
                filepath = "assets/platform_short.png";
            break;

        case JUMP_PAD:
            filepath = "assets/jump_pad.png";
            break;

        case SPIKES:
            filepath = "assets/spikes.png";
            break;

        case CRATE:
            filepath = "assets/crate.png";
            break;

        case EXIT:
            filepath = "assets/exit.png";
            break;

        case SPACESHIP:
            filepath = "assets/spaceship.png";
            break;

        default:
            break;
    }

    if (filepath && FileExists(filepath))
    {
        mTexture = LoadTexture(filepath);
        SetTextureFilter(mTexture, TEXTURE_FILTER_POINT);
    }
}

Entity::~Entity()
{
    if (mTexture.id != 0)
        UnloadTexture(mTexture);
}

void Entity::moveLeft()
{
    mMovement.x = -1.0f;
    mDirection = LEFT;
}

void Entity::moveRight()
{
    mMovement.x = 1.0f;
    mDirection = RIGHT;
}

void Entity::resetMovement()
{
    mMovement = { 0.0f, 0.0f };
}

void Entity::jump()
{
    if (mIsGrounded)
    {
        mVelocity.y = -mJumpingPower;
        mIsJumping = true;
        mIsGrounded = false;
    }
}

void Entity::AIWander(float deltaTime)
{
    mPosition.x += mMovement.x * mSpeed * deltaTime;

    if (mPosition.x >= mStartPosition.x + mPatrolDistance)
        moveLeft();
    else if (mPosition.x <= mStartPosition.x - mPatrolDistance)
        moveRight();
}

void Entity::AIFollow(Entity *player)
{
    if (!player) return;

    float distance = Vector2Distance(
        mPosition, player->getPosition()
    );

    if (distance < 300.0f)
    {
        if (player->getPosition().x < mPosition.x)
            moveLeft();
        else
            moveRight();
    }
    else
    {
        resetMovement();
    }
}

void Entity::AIFly(float deltaTime)
{
    mAITime += deltaTime;

    mPosition.x += mMovement.x * mSpeed * deltaTime;

    mPosition.y = mStartPosition.y +
                  sinf(mAITime * 2.0f) * 45.0f;

    if (mPosition.x >= mStartPosition.x + mPatrolDistance)
        moveLeft();
    else if (mPosition.x <= mStartPosition.x - mPatrolDistance)
        moveRight();
}

void Entity::AIActivate(Entity *player)
{
    if (mAIType == FOLLOWER)
        AIFollow(player);
}

void Entity::update(float deltaTime, Entity *player)
{
    if (mEntityStatus == INACTIVE) return;

    if (mEntityType == PLAYER)
    {
        mVelocity.x = mMovement.x * mSpeed;
        mVelocity.y += mAcceleration.y * deltaTime;

        mPosition.x += mVelocity.x * deltaTime;
        mPosition.y += mVelocity.y * deltaTime;
    }
    else
    {
        AIActivate(player);

        if (mAIType == WANDERER)
        {
            AIWander(deltaTime);
        }
        else if (mAIType == FOLLOWER)
        {
            mPosition.x += mMovement.x * mSpeed * deltaTime;

            mPosition.x = Clamp(
                mPosition.x,
                mStartPosition.x - mPatrolDistance,
                mStartPosition.x + mPatrolDistance
            );
        }
        else if (mAIType == FLYER)
        {
            AIFly(deltaTime);
        }
    }

    if (mIsAnimated)
    {
        mAnimationTime += deltaTime;

        if (mAnimationTime >= 0.12f)
        {
            mAnimationTime -= 0.12f;
            mCurrentFrameIndex =
                (mCurrentFrameIndex + 1) % 6;
        }
    }
}

bool Entity::isColliding(Entity *other) const
{
    if (!other || !other->isActive()) return false;

    float xDistance = fabsf(
        mPosition.x - other->mPosition.x
    );

    float yDistance = fabsf(
        mPosition.y - other->mPosition.y
    );

    float xOverlap = (
        mColliderDimensions.x +
        other->mColliderDimensions.x
    ) / 2.0f;

    float yOverlap = (
        mColliderDimensions.y +
        other->mColliderDimensions.y
    ) / 2.0f;

    return xDistance < xOverlap &&
           yDistance < yOverlap;
}

void Entity::render()
{
    if (mEntityStatus == INACTIVE) return;

    Rectangle destination = {
        mPosition.x - mScale.x / 2.0f,
        mPosition.y - mScale.y / 2.0f,
        mScale.x,
        mScale.y
    };

    if (mTexture.id == 0)
    {
        DrawRectangleRec(destination, mColor);
        return;
    }

    Rectangle source = {
        0.0f, 0.0f,
        (float) mTexture.width,
        (float) mTexture.height
    };

    if (mIsAnimated)
    {
        int frame = 0;

        if (mEntityType == PLAYER)
        {
            if (!mIsGrounded)
                frame = mVelocity.y < 0.0f ? 5 : 6;
            else if (mMovement.x != 0.0f)
                frame = 2 + mCurrentFrameIndex % 3;
            else
                frame = mCurrentFrameIndex % 2;
        }
        else if (mEntityType == DRONE)
        {
            frame = mCurrentFrameIndex % 3;
        }
        else
        {
            if (mMovement.x != 0.0f)
                frame = 2 + mCurrentFrameIndex % 3;
            else
                frame = mCurrentFrameIndex % 2;
        }

        float frameWidth  = (float) mTexture.width / 4.0f;
        float frameHeight = (float) mTexture.height / 2.0f;

        source = {
            (frame % 4) * frameWidth,
            (frame / 4) * frameHeight,
            frameWidth,
            frameHeight
        };

        if (mDirection == LEFT)
            source.width = -source.width;

        if (mEntityType != DRONE)
        {
            destination.y = mPosition.y +
                            mColliderDimensions.y / 2.0f -
                            mScale.y * 60.0f / 64.0f;
        }
    }

    DrawTexturePro(
        mTexture,
        source,
        destination,
        { 0.0f, 0.0f },
        0.0f,
        WHITE
    );
}
