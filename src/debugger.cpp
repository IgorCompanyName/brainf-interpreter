#include "bfc.hpp"
#include "bfd.hpp"
#include <string.h>
#include <sstream>
#include <iterator>
#include <vector>

int main(int argc, char* argv[]) {
    std::cout << "\nWelcome to BrainF*ck debugger! \nTo get a list of"
    " all commands, simply write 'help'.\n\n";

    Debugger d;
    if(argc >= 2) {
        d.start(argv[1]);
        std::cout << "Opened file '" << argv[1] << "'\n\n";
    }
    // TODO: Add more commands for debuggind brainfuck
    while(true) {
        if(d.i.s_Path != "")
            std::cout << " (" << d.i.s_Path << ") >>> ";
        else
            std::cout << " (bfd) >>> ";
        std::string temp;

        getline(std::cin, temp);
        if(temp.find_first_not_of(' ') == std::string::npos)
            continue;
    
        std::stringstream ss(temp);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> args(begin, end);
        std::string cmd = args[0];

        if(cmd == "exit" || cmd == "q") {
            break;
        } else if(cmd == "step" || cmd == "s") {
            if(!d.task) {
                printf("Open file to debug: 'open <filename>'\n");
                continue;
            }
            if(args.size() < 2) {
                d.step();
                printf("Stepped to char '%c' at %d\n", 
                d.i.instruction[d.i.instructionPointer], 
                d.i.instructionPointer); 
            } else {
                std::string arg = args[1]; // get argument
                int num;
                try {
                    num = stoi(arg);
                } catch(...) {
                    std::cerr << "'" << arg << "' is not a whole number!\n";
                    continue;
                }
                for(int i = 0; i < num; i++) {
                    if(!d.task) break;
                    d.step();
                }
                printf("Stepped to char '%c' at %d\n",
                d.i.instruction[d.i.instructionPointer], 
                d.i.instructionPointer); 
            }
        } else if(cmd == "ls") {
            if(!d.task) {
                printf("Open file to debug: 'open <filename>'\n");
                continue;
            }
            d.showCode();
        } else if(cmd == "help" || cmd == "?") {
            printf("\nCommands list:\n" 
            "    exit help step memory ls interpret open clear\n\n");
        } else if(cmd == "open" || cmd == "o") {
            if(args.size() >= 2) {
                d.start(args[1].c_str());
            } else {
                printf("Enter filename!\n");
            }
        } else if(cmd == "interpret" || cmd == "int") {
            if(!d.task) {
                printf("Open file to debug: 'open <filename>'\n");
                continue;
            }
            d.interpret(); 
        } else if(cmd == "mem" || cmd == "memory") {
            if(!d.task) {
                printf("Open file to debug: 'open <filename>'\n");
                continue;
            }
            if(args.size() < 2) {
                d.showNearestCells();
            }
        } else if(cmd == "stop" || cmd == "end") {
            if(d.task)
                d.end();
            else
                printf("Open file to debug: 'open <filename>'\n");
        } else if(cmd == "clear" || cmd == "cl") {
            #ifdef linux
                system("clear");
            #elif _WIN32
                system("cls");
            #else
            #error What the hell of a system are you using?
            #endif
        } else {
            std::cout << "Incorrect command '" << cmd << "'. Enter 'help' to get a list of"
            " commands\n";
        }
    }
    return 0;
}