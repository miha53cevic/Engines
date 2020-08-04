#pragma once
#include "State.h"

#include "../gl/glObjects.h"
#include "../world/Entity.h"
#include "../util/Camera.h"

class Application;

class Playing : public State
{
public:
    Playing(Application* app);

    virtual void init() override;
    virtual void HandleInput(sf::Event& e) override;
    virtual void Update(sf::Time elapsed) override;
    virtual void Draw() override;

    virtual void pause();
    virtual void resume();

private:
    gl::Shader m_shader;
    gl::Texture m_texture;
    Entity m_cube;
    Camera m_camera;
};
