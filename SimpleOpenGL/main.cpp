#include "window/window.h"
#include "gl/loadGL.h"

#include "Util/Cube.h"
#include "Util/Math.h"

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

    Camera camera;
    
    bool running = true;
    while (running)
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

        sf::Time elapsed = window.calculateElapsedTime();

        window.clear();

        // ...Drawing
        shader.Bind();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.texture);

        camera.Update(elapsed, window.getWindow());
        shader.loadMatrix(shader.getUniformLocation("viewMatrix"), Math::createViewMatrix(&camera));
        VAO.Bind();

        shader.loadMatrix(shader.getUniformLocation("transformationMatrix"), Math::createTransformationMatrix({ 0, 0, -2.0 }, { 0, 0, 0 }, { 1, 1 ,1 }));
        glDrawElements(GL_TRIANGLES, EBO.size, GL_UNSIGNED_INT, 0);
        VAO.Unbind();

        shader.Unbind();

        window.display();
    }

	return 0;
}