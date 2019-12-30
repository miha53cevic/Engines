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
        bWireframeMode = true;
    }

    ~App()
    {
        delete renderer;
        delete mesh;
        delete terrain;

        renderer = nullptr;
        mesh = nullptr;
        terrain = nullptr;
    }

private:
    Static_Shader shader;
    Camera        camera;

    Renderer* renderer;
    Mesh*     mesh;
    Terrain*  terrain;

    std::map<Mesh*, std::vector<Entity>> entity_map;

    bool bWireframeMode;

    void processEntity(Mesh* m, Entity e)
    {
        if (entity_map.find(m) == entity_map.end())
        {
            // Add the mesh to the collection
            entity_map.insert(std::make_pair(m, std::vector<Entity>()));
            entity_map.at(m).push_back(e);
        }
        else
        {
            // If it exists just push back the entity
            entity_map.at(m).push_back(e);
        }
    }

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

        for (int i = 0; i < 10; i++)
        {
            processEntity(mesh, Entity(mesh, { Math::fRandom(-100, 100), Math::fRandom(-100, 100), -Math::fRandom(5, 105) }));
        }

        terrain = new Terrain();

        return true;
    }

    bool OnUserUpdate(sf::Time elapsed) override
    {
        camera.Update(elapsed, 10);

        shader.Bind();

        for (auto& entity : entity_map.at(mesh))
            entity.Rotate(0, 1, 1);

        shader.loadViewMatrix(&camera);
        renderer->Render(entity_map, &shader);

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