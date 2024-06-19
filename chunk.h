//
// Created by snake on 17/06/24.
//

#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H
#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

typedef struct {
    int count;
    int capacity;
    uint8_t* code;
    int* lines;
    int lineCount;
    int lineCapacity;
    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);
void freeChunk(Chunk* chunk);
int getLine(Chunk* chunk, int instructionIndex);

#endif //CLOX_CHUNK_H
