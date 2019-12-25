#include "SimpleOpenGL.h"

#include "Static_Shader.h"
#include "Entity.h"
#include "Renderer.h"
#include "Light.h"

class OpenGL : public SimpleOpenGL
{
public:
    OpenGL()
    {
    }

private:
    // Napomena: Nemoj koristiti prazne Constructore jer se onda zove deconstructor nakon kaj se doda
    // Zato su bolji std::unique_ptr<>() jer se oni brisu samo kada se glavni objekt brise
    // Ali se zato moraju podaci prebaciti preko std::move()
    EntityRef entity;
    Static_ShaderRef shaderProgram;
    RendererRef renderer;
    CameraRef camera;
    Light light;
    std::map<Mesh, std::vector<Entity>> entities;

protected:
    void Event(sf::Event& e) override
    {
    }

    bool OnUserCreate() override
    {
        EnableFPSCounter(true);
        EnableVSync(true);

        // Create light source
        light.setPosition(glm::vec3(0, 0, -20));
        light.setColour(glm::vec3(1, 1, 1));

        entity = std::make_unique<Entity>("obj/dragon", "tex/blank.png", glm::vec3(0, 0, -25.0f), glm::vec3(0, 0, 0), 1);

        shaderProgram = std::make_unique<Static_Shader>();
        shaderProgram->createProgram("shaders/texture_shader");

        renderer = std::make_unique<Renderer>(glm::vec2(ScreenWidth(), ScreenHeight()), shaderProgram);

        camera = std::make_unique<Camera>();

        return true;
    }

    bool OnUserUpdate(sf::Time elapsed) override
    {
        entity->Rotate(0, -100 * elapsed.asSeconds(), 0);

        camera->Update(elapsed, 10.0f);

        shaderProgram->Bind();
        shaderProgram->loadLight(light);
       
        shaderProgram->loadViewMatrix(camera.get());
        renderer->Render(entity, shaderProgram.get());

        shaderProgram->Unbind();

        return true;
    }

private:
};

int main()
{
    OpenGL app;
    app.setupWindow({ 1280, 720 }, "OpenGL");
    app.start();

    return 0;
}