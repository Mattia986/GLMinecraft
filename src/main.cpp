#include "config.h"
#include "shaders/shader.h"
#include "mesh/block.h"
#include "textures/texture.h"
#include "components/transform.h"
#include "camera/camera.h"
#include "world_generation/chunk.h"

int main() {

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL Craft", NULL, NULL);

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    unsigned int shader = make_shader("../../src/shaders/vertex.txt", "../../src/shaders/fragment.txt");

    TransformComponent block_trans;
    block_trans.position = {0.0f, 0.0f, 0.0f};

    //Block* cube = new Block(1.0f, 1.0f, 1.0f, shader, block_trans);

    Chunk* chunk = new Chunk(block_trans, shader);

    std::vector<TransformComponent>* transformComponents;

    TransformComponent cameraComponent;
    cameraComponent.position = {1.0f, 2.0f, 2.0f};
    cameraComponent.rotation = {0.0f, 0.0f, -90.0f};

    glUseProgram(shader);
    glUniform1i(glGetUniformLocation(shader, "texSampler"), 0);
    unsigned int proj_loc = glGetUniformLocation(shader, "proj");

    Texture* auvova = new Texture("../../img/pop.jpg");

    Camera* camera = new Camera(shader, window, cameraComponent, 0.2f, 0.1f);

    glm::mat4 projection = glm::perspective(
		45.0f, 1280.0f / 720.0f, 0.1f, 30.0f);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDisable(GL_CULL_FACE);

    glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        camera->update();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader);
        
        auvova->use(0);
        chunk->draw();
        //cube->draw();
        glfwSwapBuffers(window);
    }
    

    glfwTerminate();
    delete chunk;
    return 0;
}