# Brainf*ck interpreter and debugger

## Overview

This project is done in c++. It's a small debugger as well as an interpreter 
for [Brainf*ck esoteric language](https://en.wikipedia.org/wiki/Brainfuck
"Brainf*ck wikipedia").

## How to use

### Windows

For windows, just download release files and use them within the command line
or PowerShell.

### Linux

Before compilation, you need to download C/C++. If you have it already, then
skip this step, but for anyone who doesn't have g++, here:

```bash
# Ubuntu / Debian
sudo apt install g++ -y

# Fedora
sudo dnf install gcc-c++

# Arch
sudo pacman -S g++

# For any other distributions look it up in google
```

Next we need to compile it. It's easy to do, just go to the folder end enter:

```bash
./compile-x86_64.sh
```

And with that you get two files: `brainf` and `braind`.

## This is it!

Now you can use brainf*ck interpreter and debugger!
