#pragma once
#include "bfc.hpp"

class Debugger {
public:
    Debugger();
    Debugger(const char* path);
    ~Debugger();

    Interpreter i;
public:
    void showNearestCells();
    void showCode();
    void step();
    void end();
    void start(const char* path);
    void interpret();

    bool task;
};
