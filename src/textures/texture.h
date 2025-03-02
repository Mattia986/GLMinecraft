#pragma once
#include "../config.h"

class Texture{
    public:
    Texture(const char* filepath);
    ~Texture();
    void use(int unit);
    private:
    unsigned int texture;
};