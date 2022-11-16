#include "bfc.hpp"

void increment(int *ptr, int max) {
    if (*ptr == max) {
        *ptr = 0;
    } else {
        (*ptr)++;
    }
};

void decrement(int *ptr, int max) {
    if (*ptr == 0) {
        *ptr = max;
    } else {
        (*ptr)--;
    }
}

void outputByte(int *ptr) {
    printf("%c", *ptr);
}

void inputByte(int *ptr) {
    *ptr = getchar();
}

Interpreter::Interpreter() {
    hasCode = false;
    s_Path = "";
    dataPointer = 0;
    instructionPointer = 0;
    bracketCounter = 0;
}

Interpreter::Interpreter(const char* path) {
    f = fopen(path, "r");

    for(i = 0; i < MAX_SIZE; i++) {
        data[i] = 0;
        instruction[i] = '\0';
    }
    instructionPointer = 0;
    while((c = fgetc(f)) != EOF) {
        instruction[instructionPointer] = c;
        instructionPointer++;
    }
    fclose(f);

    dataPointer = 0;
    instructionPointer = 0;
    bracketCounter = 0;

    s_Path = path;
    hasCode = true;
}
void Interpreter::step(char c) {
    switch (c) {
        case '>':
            increment(&dataPointer, MAX_SIZE);
            break;
        case '<':
            decrement(&dataPointer, MAX_SIZE);
            break;
        case '+':
            increment(&data[dataPointer], BYTE_LIMIT);
            break;
        case '-':
            decrement(&data[dataPointer], BYTE_LIMIT);
            break;
        case '.':
            outputByte(&data[dataPointer]);
            break;
        case ',':
            inputByte(&data[dataPointer]);
            break;
        case '[':
            if (data[dataPointer] == 0) {
                instructionPointer++;

                while (true) {
                    c = instruction[instructionPointer];

                    if (c == EOF) {
                        fputs("Unmatched brackets", stderr);
                        exit(EXIT_FAILURE);
                    }

                    if (c == ']' && bracketCounter == 0) {
                        break;
                    } else if (c == ']') {
                        bracketCounter--;
                    } else if (c == '[') {
                        bracketCounter++;
                    }

                    instructionPointer++;
                }
            }
            break;
        case ']':
            if (data[dataPointer] != 0) {
                instructionPointer--;

                while (true) {
                    c = instruction[instructionPointer];

                    if (c == '[' && bracketCounter == 0) {
                        break;
                    } else if (c == '[') {
                        bracketCounter--;
                    } else if (c == ']') {
                        bracketCounter++;
                    }

                    instructionPointer--;

                    if (instructionPointer == -1) {
                        fputs("Unmatched brackets", stderr);
                        exit(EXIT_FAILURE);
                    }

                    continue;
                }
            }
            break;
    }
    instructionPointer++;
}
void Interpreter::interpret() {
    while((c = instruction[instructionPointer]) != '\0') {
        step(c);
    }
}
Interpreter::~Interpreter() {
    
}
void Interpreter::appendPath(const char* path) {
    f = fopen(path, "r");

    for(i = 0; i < MAX_SIZE; i++) {
        data[i] = 0;
        instruction[i] = '\0';
    }
    instructionPointer = 0;
    while((c = fgetc(f)) != EOF) {
        instruction[instructionPointer] = c;
        instructionPointer++;
    }
    fclose(f);

    dataPointer = 0;
    instructionPointer = 0;
    bracketCounter = 0;

    s_Path = path;
    hasCode = true;
}