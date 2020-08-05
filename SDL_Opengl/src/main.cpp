#include "app.h"
#include "entity.h"
#include "math.h"
#include "cube.h"

class Woxel : public App
{
public:
    Woxel(const char* title, int width, int height)
        : App(title, width, height)
    {}

private:
    virtual bool Event(SDL_Event& e) override
    {
        return true;
    }
    virtual bool Setup() override
    {
        shader.setAttribute(0, "position");
        shader.setAttribute(1, "textureCoords");
        shader.createProgram("resources/shaders/shader");

        shader.setUniformLocation("MVPMatrix");

        cube.texture.loadTexture("resources/textures/plank_draft.png");
        cube.position = glm::vec3(-0.5f, -0.5f, -2);
        cube.setEBO(Cube::indicies);
        cube.setVBO(Cube::verticies, 0, 3);
        cube.setVBO(Cube::textureCoords, 1, 2);

        setClearColor(255, 255, 255, 255);

        return true;
    }
    virtual bool Loop(float elapsed) override
    {
        RenderEntity(cube, shader);
        return true;
    }

private:
    void RenderEntity(Entity& e, gl::Shader& s)
    {
        s.Bind();

        cube.texture.activateAndBind();
        shader.loadMatrix(
            shader.getUniformLocation("MVPMatrix"),
            Math::createMVPMatrix(glm::vec2(ScreenWidth(), ScreenHeight()), 90, 0.1f, 100.0f, camera, cube)
        );

        e.VAO.Bind();
        glDrawElements(GL_TRIANGLES, e.EBO.size, GL_UNSIGNED_INT, 0);
        e.VAO.Unbind();

        s.Unbind();
    }

private:
    Entity cube;
    gl::Shader shader;
    Camera camera;
};

int main(int argc, char* argv[])
{
    Woxel game("Woxel", 640, 480);
    game.Run();
    return 0;
}