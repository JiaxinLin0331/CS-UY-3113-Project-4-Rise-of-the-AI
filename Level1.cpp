/**

* Author: Jiaxin Lin

* Assignment: Rise of the AI

* Date due: 11/16/2026

* I pledge that I have completed this assignment without

* collaborating with anyone else, in conformance with the

* NYU School of Engineering Policies and Procedures on

* Academic Misconduct.

**/

#include "Level1.h"

void Level1::initialise()
{
    initialiseLevel(1, 2560.0f, "assets/laboratory.png");

    mMap->addGround(0, 512, 640, 128);
    mMap->addGround(800, 512, 640, 128);
    mMap->addGround(1600, 512, 512, 128);
    mMap->addGround(2272, 512, 288, 128);

    addPlatform({ 280, 420 }, { 160, 40 },
                "assets/platform_short.png");

    addPlatform({ 520, 340 }, { 180, 32 },
                "assets/platform_long.png");

    addPlatform({ 720, 430 }, { 120, 40 },
                "assets/platform_short.png");

    addPlatform({ 1000, 400 }, { 220, 40 },
                "assets/platform_long.png");

    addPlatform({ 1350, 420 }, { 140, 40 },
                "assets/platform_short.png");

    addPlatform({ 1520, 440 }, { 120, 55 },
                "assets/platform_floating.png");

    addPlatform({ 1830, 400 }, { 220, 40 },
                "assets/platform_long.png");

    addPlatform({ 2190, 430 }, { 130, 40 },
                "assets/platform_short.png");

    addEnemy({ 360, 489 }, PATROL, 110);
    addEnemy({ 1080, 489 }, PATROL, 140);
    addEnemy({ 1840, 489 }, PATROL, 140);
    addEnemy({ 2400, 489 }, PATROL, 55);

    // Exit
    mExit = new Entity(
        { mMap->getWidth() - 80.0f, 466.0f },
        { 132.0f, 92.0f },
        EXIT
    );
}
