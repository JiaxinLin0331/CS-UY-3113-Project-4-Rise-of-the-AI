#ifndef MAP_H
#define MAP_H

#include "cs3113.h"

class Map
{
private:
    std::vector<Rectangle> mGround;
    std::vector<std::vector<int>> mMapData;

    Texture2D mTexture;
    float mWidth;
    Color mColor;

    int mRows;
    int mColumns;

public:
    static constexpr int TILE_SIZE = 32;

    Map(float width, Color color = DARKGRAY);

    ~Map();

    void addGround(float x, float y, float width, float height);
    void render();

    const std::vector<Rectangle> &getGround() const {
        return mGround;
    }

    float getWidth() const { return mWidth; }
    float getLeftBoundary() const { return 0.0f; }
    float getRightBoundary() const { return mWidth; }
};

#endif
