#include <stdio.h>
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    int constant2 = addConstant(&chunk, 42);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant2, 123);
    writeChunk(&chunk, OP_RETURN, 124);
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);
    return 0;
}
