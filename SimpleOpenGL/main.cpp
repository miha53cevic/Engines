<<<<<<< HEAD
#include "window/window.h"
#include "gl/loadGL.h"

#include "Util/Cube.h"
#include "Util/Math.h"
=======
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
>>>>>>> b88c04865c5af579b78fd506340af003e86f84fa

int main()
{
    Window window(1280, 720, "My window");

    gl::Shader shader;
    shader.setAttribute(0, "position");
    shader.setAttribute(1, "textureCoords");
    
    shader.createProgram("glsl/shader1");

    shader.setUniformLocation("transformationMatrix");
    shader.setUniformLocation("projectionMatrix");
    shader.setUniformLocation("viewMatrix");

    gl::Texture texture;
    texture.loadTexture("Resources/textures/tex1.png");

    gl::VertexArray VAO;
    VAO.Bind();
    gl::ElementArrayBuffer EBO;
    EBO.setData(Cube::indicies);
    gl::VertexBufferObject VBO1, VBO2;
    VBO1.setData(Cube::verticies, 0, 3);
    VBO2.setData(Cube::textureCoords, 1, 2);
    VAO.Unbind();

    shader.Bind();
    shader.loadMatrix(shader.getUniformLocation("projectionMatrix"), Math::createProjectionMatrix(glm::vec2(window.ScreenWidth(), window.ScreenHeight()), 90, 0.1, 1000));
    shader.Unbind();

<<<<<<< HEAD
    Camera camera;
    
    bool running = true;
    while (running)
=======
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
>>>>>>> b88c04865c5af579b78fd506340af003e86f84fa
    {
        sf::Event e;
        while (window.getWindow()->pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                running = false;
            if (e.type == sf::Event::Resized)
                glViewport(0, 0, e.size.width, e.size.height);
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Q)
                running = false;
        }
<<<<<<< HEAD
=======
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
>>>>>>> b88c04865c5af579b78fd506340af003e86f84fa

        sf::Time elapsed = window.calculateElapsedTime();

        window.clear();

        // ...Drawing
        shader.Bind();

<<<<<<< HEAD
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.texture);

        camera.Update(elapsed, window.getWindow());
        shader.loadMatrix(shader.getUniformLocation("viewMatrix"), Math::createViewMatrix(&camera));
        VAO.Bind();
=======
        for (auto& entity : entity_map.at(mesh))
            entity.Rotate(0, 1, 1);

        shader.loadViewMatrix(&camera);
        renderer->Render(entity_map, &shader);
>>>>>>> b88c04865c5af579b78fd506340af003e86f84fa

        shader.loadMatrix(shader.getUniformLocation("transformationMatrix"), Math::createTransformationMatrix({ 0, 0, -2.0 }, { 0, 0, 0 }, { 1, 1 ,1 }));
        glDrawElements(GL_TRIANGLES, EBO.size, GL_UNSIGNED_INT, 0);
        VAO.Unbind();

        shader.Unbind();

        window.display();
    }

	return 0;
}