/**

* Author: Jiaxin Lin

* Assignment: Rise of the AI

* Date due: 11/16/2026

* I pledge that I have completed this assignment without

* collaborating with anyone else, in conformance with the

* NYU School of Engineering Policies and Procedures on

* Academic Misconduct.

**/

#include "Level3.h"

void Level3::initialise()
{
    initialiseLevel(3, 3840.0f, "assets/hangar.png");

    mMap->addGround(0, 512, 512, 128);
    mMap->addGround(768, 512, 544, 128);
    mMap->addGround(1568, 512, 448, 128);
    mMap->addGround(2304, 512, 448, 128);
    mMap->addGround(3040, 512, 448, 128);
    mMap->addGround(3648, 512, 192, 128);

    addPlatform({ 300, 410 }, { 160, 40 },
                "assets/platform_short.png");

    addPlatform({ 500, 330 }, { 140, 40 },
                "assets/platform_short.png");

    addPlatform({ 640, 430 }, { 140, 55 },
                "assets/platform_floating.png");

    addPlatform({ 900, 410 }, { 140, 40 },
                "assets/platform_short.png");

    addPlatform({ 1100, 330 }, { 180, 40 },
                "assets/platform_long.png");

    addPlatform({ 1440, 420 }, { 140, 55 },
                "assets/platform_floating.png");

    addPlatform({ 1750, 390 }, { 170, 40 },
                "assets/platform_short.png");

    addPlatform({ 1940, 310 }, { 140, 40 },
                "assets/platform_short.png");

    addPlatform({ 2160, 430 }, { 140, 55 },
                "assets/platform_floating.png");

    addPlatform({ 2500, 400 }, { 180, 40 },
                "assets/platform_long.png");

    addPlatform({ 2700, 320 }, { 150, 40 },
                "assets/platform_short.png");

    addPlatform({ 2890, 430 }, { 130, 55 },
                "assets/platform_floating.png");

    addPlatform({ 3250, 390 }, { 200, 40 },
                "assets/platform_long.png");

    addPlatform({ 3570, 430 }, { 130, 55 },
                "assets/platform_floating.png");

    // Jump pad
    Entity *jumpPad = new Entity(
        { 450.0f, 486.0f },
        { 80.0f, 52.0f },
        JUMP_PAD
    );

    jumpPad->setColliderDimensions({ 70.0f, 20.0f });
    mPlatforms.push_back(jumpPad);

    // Spikes
    mPlatforms.push_back(new Entity(
        { 950.0f, 495.0f },
        { 90.0f, 34.0f },
        SPIKES
    ));

    mPlatforms.push_back(new Entity(
        { 2380.0f, 495.0f },
        { 90.0f, 34.0f },
        SPIKES
    ));

    // Patrol robots
    addEnemy({ 300, 489 }, PATROL, 80);
    addEnemy({ 1150, 489 }, PATROL, 90);
    addEnemy({ 1800, 489 }, PATROL, 100);
    addEnemy({ 3250, 489 }, PATROL, 120);

    // Hunter robots
    addEnemy({ 850, 479 }, HUNTER, 45);
    addEnemy({ 1920, 479 }, HUNTER, 60);
    addEnemy({ 2580, 479 }, HUNTER, 100);

    // Flying drones
    addEnemy({ 680, 145 }, DRONE, 120);
    addEnemy({ 1450, 140 }, DRONE, 130);
    addEnemy({ 2210, 150 }, DRONE, 140);
    addEnemy({ 3000, 145 }, DRONE, 130);

    // Escape shuttle
    mExit = new Entity(
        { mMap->getWidth() - 100.0f, 459.0f },
        { 180.0f, 106.0f },
        SPACESHIP
    );
}
