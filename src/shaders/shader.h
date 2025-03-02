#pragma once
#include "../config.h"

unsigned int make_module(const char* filepath, unsigned int module_type);

unsigned int make_shader(const char* vertexPath, const char* fragmentPath);
