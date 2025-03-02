#include "block.h"

Block::Block(float l, float w, float h, unsigned int shader){

    std::vector<float> vertices = {
        // Front Face
         l,  w, -h, 1.0f, 1.0f,  
         l, -w, -h, 1.0f, 0.0f,  
        -l, -w, -h, 0.0f, 0.0f,  
        -l,  w, -h, 0.0f, 1.0f,  
    
        // Back Face
        -l,  w,  h, 1.0f, 1.0f,  
        -l, -w,  h, 1.0f, 0.0f,  
         l, -w,  h, 0.0f, 0.0f,  
         l,  w,  h, 0.0f, 1.0f,  
    
        // Left Face
        -l,  w, -h, 1.0f, 1.0f,  
        -l, -w, -h, 1.0f, 0.0f,  
        -l, -w,  h, 0.0f, 0.0f,  
        -l,  w,  h, 0.0f, 1.0f,  
    
        // Right Face
         l,  w,  h, 1.0f, 1.0f,  
         l, -w,  h, 1.0f, 0.0f,  
         l, -w, -h, 0.0f, 0.0f,  
         l,  w, -h, 0.0f, 1.0f,  
    
        // Top Face
        -l,  w,  h, 1.0f, 1.0f,  
        -l,  w, -h, 1.0f, 0.0f,  
         l,  w, -h, 0.0f, 0.0f,  
         l,  w,  h, 0.0f, 1.0f,  
    
        // Bottom Face
        -l, -w, -h, 1.0f, 1.0f,  
        -l, -w,  h, 1.0f, 0.0f,  
         l, -w,  h, 0.0f, 0.0f,  
         l, -w, -h, 0.0f, 1.0f  
    };

    std::vector<int> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void*)12);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Block::draw(){
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

Block::~Block(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}