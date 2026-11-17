/**

* Author: Jiaxin Lin

* Assignment: Rise of the AI

* Date due: 11/16/2026

* I pledge that I have completed this assignment without

* collaborating with anyone else, in conformance with the

* NYU School of Engineering Policies and Procedures on

* Academic Misconduct.

**/

#include "Map.h"

Map::Map(float width, Color color) :
    mTexture{},
    mWidth{ width },
    mColor{ color },
    mRows{ 20 },
    mColumns{ (int) ceilf(width / TILE_SIZE) }
{
    mMapData.resize(
        mRows,
        std::vector<int>(mColumns, 0)
    );

    if (FileExists("assets/tileset.png"))
    {
        mTexture = LoadTexture("assets/tileset.png");
        SetTextureFilter(mTexture, TEXTURE_FILTER_POINT);
    }
}

Map::~Map()
{
    if (mTexture.id != 0)
        UnloadTexture(mTexture);
}

void Map::addGround(
    float x,
    float y,
    float width,
    float height
)
{
    mGround.push_back({ x, y, width, height });

    int startColumn = (int) (x / TILE_SIZE);
    int startRow = (int) (y / TILE_SIZE);

    int endColumn = (int) ceilf((x + width) / TILE_SIZE);
    int endRow = (int) ceilf((y + height) / TILE_SIZE);

    for (int row = startRow; row < endRow; row++)
    {
        for (int column = startColumn; column < endColumn; column++)
        {
            if (row < 0 || row >= mRows ||
                column < 0 || column >= mColumns)
                continue;

            if (row == startRow)
                mMapData[row][column] = 1 + column % 4;
            else
                mMapData[row][column] = 13;
        }
    }
}

void Map::render()
{
    for (int row = 0; row < mRows; row++)
    {
        for (int column = 0; column < mColumns; column++)
        {
            int tile = mMapData[row][column];

            if (tile == 0) continue;

            Rectangle destination = {
                (float) column * TILE_SIZE,
                (float) row * TILE_SIZE,
                (float) TILE_SIZE,
                (float) TILE_SIZE
            };

            if (mTexture.id != 0)
            {
                int index = tile - 1;

                Rectangle source = {
                    (float) (index % 8) * TILE_SIZE,
                    (float) (index / 8) * TILE_SIZE,
                    (float) TILE_SIZE,
                    (float) TILE_SIZE
                };

                DrawTexturePro(
                    mTexture,
                    source,
                    destination,
                    { 0.0f, 0.0f },
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangleRec(destination, mColor);
            }
        }
    }
}
