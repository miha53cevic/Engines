#include "SimpleOpenGL.h"
#include "Static_Shader.h"
#include "Renderer.h"
#include "Terrain.h"
#include "Entity.h"
#include "Camera.h"

class App : public SimpleOpenGL
{
public:
    App()
    {
        bWireframeMode = false;
    }

    ~App()
    {
        delete renderer;
        delete mesh;
        delete entity;
    }

private:
    Static_Shader shader;
    Renderer* renderer;
    Mesh* mesh;
    Entity* entity;
    Entity* entity1;
    Camera camera;
    Terrain* terrain;

    bool bWireframeMode;

protected:
    void Event(sf::Event& e) override
    {
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Tab)
        {
            EnableWireframe(bWireframeMode);
            bWireframeMode = !bWireframeMode;
        }
    }

protected:
    bool OnUserCreate() override
    {
        EnableVSync(true);
        EnableFPSCounter(true);

        renderer = new Renderer(glm::vec2(ScreenWidth(), ScreenHeight()));

        shader.createProgram("./shaders/static_shader");
        shader.loadProjectionMatrix(renderer->getProjectionMatrix());

        mesh = new Mesh("./resources/obj/cube.obj", "./resources/textures/cube.png");
        entity = new Entity(mesh);
        entity->setPosition({ 0, 0, -5 });

        entity1 = new Entity(mesh);
        entity1->setPosition({ -5, 0, -5 });

        terrain = new Terrain();

        return true;
    }

    bool OnUserUpdate(sf::Time elapsed) override
    {
        camera.Update(elapsed, 10);

        shader.Bind();

        entity->Rotate(0, 1, 1);
        shader.loadViewMatrix(&camera);
        renderer->Render(entity, &shader);
        renderer->Render(entity1, &shader);

        terrain->Draw(&shader);

        shader.Unbind();

        return true;
    }
};

int main()
{
    App app;
    app.setupWindow(sf::Vector2u(1280, 720), "Yet another OpenGL App");
    app.start();

	return 0;
}