#include "bfc.hpp"

int main(int argc, char** argv) {
    if(argc < 2)
    {
        printf("No input file specified!\n");
        return 1;
    }
    Interpreter interpreter(argv[1]);
    interpreter.interpret();
}