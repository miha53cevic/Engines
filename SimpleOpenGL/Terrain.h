#pragma once
#include "Math.h"
#include "Shader.h"

class Terrain
{
public:
    Terrain()
    {
        pos = glm::vec3(-200, -20, -200);
        rot = glm::vec3(0, 0, 0);
        scale = 1.0f;

        const unsigned int SIZE = 400;
        const unsigned int VERTEX_COUNT = 128;

        int count = VERTEX_COUNT * VERTEX_COUNT;
        std::vector<GLfloat> vertices(count * 3);
        std::vector<GLfloat> normals(count * 3);
        std::vector<GLfloat> textureCoords(count * 2);
        std::vector<GLuint> indices(6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1));
        int vertexPointer = 0;
        for (int i = 0; i < VERTEX_COUNT; i++) {
            for (int j = 0; j < VERTEX_COUNT; j++) {
                vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
                vertices[vertexPointer * 3 + 1] = Math::fRandom(0.0f, 10.0f);
                vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
                normals[vertexPointer * 3] = 0;
                normals[vertexPointer * 3 + 1] = 1;
                normals[vertexPointer * 3 + 2] = 0;
                textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
                textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
                vertexPointer++;
            }
        }
        int pointer = 0;
        for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
            for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
                int topLeft = (gz*VERTEX_COUNT) + gx;
                int topRight = topLeft + 1;
                int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
                int bottomRight = bottomLeft + 1;
                indices[pointer++] = topLeft;
                indices[pointer++] = bottomLeft;
                indices[pointer++] = topRight;
                indices[pointer++] = topRight;
                indices[pointer++] = bottomLeft;
                indices[pointer++] = bottomRight;
            }
        }

        entity = std::make_unique<Entity>(std::make_unique<Mesh>(vertices, indices), pos, rot, scale);
        entity->getMesh()->addTexture("tex/grass.png", textureCoords);
    }

    glm::vec3 pos;
    glm::vec3 rot;
    float scale;

    EntityRef entity;

    std::vector<GLfloat> vertices;
    GLuint VAO;

    void Draw(Shader* shader)
    {
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);

        glBindVertexArray(entity->getMesh()->getVAO());

        glm::mat4x4 transformationMatrix = Math::createTransformationMatrix(entity->getPosition(), entity->getRotation(), entity->getScale());
        shader->loadTransformationMatrix(transformationMatrix);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, entity->getMesh()->getTexture());

        glDrawElements(GL_TRIANGLES, entity->getMesh()->getVertexCount(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }
};
