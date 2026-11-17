
#ifndef CS3113_H
#define CS3113_H

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <string>

#define LOG(argument) std::cout << argument << '\n'

enum AppStatus { TERMINATED, RUNNING };

enum SceneID {
    NO_SCENE,
    MENU,
    LEVEL1,
    LEVEL2,
    LEVEL3,
    WIN,
    LOSE
};

constexpr int SCREEN_WIDTH  = 1000,
              SCREEN_HEIGHT = 600,
              FPS           = 120;

constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

constexpr Vector2 ORIGIN = {
    SCREEN_WIDTH / 2.0f,
    SCREEN_HEIGHT / 2.0f
};

#endif
