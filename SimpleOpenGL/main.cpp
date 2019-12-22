#include "SimpleOpenGL.h"

#include "Static_Shader.h"
#include "Mesh.h"

class OpenGL : public SimpleOpenGL
{
public:
    OpenGL()
    {
    }

private:
    std::unique_ptr<Mesh> mesh;
    std::unique_ptr<Static_Shader> shaderProgram;

protected:
    void Event(sf::Event& e) override
    {
    }

    bool OnUserCreate() override
    {
        EnableFPSCounter(true);
        EnableVSync(true);

        // Go counter-clockwise in OpenGL
        std::vector<GLfloat> data = {
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
        };

        mesh = std::make_unique<Mesh>(data, indicies);
        mesh->addTexture("tex/sample.png", textureCoords);
        shaderProgram = std::make_unique<Static_Shader>();
        shaderProgram->createProgram("shaders/texture_shader");

        return true;
    }

    bool OnUserUpdate(sf::Time elapsed) override
    {
        shaderProgram->Bind();
        mesh->Draw();
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