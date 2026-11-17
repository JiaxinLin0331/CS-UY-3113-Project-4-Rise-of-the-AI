
#ifndef MENU_H
#define MENU_H

#include "Scene.h"

class Menu : public Scene
{
public:
    void initialise() override;
    void processInput() override;
    void update(float deltaTime) override;
    void render() override;
};

#endif
