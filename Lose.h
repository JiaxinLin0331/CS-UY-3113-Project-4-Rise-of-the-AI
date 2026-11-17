
#ifndef LOSE_H
#define LOSE_H

#include "Scene.h"

class Lose : public Scene
{
public:
    void initialise() override;
    void processInput() override;
    void update(float deltaTime) override;
    void render() override;
};

#endif
