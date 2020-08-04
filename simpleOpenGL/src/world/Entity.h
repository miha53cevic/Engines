#pragma once
#include "../gl/glObjects.h"
#include <memory>

typedef std::unique_ptr<gl::VertexBufferObject> VBORef;

struct Entity
{
    Entity();
    ~Entity();

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    gl::VertexArray VAO;
    gl::ElementArrayBuffer EBO;

    void setEBO(const std::vector<GLuint>& indicies, int DrawMode = GL_STATIC_DRAW);
    void setVBO(const std::vector<GLfloat>& data, int attributeID, int size, int DrawMode = GL_STATIC_DRAW);

    void updateEBO(const std::vector<GLuint>& indicies);
    void updateVBO(const std::vector<GLfloat>& data, int index);

    void draw(int mode = GL_TRIANGLES, int type = GL_UNSIGNED_INT, const void* indicies = 0);

    std::vector<VBORef> VBOs;

    void loadObj(std::string path);
};

