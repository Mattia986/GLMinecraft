#include "camera.h"

Camera::Camera(unsigned int shader, GLFWwindow* window, TransformComponent camera_trans, float cam_speed, float sensitivity){
    this->window = window;
    this->transform = camera_trans;
    this->speed = cam_speed;
    this->sensitivity = sensitivity;

    glUseProgram(shader);
    this->view_loc = glGetUniformLocation(shader, "view");
}

void Camera::update(){
    float theta = glm::radians(transform.rotation.z);
    float phi = glm::radians(transform.rotation.y);

    forwards = {
        glm::cos(theta) * glm::cos(phi),
        glm::sin(theta) * glm::cos(phi),
        glm::sin(phi)
    };

    this->right = glm::normalize(glm::cross(forwards, global_up));
    this->up = glm::normalize(glm::cross(right, forwards));

	glm::mat4 view = glm::lookAt(this->transform.position, this->transform.position+forwards, up);

    glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        this->transform.position += speed*forwards;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        this->transform.position -= speed*forwards;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        this->transform.position -= speed*right;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    this->transform.position += speed*right;

    glm::vec3 dEulers = {0.0f, 0.0f, 0.0f};
    double mouse_x, mouse_y;

    int window_w, window_h;
    glfwGetWindowSize(window, &window_w, &window_h);
    glfwGetCursorPos(window, &mouse_x, &mouse_y);
    glfwSetCursorPos(window, (float)window_w/2.0f, (float)window_h/2.0f);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents();

    dEulers.z = -this->sensitivity * static_cast<float>(mouse_x - (float)window_w/2.0f);
    dEulers.y = -this->sensitivity * static_cast<float>(mouse_y - (float)window_h/2.0f);

    this->transform.rotation.y = fminf(89.0f, fmaxf(-89.0f, this->transform.rotation.y + dEulers.y));

    this->transform.rotation.z += dEulers.z;
    if (this->transform.rotation.z > 360) {
        this->transform.rotation.z -= 360;
    }
    else if (this->transform.rotation.z < 0) {
        this->transform.rotation.z += 360;
    }

}