/**

* Author: Jiaxin Lin

* Assignment: Rise of the AI

* Date due: 11/16/2026

* I pledge that I have completed this assignment without

* collaborating with anyone else, in conformance with the

* NYU School of Engineering Policies and Procedures on

* Academic Misconduct.

**/

#include "Level2.h"

void Level2::initialise()
{
    initialiseLevel(2, 3200.0f, "assets/factory.png");

    mMap->addGround(0, 512, 576, 128);
    mMap->addGround(768, 512, 608, 128);
    mMap->addGround(1600, 512, 608, 128);
    mMap->addGround(2432, 512, 320, 128);
    mMap->addGround(2976, 512, 224, 128);

    addPlatform({ 300, 410 }, { 180, 40 },
                "assets/platform_short.png");

    addPlatform({ 500, 330 }, { 150, 40 },
                "assets/platform_short.png");

    addPlatform({ 670, 420 }, { 130, 40 },
                "assets/platform_short.png");

    addPlatform({ 900, 385 }, { 180, 40 },
                "assets/platform_long.png");

    addPlatform({ 1120, 300 }, { 180, 40 },
                "assets/platform_long.png");

    addPlatform({ 1300, 380 }, { 140, 40 },
                "assets/platform_short.png");

    addPlatform({ 1480, 430 }, { 140, 55 },
                "assets/platform_floating.png");

    addPlatform({ 1750, 420 }, { 170, 40 },
                "assets/platform_short.png");

    addPlatform({ 1980, 340 }, { 160, 40 },
                "assets/platform_short.png");

    addPlatform({ 2320, 430 }, { 140, 55 },
                "assets/platform_floating.png");

    addPlatform({ 2600, 400 }, { 200, 40 },
                "assets/platform_long.png");

    addPlatform({ 2860, 430 }, { 140, 55 },
                "assets/platform_floating.png");

    // Jump pad
    Entity *jumpPad = new Entity(
        { 520.0f, 486.0f },
        { 80.0f, 52.0f },
        JUMP_PAD
    );

    jumpPad->setColliderDimensions({ 70.0f, 20.0f });
    mPlatforms.push_back(jumpPad);

    // Spikes
    mPlatforms.push_back(new Entity(
        { 850.0f, 495.0f },
        { 90.0f, 34.0f },
        SPIKES
    ));

    // Patrol robots
    addEnemy({ 330, 489 }, PATROL, 90);
    addEnemy({ 1000, 489 }, PATROL, 90);
    addEnemy({ 1840, 489 }, PATROL, 100);
    addEnemy({ 2570, 489 }, PATROL, 90);

    // Hunter robots
    addEnemy({ 1240, 479 }, HUNTER, 85);
    addEnemy({ 2050, 479 }, HUNTER, 100);
    addEnemy({ 3070, 479 }, HUNTER, 50);

    // Exit
    mExit = new Entity(
        { mMap->getWidth() - 80.0f, 466.0f },
        { 132.0f, 92.0f },
        EXIT
    );
}
