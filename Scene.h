#ifndef SCENE_H
#define SCENE_H

#include "cs3113.h"
#include "Entity.h"
#include "Map.h"

extern Sound gJumpSound;

struct SceneState
{
    SceneID nextSceneID = NO_SCENE;
    bool playerHit = false;
};

class Scene
{
protected:
    SceneState mState;

    Entity *mPlayer = nullptr;
    Entity *mExit = nullptr;
    Map *mMap = nullptr;

    std::vector<Entity *> mEnemies;
    std::vector<Entity *> mPlatforms;

    Texture2D mBackground = { 0 };
    Camera2D mCamera = { 0 };

    int mLevelNumber = 0;

    void initialiseLevel(int levelNumber, float mapWidth, const char *backgroundPath);
    void addPlatform(Vector2 position, Vector2 scale, const char *filepath);
    void addEnemy(Vector2 position, EntityType type, float patrolDistance);

public:
    virtual ~Scene();

    virtual void initialise() = 0;
    virtual void processInput();
    virtual void update(float deltaTime);
    virtual void render();
    virtual void shutdown();

    SceneState &getState() { return mState; }

    Entity *getPlayer() const { return mPlayer; }
    Map *getMap() const { return mMap; }
};

#endif
