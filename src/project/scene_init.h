#pragma once

#include "../core/scene.h"

class SceneInit : public Scene
{
public:
    SceneInit() = default;
    ~SceneInit() = default;
    virtual void init() override;
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;

};

