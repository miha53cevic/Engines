#include "SimpleOpenGL.h"

#include "Static_Shader.h"
#include "Entity.h"
#include "Renderer.h"

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

protected:
    void Event(sf::Event& e) override
    {
    }

    bool OnUserCreate() override
    {
        EnableFPSCounter(true);
        EnableVSync(true);

        // Go counter-clockwise in OpenGL
        /*std::vector<GLfloat> data = {
            -0.5f,  0.5f, 0.0f, //v0
            -0.5f, -0.5f, 0.0f, //v1
             0.5f, -0.5f, 0.0f, //v2
             0.5f,  0.5f, 0.0f  //v3
        };

        std::vector<GLuint> indicies = {
            0,1,3,
            3,1,2
        };

        std::vector<GLfloat> textureCoords = {
            0, 0,
            0, 1,
            1, 1,
            1, 0
        };*/

        std::vector<GLfloat> cubeData = {
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,

            -0.5f,  0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
             0.5f, -0.5f, 0.5f,
             0.5f,  0.5f, 0.5f,

             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,

            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            -0.5f, 0.5f,  0.5f,
            -0.5f, 0.5f, -0.5f,
             0.5f, 0.5f, -0.5f,
             0.5f, 0.5f,  0.5f,

            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f
        };

        std::vector<GLuint> Cubeindicies = {
            0,1,3,
            3,1,2,
            4,5,7,
            7,5,6,
            8,9,11,
            11,9,10,
            12,13,15,
            15,13,14,
            16,17,19,
            19,17,18,
            20,21,23,
            23,21,22
        };

        std::vector<GLfloat> CubetextureCoords = {
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0
        };

        // Primjena napomene gore navedene
        //entity = std::make_unique<Entity>(std::make_unique<Mesh>(cubeData, Cubeindicies), glm::vec3(0,0,-1.5f), glm::vec3(0,0,0), 1);

        // Add texture to the mesh
        //entity->getMesh()->addTexture("tex/sample.png", CubetextureCoords);

        entity = std::make_unique<Entity>("obj/Cube", "tex/Cube.png", glm::vec3(0, 0, -5.0f), glm::vec3(0, 0, 0), 1);

        shaderProgram = std::make_unique<Static_Shader>();
        shaderProgram->createProgram("shaders/texture_shader");

        renderer = std::make_unique<Renderer>(glm::vec2(ScreenWidth(), ScreenHeight()), shaderProgram);

        camera = std::make_unique<Camera>();

        return true;
    }

    bool OnUserUpdate(sf::Time elapsed) override
    {
        entity->Rotate(-100 * elapsed.asSeconds(), -100 * elapsed.asSeconds(), 0);
        //entity->Rotate(0, -100 * elapsed.asSeconds(), 0);

        camera->Update(elapsed, 10.0f);

        shaderProgram->Bind();
       
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