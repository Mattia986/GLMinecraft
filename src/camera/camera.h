#pragma once
#include "../config.h"
#include "../components/transform.h"

class Camera{
    public:
    Camera(unsigned int shader, GLFWwindow* window, TransformComponent camera_trans, float cam_speed, float sensitivity);
    void update();

    private:
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 forwards;

    glm::vec3 global_up = {0.0f, 0.0f, 1.0f};
    GLFWwindow* window;
    unsigned int view_loc;
    TransformComponent transform;
    float speed;
    float sensitivity;
};