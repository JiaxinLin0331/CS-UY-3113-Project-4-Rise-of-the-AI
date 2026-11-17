
#ifndef WIN_H
#define WIN_H

#include "Scene.h"

class Win : public Scene
{
public:
    void initialise() override;
    void processInput() override;
    void update(float deltaTime) override;
    void render() override;
};

#endif
