# Brainf*ck interpreter and debugger

## Overview

This project is done in C++. It's a small debugger as well as an interpreter
for [Brainf*ck esoteric language](https://en.wikipedia.org/wiki/Brainfuck
"Brainf*ck wikipedia").

## Compilation

For windows, just download release files and use them within the command line
or PowerShell.

For Linux use compilation from source.

### Compile from source / Linux

To compile this you will need to have gcc/clang or any other C++ compiler and
CMake already installed on your computer.

To configure cmake and compile Debug build use:

```bash
# Make sure you are in a root folder of a project
# Configure, you won't need to run this line more than once, unless
# you change CMakeLists.txt
cmake -DCMAKE_BUILD_TYPE:STRING=Debug

# Compile
cmake --build --config Debug --target all --
```

And with that you get two files: `build/src/brainf` and `build/src/braind`.

Now you can use brainf*ck interpreter and debugger!

## Usage

To use executable you compiled or downloaded and write:

```bash
# Interpreter
brainf <filename>

# Debugger
braind <filename or nothing>
```

## Special thanks

Thanks to random people of the internet that helped me come up with this
idea!
