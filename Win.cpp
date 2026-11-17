/**

* Author: Jiaxin Lin

* Assignment: Rise of the AI

* Date due: 11/16/2026

* I pledge that I have completed this assignment without

* collaborating with anyone else, in conformance with the

* NYU School of Engineering Policies and Procedures on

* Academic Misconduct.

**/

#include "Win.h"

void Win::initialise()
{
    mState = {};

    mBackground = LoadTexture("assets/hangar.png");
}

void Win::processInput()
{
    if (IsKeyPressed(KEY_R))
        mState.nextSceneID = MENU;
}

void Win::update(float deltaTime)
{
}

void Win::render()
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
        Fade(BLACK, 0.6f)
    );

    DrawRectangle(180, 130, 640, 340, Fade(BLACK, 0.7f));
    DrawRectangleLines(180, 130, 640, 340, SKYBLUE);

    DrawText(
        "MISSION COMPLETE",
        SCREEN_WIDTH / 2 -
            MeasureText("MISSION COMPLETE", 24) / 2,
        165, 24, SKYBLUE
    );

    DrawText(
        "YOU WIN!",
        SCREEN_WIDTH / 2 - MeasureText("YOU WIN!", 70) / 2,
        220, 70, GREEN
    );

    DrawText(
        "You escaped the facility.",
        SCREEN_WIDTH / 2 -
            MeasureText("You escaped the facility.", 25) / 2,
        315, 25, RAYWHITE
    );

    DrawText(
        "Press R to Return to Menu",
        SCREEN_WIDTH / 2 -
            MeasureText("Press R to Return to Menu", 22) / 2,
        410, 22, LIGHTGRAY
    );
}
