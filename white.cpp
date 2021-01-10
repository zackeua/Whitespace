
#include <iostream>
#include <fstream>
#include <string>
#include <stack>


int numberOfImps = 5;
std::string imps[5] = {" ", "\t ", "\t\t", "\n", "\t\n"};
std::string impsString[5] = {"Stack Manipulation", "Arithmetic", "Heap Access", "Flow Control", "I/O"};

int numberOfStackCommands = 4;
std::string stackCommands[4] = {" ", "\n ", "\n\t", "\n\n"};
std::string stackCommandStrings[4] = {"Push to stack", "Duplicate top number", "Swap top numbers", "Discard top number"};

int numberOfArithmeticCommands = 5;
std::string arithmeticCommands[5] = {"  ", " \t", " \n", "\n ", "\t\t"};
std::string arithmeticCommandStrings[5] = {"Addition", "Subtraction", "Multiplication", "Integer Division", "Modulo"};

int numberOfHeapCommands = 2;
std::string heapCommands[2] = {" ", "\t"};
std::string heapCommandStrings[2] = {"Store in heap", "Retrieve from heap"};

int numberOfFlowCommands = 7;
std::string flowCommands[7] = {"  ", " \t", " \n", "\t ", "\t\t", "\t\n", "\n\n"};
std::string flowCommandStrings[7] = {"Mark a location in the program", "Call a subruotine", "Jump to label", "Jump to label if the top of stack is 0", "Jump to label if the top of stack is <0", "End subruotine and transfer control back to caller", "End the program"};

int numberOfIoCommands = 4;
std::string ioCommands[4] = {"  ", " \t", "\t ", "\t\t"};
std::string ioCommandStrings[4] = {"Output char at top of stack", "Output number at top of stack", "Read a char and place it in the location given by top of stack", "Read number and place it in the location given by top of stack"};




std::string readIMP(std::ifstream &inFile);

std::string readCommand(std::string imp, std::ifstream &inFile);

int getInstruction(std::string imp, std::string command);

bool checkStack(std::string command);
bool checkArithmetic(std::string command);
bool checkHeap(std::string command);
bool checkFlow(std::string command);
bool checkIo(std::string command);


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

    int instructions = new 


    bool parsing = true;

    while (parsing)
    {
        imp = readIMP(inFile);

        command = readCommand(imp, inFile);
        instructions[]
        if (imp == imps[3] && command == flowCommands[6]) {
            parsing = false;
        }
    }

    inFile.close();
    return 0;
}

std::string readIMP(std::ifstream &inFile) {
    char c;
    std::string imp = "";
    bool impFound = false;
    int iter = 0;
    while (!impFound && iter < 3 && inFile.get(c)) {

        if (c == ' ') {
            std::cout << "Space" << '\n';
            imp += " ";
        }
        else if (c == '\t') {
            std::cout << "Tab" << '\n';
            imp += "\t";
        }
        else if (c == '\n') {
            std::cout << "Line Feed" << '\n';
            imp += "\n";
        }
        else {
            //std::cout << c << '\n';
        }

        for (int i = 0; i < numberOfImps; i++) {
            if (!impFound && imp == imps[i]) {
                impFound = i+1;
                std::cout << "IMP: " << impsString[i]<<'\n';
            }
        }
    }
    return imp;
}

std::string readCommand(std::string imp, std::ifstream &inFile) {

    char c;
    std::string command = "";
    bool commandFound = false;
    int iter = 0;

    while (!commandFound && iter < 3 && inFile.get(c)) {

        if (c == ' ') {
            std::cout << "Space" << '\n';
            command += " ";
        }
        else if (c == '\t') {
            std::cout << "Tab" << '\n';
            command += "\t";
        }
        else if (c == '\n') {
            std::cout << "Line Feed" << '\n';
            command += "\n";
        }
        else {
            //std::cout << c << '\n';
        }


        if (imp == imps[0]) { // stackCommands
            if(checkStack(command)) {
                commandFound = true;
            }
        } else if (imp == imps[1]) { // arithmeticCommands
            if (checkArithmetic(command)) {
                commandFound = true;
            }
        } else if (imp == imps[2]) { // heapCommands
            if(checkHeap(command)){
                commandFound = true;
            }
        } else if (imp == imps[3]) { // flowCommands
            if (checkFlow(command)) {
                commandFound = true;
            }
        } else if (imp == imps[4]) { // IoCommands
            if (checkIo(command)) {
                commandFound = true;
            }
        }
    }
    return command;
}

bool checkStack(std::string command) {
    for (int i = 0; i < numberOfStackCommands; i++) {
        if (command == stackCommands[i]) {
            std::cout << "Command: " << stackCommandStrings[i] <<'\n';
            return true;
        }
    }
    return false;
}

bool checkArithmetic(std::string command) {
    for (int i = 0; i < numberOfArithmeticCommands; i++) {
        if (command == arithmeticCommands[i]) {
            std::cout << "Command: " << arithmeticCommandStrings[i] <<'\n';
            return true;
        }
    }
    return false;
}

bool checkHeap(std::string command) {
    for (int i = 0; i < numberOfHeapCommands; i++) {
        if (command == heapCommands[i]) {
            std::cout << "Command: " << heapCommandStrings[i] << '\n';
            return true;
        }
    }
    return false;
}

bool checkFlow(std::string command) {
    for (int i = 0; i < numberOfFlowCommands; i++) {
        if (command == flowCommands[i]) {
            std::cout << "Command: " << flowCommandStrings[i] << '\n';
            return true;
        }
    }
    return false;
}


bool checkIo(std::string command) {
    for (int i = 0; i < numberOfIoCommands; i++) {
        if (command == ioCommands[i]) {
            std::cout << "Command: " << ioCommandStrings[i] << '\n';
            return true;
        }
    }
    return false;
}

int getInstruction(std::string imp, std::string command) {
    if (imp == imps[0]) {
        if (command == stackCommands[0]) {
            return 0;
        }
        else if (command == stackCommands[1]) {
            return 1;
        }
        else if (command == stackCommands[2])
    }
    else if (imp == imps[1]) {

    }
    else if (imp == imps[2]) {

    }
    else if (imp == imps[3]) {

    }
    else if (imp == imps[4]) {

    }
}
