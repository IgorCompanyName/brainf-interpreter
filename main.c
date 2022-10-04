#include <stdbool.h>
#include <stdio.h>

#define BYTE_LIMIT 255
#define MAX_SIZE 65535

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

int main (int argc, char *argv[]) {
    int dataPointer;
    int data[MAX_SIZE];
    int instructionPointer;
    char instruction[MAX_SIZE];
    int bracketCounter;
    int i;
    char c;
    FILE *f;

    if (argc < 2) {
        puts("No filename provided for input.");
        return 1;
    }

    f = fopen(argv[1], "r");

    // Zero out all memory in all arrays
    for (i = 0; i < MAX_SIZE; i++) {
        data[i] = 0;
        instruction[i] = '\0';
    }

    // Load all commands into memory
    instructionPointer = 0;
    while ((c = fgetc(f)) != EOF) {
        instruction[instructionPointer] = c;
        instructionPointer++;
    }

    fclose(f);

    dataPointer = 0;
    instructionPointer = 0;
    bracketCounter = 0;

    while ((c = instruction[instructionPointer]) != '\0') {
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
                            return 1;
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
                            return 1;
                        }

                        continue;
                    }
                }
                break;
        }
        instructionPointer++;
    }

    return 0;
}
