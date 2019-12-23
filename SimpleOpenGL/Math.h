#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Math
{
public:
    Math() {}

    glm::mat4x4 static createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale)
    {
        // Set identity matrix
        glm::mat4x4 matrix = glm::mat4x4(1.0f);
        matrix = glm::translate(matrix, translation);
        matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
        matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));

        return matrix;
    }

    glm::mat4x4 static createProjectionMatrix(glm::vec2 screenSize, float FOV, float NEAR_PLANE, float FAR_PLANE)
    {
        return glm::perspective(FOV, (screenSize.x / screenSize.y), NEAR_PLANE, FAR_PLANE);
    }

private:
};

