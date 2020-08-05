#include "math.h"
#include "entity.h"

Camera::Camera()
    : m_position(glm::vec3(0, 0, 0))
    , m_rotation(glm::vec3(0, 0, 0))
{
}

void Camera::Update(SDL_Window * win, float sens)
{
    // Get the offset between mouse movements then add them to rotation
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int w, h;
    SDL_GetWindowSize(win, &w, &h);
    int screenCenterW = w / 2;
    int screenCenterH = h / 2;

    if (SDL_GetWindowFlags(win) == SDL_WINDOW_MOUSE_FOCUS)
    {
        float xOffset = mouseX - screenCenterW;
        float yOffset = mouseY - screenCenterH;

        xOffset *= sens;
        yOffset *= sens;

        m_rotation.x += yOffset;
        m_rotation.y += xOffset;

        // Set max up/down rotation
        if (m_rotation.x > 90.0f)
            m_rotation.x = 90.0f;

        if (m_rotation.x < -90.0f)
            m_rotation.x = -90.0f;

        // Set mouse position to the center of the screen
        if (xOffset != 0 || yOffset != 0)
            SDL_WarpMouseInWindow(win, screenCenterW, screenCenterH);
    }
}

glm::vec3 Camera::getPosition()
{
    return m_position;
}

glm::vec3 Camera::getRotation()
{
    return m_rotation;
}

void Camera::updatePosition(glm::vec3 position)
{
    m_position = position;
}

void Camera::updateRotation(glm::vec3 rotation)
{
    m_rotation = rotation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

glm::mat4x4 Math::createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
{
    // Set identity matrix
    glm::mat4x4 matrix = glm::mat4x4(1.0f);
    matrix = glm::translate(matrix, translation);
    matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    matrix = glm::scale(matrix, scale);

    return matrix;
}

glm::mat4x4 Math::createProjectionMatrix(glm::vec2 screenSize, float FOV, float NEAR_PLANE, float FAR_PLANE)
{
    return glm::perspective(glm::radians(FOV), (screenSize.x / screenSize.y), NEAR_PLANE, FAR_PLANE);
}

glm::mat4x4 Math::createViewMatrix(Camera& camera)
{
    // The camera never moves the world moves opposite of the camera
    glm::mat4x4 view = glm::mat4x4(1.0f);

    view = glm::rotate(view, glm::radians(camera.getRotation().x), glm::vec3(1, 0, 0));
    view = glm::rotate(view, glm::radians(camera.getRotation().y), glm::vec3(0, 1, 0));
    view = glm::rotate(view, glm::radians(camera.getRotation().z), glm::vec3(0, 0, 1));
    view = glm::translate(view, -camera.getPosition());

    return view;
}

glm::mat4x4 Math::createMVPMatrix(glm::vec2 screenSize, float FOV, float NEAR_PLANE, float FAR_PLANE, Camera & camera, Entity & entity)
{
    // MVP Matrix = Projection * View * Model(transformation matrix)
    return (
        createProjectionMatrix(screenSize, FOV, NEAR_PLANE, FAR_PLANE) * 
        createViewMatrix(camera) * 
        createTransformationMatrix(entity.position, entity.rotation, entity.scale)
        );
}

float Math::fRandom(float first, float second)
{
    std::random_device rd;
    std::default_random_engine generator(rd()); // rd() provides a random seed
    std::uniform_real_distribution<float> distribution(first, second);

    return distribution(generator);
}

int Math::iRandom(int first, int second)
{
    std::random_device rd;
    std::default_random_engine generator(rd()); // rd() provides a random seed
    std::uniform_int_distribution<int> distribution(first, second);

    return distribution(generator);
}

float Math::map(float s, float a1, float a2, float b1, float b2)
{
    return b1 + ((s - a1) * (b2 - b1)) / (a2 - a1);
}

float Math::simplex2(float x, float y, int octaves, float persistence, float lacunarity)
{
    float freq = 1.0f;
    float amp = 1.0f;
    float max = 1.0f;
    float total = glm::simplex(glm::vec2(x, y));
    int i;
    for (i = 1; i < octaves; i++) {
        freq *= lacunarity;
        amp *= persistence;
        max += amp;
        total += glm::simplex(glm::vec2(x * freq, y * freq)) * amp;
    }
    // Map from [-1, 1] to [0, 1]
    return (1 + total / max) / 2;
}

float Math::simplex3(float x, float y, float z, int octaves, float persistence, float lacunarity)
{
    float freq = 1.0f;
    float amp = 1.0f;
    float max = 1.0f;
    float total = glm::simplex(glm::vec3(x, y, z));
    int i;
    for (i = 1; i < octaves; ++i) {
        freq *= lacunarity;
        amp *= persistence;
        max += amp;
        total += glm::simplex(glm::vec3(x * freq, y * freq, z * freq)) * amp;
    }
    // Map from [-1, 1] to [0, 1]
    return (1 + total / max) / 2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Raycasting reference
// https://github.com/Hopson97/MineCraft-One-Week-Challenge/blob/master/Source/Maths/Ray.cpp

Math::Ray::Ray(const glm::vec3 & position, const glm::vec3 & direction)
    : m_rayStart(position)
    , m_rayEnd(position)
    , m_direction(direction)
{
}

void Math::Ray::step(float scale)
{
    float yaw = glm::radians(m_direction.y + 90); // no clue why + 90
    float pitch = glm::radians(m_direction.x);

    m_rayEnd.x -= glm::cos(yaw) * glm::cos(pitch) * scale;
    m_rayEnd.z -= glm::sin(yaw) * glm::cos(pitch) * scale;
    m_rayEnd.y -= glm::sin(pitch)                 * scale;

    // Moguce samo podijeliti cijeli vektor sa glm::cos(pitch) pa se dobije drugacija formula
    /*
        m_rayEnd.x -= glm::cos(yaw)   * scale;
        m_rayEnd.z -= glm::sin(yaw)   * scale;
        m_rayEnd.y -= glm::tan(pitch) * scale;
    */
}

const glm::vec3 & Math::Ray::getEnd() const
{
    return m_rayEnd;
}

float Math::Ray::getLength() const
{
    return glm::distance(m_rayStart, m_rayEnd);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////