/**

* Author: Jiaxin Lin

* Assignment: Rise of the AI

* Date due: 11/16/2026

* I pledge that I have completed this assignment without

* collaborating with anyone else, in conformance with the

* NYU School of Engineering Policies and Procedures on

* Academic Misconduct.

**/

#include "Lose.h"

void Lose::initialise()
{
    mState = {};

    mBackground = LoadTexture("assets/factory.png");
}

void Lose::processInput()
{
    if (IsKeyPressed(KEY_R))
        mState.nextSceneID = MENU;
}

void Lose::update(float deltaTime)
{
}

void Lose::render()
{
    ClearBackground(BLACK);

    DrawTexturePro(
        mBackground,
        {
            0.0f, 0.0f,
            (float) mBackground.width,
            (float) mBackground.height
        },
        {
            0.0f, 0.0f,
            (float) SCREEN_WIDTH,
            (float) SCREEN_HEIGHT
        },
        { 0.0f, 0.0f },
        0.0f,
        WHITE
    );

    DrawRectangle(
        0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
        Fade(BLACK, 0.75f)
    );

    float warningAlpha =
        0.1f + 0.08f * sinf((float) GetTime() * 4.0f);

    DrawRectangle(
        0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
        Fade(RED, warningAlpha)
    );

    DrawRectangle(180, 130, 640, 340, Fade(BLACK, 0.75f));
    DrawRectangleLines(180, 130, 640, 340, RED);

    DrawText(
        "ESCAPE FAILED",
        SCREEN_WIDTH / 2 -
            MeasureText("ESCAPE FAILED", 24) / 2,
        165, 24, RED
    );

    DrawText(
        "YOU LOSE",
        SCREEN_WIDTH / 2 - MeasureText("YOU LOSE", 70) / 2,
        220, 70, RED
    );

    DrawText(
        "The facility remains under AI control.",
        SCREEN_WIDTH / 2 -
            MeasureText("The facility remains under AI control.", 22) / 2,
        315, 22, RAYWHITE
    );

    DrawText(
        "Press R to Return to Menu",
        SCREEN_WIDTH / 2 -
            MeasureText("Press R to Return to Menu", 22) / 2,
        410, 22, LIGHTGRAY
    );
}
