#pragma once
#include <stdbool.h>
#include <iostream>
#include <string>

#define BYTE_LIMIT 255
#define MAX_SIZE 65535

// Increment byte at pointer
void increment(int* ptr, int max);
// Decrement byte at pointer
void decrement(int *ptr, int max);
// Output byte at pointer
void outputByte(int *ptr);
// Input byte into pointer
void inputByte(int *ptr);

class Interpreter {
public:
    Interpreter();
    Interpreter(const char* path);
    ~Interpreter();

    int dataPointer;
    int data[MAX_SIZE];
    int instructionPointer;
    unsigned long cyclesElapsed = 0;
    char instruction[MAX_SIZE];
    bool hasCode;
    std::string s_Path;
    
    void appendPath(const char* path);
    void step(char c);
    void interpret();
private:
    char c;
    FILE *f;
    int i;
    int bracketCounter;
};
