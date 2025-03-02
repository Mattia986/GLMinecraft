#include "shader.h"

unsigned int make_module(const char* filepath, unsigned int module_type) {
    std::ifstream file(filepath);
    if (!file) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return 0;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string shader_code = buffer.str();
    file.close();

    unsigned int shader = glCreateShader(module_type);
    const char* shader_code_cstr = shader_code.c_str();
    glShaderSource(shader, 1, &shader_code_cstr, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char info_log[1024];
        glGetShaderInfoLog(shader, 1024, NULL, info_log);
        std::cerr << "Couldn't load the shader correctly!\n" << info_log << std::endl;
        return 0;
    }

    return shader;
}

unsigned int make_shader(const char* vertexPath, const char* fragmentPath) {
    unsigned int vertexShader = make_module(vertexPath, GL_VERTEX_SHADER);
    unsigned int fragmentShader = make_module(fragmentPath, GL_FRAGMENT_SHADER);

    if (vertexShader == 0 || fragmentShader == 0) {
        std::cerr << "Shader compilation failed!" << std::endl;
        return 0;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        char info_log[1024];
        glGetProgramInfoLog(shaderProgram, 1024, NULL, info_log);
        std::cerr << "Couldn't link the program correctly!\n" << info_log << std::endl;
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
