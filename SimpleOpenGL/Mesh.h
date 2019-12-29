#pragma once
#include <vector>
#include <string>

#include <glad/glad.h>
#include <SFML/Graphics.hpp>

#include "OBJ_Loader.h"

class Mesh
{
public:
    Mesh(std::vector<GLfloat>& verticies, std::vector<GLuint>& indicies)
    {
        Setup(verticies, indicies);
    }

    Mesh(std::string obj_path, std::string texture_path)
    {
        objl::Loader loader;
        loader.LoadFile(obj_path);

        std::vector<GLfloat> verticies;
        std::vector<GLuint>  indicies;
        std::vector<GLfloat> textureCoords;
        std::vector<GLfloat> normals;

        for (auto& vertex : loader.LoadedMeshes[0].Vertices)
        {
            verticies.push_back(vertex.Position.X);
            verticies.push_back(vertex.Position.Y);
            verticies.push_back(vertex.Position.Z);

            textureCoords.push_back(vertex.TextureCoordinate.X);
            textureCoords.push_back(1.0f - vertex.TextureCoordinate.Y);

            normals.push_back(vertex.Normal.X);
            normals.push_back(vertex.Normal.Y);
            normals.push_back(vertex.Normal.Z);
        }

        for (auto& indicie : loader.LoadedMeshes[0].Indices)
        {
            indicies.push_back(indicie);
        }

        Setup(verticies, indicies);
        addTextureCoords(texture_path, textureCoords);
        addNormals(normals);
    }

    ~Mesh()
    {
        printf("Mesh: Deconstructor!\n");

        // Delete VBOs
        for (auto& vbo : m_VBOs)
        {
            glDeleteBuffers(1, &vbo);
        }

        // Delete VAO
        glDeleteVertexArrays(1, &VAO);

        // Delete Textures
        for (auto& texture : m_textures)
        {
            glDeleteTextures(1, &texture);
        }
    }

    void addTextureCoords(std::string texture_path, std::vector<GLfloat>& textureCoords)
    {
        bindVAO();
        storeDataInAttributeList(1, 2, textureCoords);
        unbindVAO();

        loadTexture(texture_path);
    }

    void addNormals(std::vector<GLfloat>& normals)
    {
        bindVAO();
        storeDataInAttributeList(2, 3, normals);
        unbindVAO();
    }

    int getVertexCount() { return m_vertexCount; }

    GLuint VAO;
    GLuint TextureID;

private:
    std::vector<GLuint> m_VBOs;
    std::vector<GLuint> m_textures;
    int m_vertexCount;

    void Setup(std::vector<GLfloat>& verticies, std::vector<GLuint>& indicies)
    {
        m_vertexCount = indicies.size();

        // Create VAO
        glGenVertexArrays(1, &VAO);
        bindVAO();

        bindIndiciesBuffer(indicies);
        storeDataInAttributeList(0, 3, verticies);

        unbindVAO();
    }

    void bindIndiciesBuffer(std::vector<GLuint>& indicies)
    {
        GLuint EBO;
        glGenBuffers(1, &EBO);
        m_VBOs.push_back(EBO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indicies.size(), indicies.data(), GL_STATIC_DRAW);
    }

    void storeDataInAttributeList(int attributeID, int size, std::vector<GLfloat>& data)
    {
        GLuint VBO;
        glGenBuffers(1, &VBO);
        m_VBOs.push_back(VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(attributeID);
        glVertexAttribPointer(attributeID, size, GL_FLOAT, GL_FALSE, 0, 0);

        // Unbind VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void loadTexture(std::string texture_path)
    {
        // Load the texture
        sf::Image img;
        if (!img.loadFromFile(texture_path))
        {
            // Error
            TextureID = -1;
        }
        else
        {
            glGenTextures(1, &TextureID);
            glBindTexture(GL_TEXTURE_2D, TextureID);

            // Store for cleanup later
            m_textures.push_back(TextureID);

            // Send texture data to the GPU
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());

            // Must add these otherwise the texture doesn't load
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
    }

    void bindVAO()   { glBindVertexArray(VAO); }
    void unbindVAO() { glBindVertexArray(0);   }
};