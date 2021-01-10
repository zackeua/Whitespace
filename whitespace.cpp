
#include <iostream>
#include <fstream>
#include <string>
#include <stack>


int main(int argc, char const *argv[]) {

    if (argc < 2) { // basic error handeling
        std::cout << "No file to run" << '\n';
        return 0;
    }
    else if (argc > 2) {
        std::cout << "Too many input arguments" << '\n';
        return 0;
    }
    else { // remove this??
        //std::cout << argv[0] << argv[1] <<'\n';
        std::string str = argv[1];
        if (str.rfind(".ws") != str.length() - 3) {
            std::cout << "wrong filetype" << '\n';
            return 0;
        }
    }
    std::ifstream inFile;

    inFile.open(argv[1]);
    if (!inFile) { // basic error handeling
        std::cout << "File not found" << '\n';
        return 0;
    }
    std::stack<int> stack;

    int impFound = 0;
    int commandFound = 0;
    std::string imp = "";
    std::string command = "";


    int numberOfImps = 5;
    int numberOfStackCommands = 4;
    int numberOfArithmeticCommands = 5;
    int numberOfHeapCommands = 2;
    int numberOfFlowCommands = 7;
    int numberOfIoCommands = 4;

    std::string imps[numberOfImps] = {" ", "\t ", "\t\t", "\n", "\t\n"};
    std::string impsString[numberOfImps] = {"Stack Manipulation", "Arithmetic", "Heap Access", "Flow Control", "I/O"};

    std::string stackCommands[numberOfStackCommands] = {" ", "\n ", "\n\t", "\n\n"};
    std::string stackCommandStrings[numberOfStackCommands] = {"Push to stack", "Duplicate top number", "Swap top numbers", "Discard top number"};

    std::string arithmeticCommands[numberOfArithmeticCommands] = {"  ", " \t", " \n", "\n ", "\t\t"};
    std::string arithmeticCommandStrings[numberOfArithmeticCommands] = {"Addition", "Subtraction", "Multiplication", "Integer Division", "Modulo"};

    std::string heapCommands[numberOfHeapCommands] = {" ", "\t"};
    std::string heapCommandStrings[numberOfHeapCommands] = {"Store in heap", "Retrieve from heap"};

    std::string flowCommands[numberOfFlowCommands] = {"  ", " \t", " \n", "\t ", "\t\t", "\t\n", "\n\n"};
    std::string flowCommandStrings[numberOfFlowCommands] = {"Mark a location in the program", "Call a subruotine", "Jump to label", "Jump to label if the top of stack is 0", "Jump to label if the top of stack is <0", "End subruotine and transfer control back to caller", "End the program"};

    std::string ioCommands[numberOfIoCommands] = {"  ", " \t", "\t ", "\t\t"};
    std::string ioCommandStrings[numberOfIoCommands] = {"Output char at top of stack", "Output number at top of stack", "Read a char and place it in the location given by top of stack", "Read number and place it in the location given by top of stack"};

    char c;
    while (inFile.get(c))
    {
        if (c == ' ') {
            std::cout << "Space" << '\n';
            if (!impFound) {
                imp += " ";
            }
            else if (!commandFound) {
                command += " ";
            }
        }
        else if (c == '\t') {
            std::cout << "Tab" << '\n';
            if (!impFound) {
                imp += "\t";
            }
            else if (!commandFound) {
                command += "\t";
            }
        }
        else if (c == '\n') {
            std::cout << "Line Feed" << '\n';
            if (!impFound) {
                imp += "\n";
            }
            else if (!commandFound) {
                command += "\n";
            }
        }
        else {
            //std::cout << c << '\n';
        }

        for (int i = 0; i < numberOfImps; i++) {
            if (!impFound && imp == imps[i]) {
                impFound = i+1;
                std::cout << "IMP: " << impsString[i]<<'\n';
            }

            if (impFound) {
                /* code */
            }
        }

    }

    inFile.close();
    return 0;
}
