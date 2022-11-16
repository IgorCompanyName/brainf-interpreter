#include "bfd.hpp"

Debugger::Debugger() {
    i = Interpreter();
    task = false;
}
Debugger::~Debugger() {
    task = false;
}
Debugger::Debugger(const char* path) {
    start(path);
}
void Debugger::showNearestCells() {
    int ptr_2 = i.dataPointer;
    printf("\n[..][..] [%d] [..][..]\n\n", ptr_2);
}
void Debugger::showCode() {
    printf("%s\n", i.instruction);
}
void Debugger::start(const char* path) {
    i = Interpreter(path);
    task = i.hasCode;
}
void Debugger::end() {
    printf("Debugging of '%s' ended.\n", i.s_Path.c_str());
    printf("%lu cycles elapsed.\n", i.cyclesElapsed);
    i = Interpreter();
    task = false;
}
void Debugger::step() {
    char c;
    c = i.instruction[i.instructionPointer];
    if(c != '\0')
        i.step(c);
    else
        end();
}
void Debugger::interpret() {
    i.interpret();
    end();
}
