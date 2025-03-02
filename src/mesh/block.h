#pragma once
#include "../config.h"
#include "../components/transform.h"

class Block{
    public:
    Block(float l, float w, float h, unsigned int shader);
    void draw();
    unsigned int VAO, EBO, VBO;
    ~Block();
};
