//
// Created by snake on 17/06/24.
//

#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->lineCapacity = 0;
    chunk->lineCount = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }
    if (chunk->lineCapacity < chunk->lineCount + 2 ) {
        int oldCapacity = chunk->lineCapacity;
        chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->lineCapacity);
    }
    chunk->code[chunk->count] = byte;
    chunk->count++;
    if (chunk->lineCount == 0 || line != chunk->lines[chunk->lineCount - 2]) {
        chunk->lines[chunk->lineCount] = line;
        chunk->lines[chunk->lineCount + 1] = 1;
        chunk->lineCount += 2;
    }
    else if (chunk->lines[chunk->lineCount - 2] == line) {
        chunk->lines[chunk->lineCount - 1]++;
    }
}

int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

int getLine(Chunk* chunk, int instructionIndex) {
    int i, counter = 0;
    for (i = 1; i < chunk->lineCapacity; i+=2) {
        counter += chunk->lines[i];
        if (counter >= instructionIndex + 1) return chunk->lines[i - 1];
    }
}