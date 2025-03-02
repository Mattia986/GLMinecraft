#include "chunk.h"

Chunk::Chunk(TransformComponent transform, unsigned int shader){
    this->transform = transform;
    this->shader = shader;
    this->block = new Block(0.5, 0.5f, 0.5f, shader);

    for(int x = 0; x < CHUNK_WIDTH; x++){
        for(int y = 0; y < CHUNK_DEPTH; y++){
            for(int z = 0; z < CHUNK_HEIGHT; z++){
                glm::mat4 model = glm::mat4(1.0f);
                glm::vec3 position = transform.position + glm::vec3((float)x, (float)y, (float)z);
                model = glm::translate(model, position);

                block_poss[x][y][z] = model;          
            }
        }
    }

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (CHUNK_DEPTH*CHUNK_HEIGHT*CHUNK_WIDTH) * sizeof(glm::mat4), &block_poss[0], GL_STATIC_DRAW);

    unsigned int VAO = block->VAO;
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    glBindVertexArray(0);
}

Chunk::~Chunk(){
    /*for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int y = 0; y < CHUNK_DEPTH; y++) {
            for (int z = 0; z < CHUNK_HEIGHT; z++) {
                blocks[x][y][z] = nullptr;
            }
        }
    }*/
}

void Chunk::draw(){
    glBindVertexArray(block->VAO);
    glDrawElementsInstanced(
        GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, (CHUNK_DEPTH*CHUNK_HEIGHT*CHUNK_WIDTH)
    );
}