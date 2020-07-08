#include "Playing.h"

#include "../app/application.h"
#include "../util/Cube.h"
#include "../util/math/Math.h"

Playing::Playing(Application * app)
    : State(app)
{
}

void Playing::init()
{
    m_shader.setAttribute(0, "position");
    m_shader.setAttribute(1, "textureCoords");

    m_shader.createProgram("deps/glsl/shader1");

    m_shader.setUniformLocation("transformationMatrix");
    m_shader.setUniformLocation("projectionMatrix");
    m_shader.setUniformLocation("viewMatrix");

    m_texture.loadTexture("deps/Resources/textures/tex1.png");

    m_cube.setVBO(Cube::verticies, 0, 3);
    m_cube.setVBO(Cube::textureCoords, 1, 2);
    m_cube.setEBO(Cube::indicies);

    m_cube.position = glm::vec3(0, 0, -3);

    m_shader.Bind();
    m_shader.loadMatrix(m_shader.getUniformLocation("projectionMatrix"), Math::createProjectionMatrix(glm::vec2(m_app->getWindow()->ScreenWidth(), m_app->getWindow()->ScreenHeight()), 90, 0.1, 1000));
    m_shader.Unbind();
}

void Playing::HandleInput(sf::Event & e)
{
}

void Playing::Update(sf::Time elapsed)
{
    m_camera.Update(elapsed, m_app->getWindow()->getWindow());
}

void Playing::Draw()
{
    // Activate the shader first
    m_shader.Bind();

    // Activate and bind the texture before use
    m_texture.activateAndBind();

    m_cube.rotation.x += 0.01;
    m_cube.rotation.y += 0.01;

    // Load the matrices
    m_shader.loadMatrix(m_shader.getUniformLocation("viewMatrix"), Math::createViewMatrix(&m_camera));
    m_shader.loadMatrix(m_shader.getUniformLocation("transformationMatrix"), Math::createTransformationMatrix(&m_cube));
    
    // Draw the object
    m_cube.draw();

    m_shader.Unbind();
}

void Playing::pause()
{
}

void Playing::resume()
{
}
