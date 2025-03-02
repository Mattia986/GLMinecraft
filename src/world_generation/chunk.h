#define CHUNK_HEIGHT 16
#define CHUNK_DEPTH 16
#define CHUNK_WIDTH 16

#include "../config.h"
#include "../components/transform.h"
#include "../mesh/block.h"

class Chunk{
    public:
    Chunk(TransformComponent transform, unsigned int shader);
    ~Chunk();
    void draw();

    private:
    glm::mat4 block_poss[CHUNK_WIDTH][CHUNK_DEPTH][CHUNK_HEIGHT];
    unsigned int shader;
    Block* block;
    unsigned int VBO;
    TransformComponent transform;
};
