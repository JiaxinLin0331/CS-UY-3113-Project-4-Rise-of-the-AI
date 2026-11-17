/**

* Author: Jiaxin Lin

* Assignment: Rise of the AI

* Date due: 11/16/2026

* I pledge that I have completed this assignment without

* collaborating with anyone else, in conformance with the

* NYU School of Engineering Policies and Procedures on

* Academic Misconduct.

**/

#include "Menu.h"

void Menu::initialise()
{
    mState = {};

    mBackground = LoadTexture("assets/laboratory.png");
}

void Menu::processInput()
{
    if (IsKeyPressed(KEY_ENTER))
        mState.nextSceneID = LEVEL1;
}

void Menu::update(float deltaTime)
{
}

void Menu::render()
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
        Fade(BLACK, 0.55f)
    );

    DrawRectangle(180, 100, 640, 400, Fade(BLACK, 0.65f));
    DrawRectangleLines(180, 100, 640, 400, SKYBLUE);

    DrawText(
        "SYSTEM FAILURE",
        SCREEN_WIDTH / 2 - MeasureText("SYSTEM FAILURE", 20) / 2,
        135, 20, RED
    );

    DrawText(
        "ESCAPE",
        SCREEN_WIDTH / 2 - MeasureText("ESCAPE", 75) / 2,
        180, 75, RAYWHITE
    );

    DrawText(
        "PROTOCOL",
        SCREEN_WIDTH / 2 - MeasureText("PROTOCOL", 55) / 2,
        260, 55, SKYBLUE
    );

    if (sinf((float) GetTime() * 4.0f) > -0.5f)
    {
        DrawText(
            "Press Enter to Start",
            SCREEN_WIDTH / 2 -
                MeasureText("Press Enter to Start", 27) / 2,
            365, 27, WHITE
        );
    }

    DrawText(
        "A / D - Move     SPACE - Jump",
        SCREEN_WIDTH / 2 -
            MeasureText("A / D - Move     SPACE - Jump", 20) / 2,
        430, 20, LIGHTGRAY
    );

    DrawText(
        "Escape the facility before it is too late.",
        SCREEN_WIDTH / 2 -
            MeasureText("Escape the facility before it is too late.", 16) / 2,
        540, 16, LIGHTGRAY
    );
}
