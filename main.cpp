/**

* Author: Jiaxin Lin

* Assignment: Rise of the AI

* Date due: 11/16/2026

* I pledge that I have completed this assignment without

* collaborating with anyone else, in conformance with the

* NYU School of Engineering Policies and Procedures on

* Academic Misconduct.

**/

#include "cs3113.h"
#include "Scene.h"
#include "Menu.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Win.h"
#include "Lose.h"

// Global Constants
constexpr int MAX_LIVES = 5;

// Global Variables
AppStatus gAppStatus = RUNNING;

float gPreviousTicks   = 0.0f,
      gTimeAccumulator = 0.0f,
      gFadeAlpha       = 1.0f;

Scene *gCurrentScene = nullptr;
std::map<SceneID, Scene *> gLevels = {};

int gLives = MAX_LIVES;

SceneID gCurrentSceneID = NO_SCENE;

Music gBackgroundMusic;

Sound gJumpSound;
Sound gDamageSound;
Sound gSuccessSound;

Texture2D gHeartFull;
Texture2D gHeartEmpty;

// Function Declarations
void switchToScene(SceneID sceneID);
void initialise();
void processInput();
void update();
void render();
void shutdown();

void switchToScene(SceneID sceneID)
{
    if (gCurrentScene)
        gCurrentScene->shutdown();

    gCurrentSceneID = sceneID;
    gCurrentScene = gLevels[sceneID];

    gCurrentScene->initialise();

    gFadeAlpha = 1.0f;

    if (sceneID == MENU)
        gLives = MAX_LIVES;
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Escape Protocol");
    InitAudioDevice();

    gBackgroundMusic = LoadMusicStream("assets/background.wav");

    gJumpSound    = LoadSound("assets/jump.ogg");
    gDamageSound  = LoadSound("assets/damage.ogg");
    gSuccessSound = LoadSound("assets/success.ogg");

    gBackgroundMusic.looping = true;

    SetMusicVolume(gBackgroundMusic, 0.5f);

    SetSoundVolume(gJumpSound, 0.5f);
    SetSoundVolume(gDamageSound, 0.7f);
    SetSoundVolume(gSuccessSound, 0.7f);

    PlayMusicStream(gBackgroundMusic);

    gHeartFull  = LoadTexture("assets/heart_full.png");
    gHeartEmpty = LoadTexture("assets/heart_empty.png");

    gLevels[MENU]   = new Menu();
    gLevels[LEVEL1] = new Level1();
    gLevels[LEVEL2] = new Level2();
    gLevels[LEVEL3] = new Level3();
    gLevels[WIN]    = new Win();
    gLevels[LOSE]   = new Lose();

    switchToScene(MENU);

    gPreviousTicks = (float) GetTime();

    SetTargetFPS(FPS);
}

void processInput()
{
    if (WindowShouldClose() || IsKeyPressed(KEY_Q))
    {
        gAppStatus = TERMINATED;
        return;
    }

    // Debug level switching
    if (IsKeyPressed(KEY_ONE))
    {
        if (gLives <= 0) gLives = MAX_LIVES;

        switchToScene(LEVEL1);
        return;
    }

    if (IsKeyPressed(KEY_TWO))
    {
        if (gLives <= 0) gLives = MAX_LIVES;

        switchToScene(LEVEL2);
        return;
    }

    if (IsKeyPressed(KEY_THREE))
    {
        if (gLives <= 0) gLives = MAX_LIVES;

        switchToScene(LEVEL3);
        return;
    }

    gCurrentScene->processInput();
}

void update()
{
    UpdateMusicStream(gBackgroundMusic);

    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;

    gPreviousTicks = ticks;
    deltaTime = fminf(deltaTime, 0.1f);

    gFadeAlpha = fmaxf(0.0f, gFadeAlpha - deltaTime * 3.0f);

    deltaTime += gTimeAccumulator;

    if (deltaTime < FIXED_TIMESTEP)
    {
        gTimeAccumulator = deltaTime;
        return;
    }

    while (deltaTime >= FIXED_TIMESTEP)
    {
        gCurrentScene->update(FIXED_TIMESTEP);
        deltaTime -= FIXED_TIMESTEP;

        if (gCurrentScene->getState().playerHit)
        {
            PlaySound(gDamageSound);

            gLives--;

            if (gLives <= 0)
                switchToScene(LOSE);
            else
                switchToScene(gCurrentSceneID);

            deltaTime = 0.0f;
            break;
        }

        SceneID nextSceneID =
            gCurrentScene->getState().nextSceneID;

        if (nextSceneID != NO_SCENE)
        {
            if (nextSceneID == LEVEL2 ||
                nextSceneID == LEVEL3 ||
                nextSceneID == WIN)
            {
                PlaySound(gSuccessSound);
            }

            switchToScene(nextSceneID);

            deltaTime = 0.0f;
            break;
        }
    }

    gTimeAccumulator = deltaTime;
}

void render()
{
    BeginDrawing();
    ClearBackground(BLACK);

    gCurrentScene->render();

    // Lives
    if (gCurrentSceneID == LEVEL1 ||
        gCurrentSceneID == LEVEL2 ||
        gCurrentSceneID == LEVEL3)
    {
        for (int i = 0; i < MAX_LIVES; i++)
        {
            Texture2D heart =
                i < gLives ? gHeartFull : gHeartEmpty;

            DrawTexturePro(
                heart,
                {
                    0.0f, 0.0f,
                    (float) heart.width,
                    (float) heart.height
                },
                {
                    SCREEN_WIDTH - 220.0f + i * 40.0f,
                    15.0f,
                    35.0f,
                    35.0f
                },
                { 0.0f, 0.0f },
                0.0f,
                WHITE
            );
        }
    }

    // Fade in
    if (gFadeAlpha > 0.0f)
    {
        DrawRectangle(
            0, 0,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            Fade(BLACK, gFadeAlpha)
        );
    }

    EndDrawing();
}

void shutdown()
{
    if (gCurrentScene)
        gCurrentScene->shutdown();

    for (std::pair<const SceneID, Scene *> &entry : gLevels)
        delete entry.second;

    gLevels.clear();
    gCurrentScene = nullptr;

    UnloadTexture(gHeartFull);
    UnloadTexture(gHeartEmpty);

    StopMusicStream(gBackgroundMusic);
    UnloadMusicStream(gBackgroundMusic);

    UnloadSound(gJumpSound);
    UnloadSound(gDamageSound);
    UnloadSound(gSuccessSound);

    CloseAudioDevice();
    CloseWindow();
}

int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }

    shutdown();

    return 0;
}
