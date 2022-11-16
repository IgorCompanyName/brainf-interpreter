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
    
    while(true) {
        if(d.i.s_Path != "")
            std::cout << " (" << d.i.s_Path << ") >>> ";
        else
            std::cout << " (bfd) >>> ";
        std::string temp;

        getline(std::cin, temp);
        if(temp.empty())
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
            printf("Stepped to char '%c' at %d\n", 
            d.i.instruction[d.i.instructionPointer], d.i.instructionPointer);
            d.step();
        } else if(cmd == "sc") {
            if(!d.task) {
                printf("Open file to debug: 'open <filename>'\n");
                continue;
            }
            d.showCode();
        } else if(cmd == "help") {
            printf("\nCommands list:\n" 
            "    exit help step memory sc interpret open\n\n");
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
        } else {
            std::cout << "Incorrect command '" << cmd << "'. Enter 'help' to get a list of"
            " commands\n";
        }
    }
    return 0;
}