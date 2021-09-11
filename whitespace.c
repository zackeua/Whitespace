#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
TODO:

sort jump lookup table once after construnction
binary search jump lookup table - faster than linear search

fix better function calling stack table


if (stackSize <= stackPointer) {
    stackSize = stackSize * 2;
    stack = realloc(stack, stackSize);
}

could be: (then only one realloc would be nessesary for each increase of the heap)

if (stackSize <= stackPointer) {
    stackSize = stackSize * 2;
}
stack = realloc(stack, stackSize);

*/

typedef struct jumps {
    int label;
    int to;
} jump_t;

// set to debug mode
int debug = 0;

void debugPrint(void *str) {
    if (debug) {
        printf("%s\n", str);
    }
}

char getChar(char c) {
    debugPrint(&c);
    return c;
}

int freeAll(int *stack, int *callStack, int *heap, jump_t *jump, char *chars, int ret) {
    free(stack);
    free(callStack);
    free(heap);
    free(jump);
    free(chars);
    return ret;
}


int main(int argc, char const *argv[]) {
    if (argc < 2) { // basic error handling
        printf("No file to run\n");
        return -1;
    }
    else if (argc > 2) {
        printf("Too many input arguments\n");
        return -1;
    }
    else {
        int len = strlen(argv[1]);
        if (!(argv[1][len-3] == '.' && argv[1][len-2] == 'w' && argv[1][len-1] == 's')) {
            printf("Wrong filetype\n");
            return -1;
        }
    }

    FILE* fp;
    fp = fopen(argv[1],"r");
    if (fp == NULL) {
        printf("File not found\n");
        return -1;
    }


    int charPointer = 0;
    char imp[2] = "00";
    char command[2] = "00";
    int parse = 1;

    int stackPointer = 0;
    int stackSize = 64;
    int *stack = calloc(stackSize, sizeof(*stack));

    int callSize = 0;
    int callStackPointer = 0;
    int *callStack = calloc(callSize, sizeof(*callStack));

    int heapSize = 64;
    int *heap = calloc(heapSize, sizeof(*heap));

    int numberOfLabels = 0;
    jump_t *jump = calloc(numberOfLabels, sizeof(*jump));

    int maximumNumberOfChars = 1024;
    int numberOfChars = 0;
    char *chars = calloc(maximumNumberOfChars, sizeof(*chars)); // ish filestream

    char buffer;
    while (fscanf(fp, "%c", &buffer) != EOF) { // clean file from other than whitespace chars
        /*
        if (buffer == ' ') {
            printf("Space\n");
        }
        else if (buffer == '\t') {
            printf("Tab\n");
        }
        else if (buffer == '\n') {
            printf("Linefeed\n");
        }
        else {
            printf("%c\n", buffer);
        }
        */
        if (buffer == ' ' || buffer == '\t' || buffer == '\n') {
            chars[numberOfChars] = buffer;
            numberOfChars++;
            if (numberOfChars == maximumNumberOfChars) {
                maximumNumberOfChars = maximumNumberOfChars * 2;
                chars = realloc(chars, maximumNumberOfChars*sizeof(*chars));
                if (chars == NULL) {
                    printf("Whole file could not be cleaned\n");
                    free(fp);
                    return freeAll(stack, callStack, heap, jump, chars, -1);
                }
            }
        }
    }
    fclose(fp);





    while (charPointer <= numberOfChars && parse) {
        /* get instrunction:
        read type of instrunction i.e. imp
        based of off imp, get instrunction and
        maybe argument to instrunction
        */

        // find IMP
        imp[0] = chars[charPointer];
        charPointer++;
        if (imp[0] == ' ' && imp[1] == '0') { // Stack Manipulation
            command[0] = chars[charPointer];
            charPointer++;
            if (command[0] == ' ') { // Push number to stack
                //debugPrint("Push number to stack\n");
                // read number until '/n'
                while (chars[charPointer] != '\n') {
                    charPointer++;
                }
                charPointer++;

            } else {
                command[1] = chars[charPointer];
                charPointer++;
            }
        }

        else if (imp[0] == '\n' && imp[1] == '0') { // Flow control
            //debugPrint("Flow Control\n");
            command[0] = chars[charPointer];
            command[1] = chars[charPointer + 1];
            charPointer = charPointer + 2;
            if (command[0] == ' ' && command[1] == ' ') { // set label
                //debugPrint("Set label\n");
                int number = 0;
                jump_t temp;
                while (chars[charPointer] != '\n') {
                    number = number * 2;
                    if (chars[charPointer] == '\t') {
                        number++;
                    }
                    charPointer++;
                }
                temp.label = number;
                temp.to = charPointer;

                jump = realloc(jump, (numberOfLabels + 1)*sizeof(*jump));
                jump[numberOfLabels] = temp;
                numberOfLabels++;
                charPointer++;
            }
            else if (command[0] == ' ' && command[1] == '\t') { // call a subroutine
                //debugPrint("Call a subruotine\n");
                while (chars[charPointer] != '\n') {
                    charPointer++;
                }
                charPointer++;
            }
            else if (command[0] == ' ' && command[1] == '\n') { // Jump to label
                //debugPrint("Jump to label\n");
                while (chars[charPointer] != '\n') {
                    charPointer++;
                }
                charPointer++;
            }
            else if (command[0] == '\t' && command[1] == ' ') { // jump to label if top of stack is 0
                //debugPrint("Jump to label if the top of stack is 0\n");
                while (chars[charPointer] != '\n') {
                    charPointer++;
                }
                charPointer++;
            }
            else if (command[0] == '\t' && command[1] == '\t') { // Jump to label if top is < 0
                //debugPrint("Jump to label if the top of stack is <0\n");
                while (chars[charPointer] != '\n') {
                    charPointer++;
                }
                charPointer++;
            }
            else if (command[0] == '\t' && command[1] == '\n') { // end subroutine and transfer control to caller
                //debugPrint("End subruotine and transfer control back to caller\n");
            }
            else if (command[0] == '\n' && command[1] == '\n') { // end program
                //debugPrint("End the program\n");
                parse = 0;
            }
            else {
                //printf("No correct command for Flow Control\n");
                return freeAll(stack, callStack, heap, jump, chars, -1);
            }
        }

        else {
            imp[1] = chars[charPointer];
            charPointer++;

            if (imp[0] == '\t' && imp[1] == ' ') { // Arithmetic
                command[0] = chars[charPointer];
                command[1] = chars[charPointer + 1];
                charPointer = charPointer + 2;
            }

            else if (imp[0] == '\t' && imp[1] == '\t') { // Heap accsess
                command[0] = chars[charPointer];
                charPointer++;
            }

            else if (imp[0] == '\t' && imp[1] == '\n') { // I/O
                command[0] = chars[charPointer];
                command[1] = chars[charPointer + 1];
                charPointer = charPointer + 2;
            }

            else {
                //printf("No correct IMP\n");
                //printf("Here\n");
                return freeAll(stack, callStack, heap, jump, chars, -1);
            }
        }

        //reset IMP
        imp[0] = '0';
        imp[1] = '0';
        // reset command
        command[0] = '0';
        command[1] = '0';

    }

    charPointer = 0;
    parse = 1;

    /*
    for (int i = 0; i < numberOfLabels; i++) {
        printf("Label: %d, to: %d\n", jump[i].label, jump[i].to);
    }
    */

    while (charPointer <= numberOfChars && parse) {
        /* get instrunction:
        read type of instrunction i.e. imp
        based of off imp, get instrunction and
        maybe argument to instrunction
        */

        // find IMP
        imp[0] = chars[charPointer];
        charPointer++;
        if (imp[0] == ' ' && imp[1] == '0') { // Stack Manipulation
            debugPrint("Stack Manipulation\n");
            command[0] = chars[charPointer];
            charPointer++;
            if (command[0] == ' ') { // Push number to stack
                debugPrint("Push number to stack\n");
                // read number until '/n'
                // push that to stack
                int sign = 0;
                int number = 0;
                while (chars[charPointer] != '\n') {
                    if (sign == 0) {
                        if (chars[charPointer] == ' ') {
                            sign = 1;
                        }
                        else {
                            sign = -1;
                        }

                    }
                    else {
                        number = number * 2;
                        if (chars[charPointer] == '\t') {
                            number++;
                        }
                    }
                    charPointer++;
                }
                charPointer++;
                stackPointer++;
                if (stackSize <= stackPointer) {
                    stackSize = stackSize * 2;
                    stack = realloc(stack, stackSize*sizeof(*stack));
                }
                stack[stackPointer] = sign * number;
                //printf("%d\n", stack[stackPointer]);
            } else {
                command[1] = chars[charPointer];
                charPointer++;
                if (command[0] == '\n' && command[1] == ' ') { // Duplicate top number
                    debugPrint("Duplicate top number\n");
                    stackPointer++;
                    if (stackSize <= stackPointer) {
                        stackSize = stackSize * 2;
                        stack = realloc(stack, stackSize*sizeof(*stack));
                    }
                    stack[stackPointer] = stack[stackPointer - 1];
                }
                else if (command[0] == '\n' && command[1] == '\t') { // swap top numbers
                    debugPrint("Swap top numbers\n");
                    /*
                    stack[stackPointer] = a
                    stack[stackPointer - 1] = b

                    a = a_init - b_init
                    a = a - b

                    b = a_init - b_init + b_init = a_init
                    b = a + b

                    a = a_init - (a_init - b_init) = b_init
                    a = b - a
                    */
                    stack[stackPointer] = stack[stackPointer] - stack[stackPointer - 1];
                    stack[stackPointer - 1] = stack[stackPointer] + stack[stackPointer - 1];
                    stack[stackPointer] = stack[stackPointer - 1] - stack[stackPointer];
                }
                else if (command[0] == '\n' && command[1] == '\n') { // Discard top number
                    debugPrint("Discard top number\n");
                    stack[stackPointer] = 0;
                    stackPointer--;
                }
                else {
                    //printf("No correct command for Stack Manipulation\n");
                    return freeAll(stack, callStack, heap, jump, chars, -1);
                }
            }

        }

        else if (imp[0] == '\n' && imp[1] == '0') { // Flow control
            debugPrint("Flow Control\n");
            command[0] = chars[charPointer];
            command[1] = chars[charPointer + 1];
            charPointer = charPointer + 2;
            if (command[0] == ' ' && command[1] == ' ') { // set label
                debugPrint("Set label\n");
                while (chars[charPointer] != '\n') { // read past label
                    charPointer++;
                }
                charPointer++;
            }
            else if (command[0] == ' ' && command[1] == '\t') { // call a subroutine
                debugPrint("Call a subruotine\n");

                int number = 0;
                while (chars[charPointer] != '\n') {
                    number = number * 2;
                    if (chars[charPointer] == '\t') {
                        number++;
                    }
                    charPointer++;
                }

                callStackPointer++;
                if (callSize < callStackPointer) {
                    callSize = callSize * 2;
                    callStack = realloc(callStack, callSize*sizeof(*callStack));
                    if (callStack == NULL) {
                        return freeAll(stack, callStack, heap, jump, chars, -1);
                    }
                }

                callStack[callStackPointer] = charPointer;
                callStackPointer = callStackPointer + 1;

                for (int i = 0; i < numberOfLabels; i++) {
                    if (jump[i].label == number) {
                        charPointer = jump[i].to;
                    }
                }

                charPointer++;

            }
            else if (command[0] == ' ' && command[1] == '\n') { // Jump to label
                debugPrint("Jump to label\n");
                int number = 0;
                while (chars[charPointer] != '\n') {
                    number = number * 2;
                    if (chars[charPointer] == '\t') {
                        number++;
                    }
                    charPointer++;
                }

                for (int i = 0; i < numberOfLabels; i++) {
                    if (jump[i].label == number) {
                        charPointer = jump[i].to;
                    }
                }

                charPointer++;
            }
            else if (command[0] == '\t' && command[1] == ' ') { // jump to label if top of stack is 0
                debugPrint("Jump to label if the top of stack is 0\n");
                int number = 0;
                while (chars[charPointer] != '\n') {
                    number = number * 2;
                    if (chars[charPointer] == '\t') {
                        number++;
                    }
                    charPointer++;
                }
                int top = stack[stackPointer];
                stack[stackPointer] = 0;
                stackPointer--;

                if (top == 0) {
                    for (int i = 0; i < numberOfLabels; i++) {
                        if (jump[i].label == number) {
                            charPointer = jump[i].to;
                        }
                    }
                }
                charPointer++;
            }
            else if (command[0] == '\t' && command[1] == '\t') { // Jump to label if top is < 0
                debugPrint("Jump to label if the top of stack is <0\n");
                int number = 0;
                while (chars[charPointer] != '\n') {
                    number = number * 2;
                    if (chars[charPointer] == '\t') {
                        number++;
                    }
                    charPointer++;
                }
                int top = stack[stackPointer];
                stack[stackPointer] = 0;
                stackPointer--;

                if (top < 0) {
                    for (int i = 0; i < numberOfLabels; i++) {
                        if (jump[i].label == number) {
                            charPointer = jump[i].to;
                        }
                    }
                }
                charPointer++;
            }
            else if (command[0] == '\t' && command[1] == '\n') { // end subroutine and transfer control to caller
                debugPrint("End subruotine and transfer control back to caller\n");
                charPointer = callStack[callStackPointer - 1];
                callStackPointer = callStackPointer - 1;
                charPointer++;
            }
            else if (command[0] == '\n' && command[1] == '\n') { // end program
                debugPrint("End the program\n");
                printf("\n");
                parse = 0;
            }
            else {
                //printf("No correct command for Flow Control\n");
                return freeAll(stack, callStack, heap, jump, chars, -1);
            }
        }

        else {
            imp[1] = chars[charPointer];
            charPointer++;

            if (imp[0] == '\t' && imp[1] == ' ') { // Arithmetic
                debugPrint("Arithmetic\n");
                command[0] = chars[charPointer];
                command[1] = chars[charPointer + 1];
                charPointer = charPointer + 2;

                if (command[0] == ' ' && command[1] == ' ') { // Addition
                    debugPrint("Addition\n");
                    stackPointer--;
                    stack[stackPointer] = stack[stackPointer] + stack[stackPointer + 1];
                    stack[stackPointer + 1] = 0;
                }
                else if (command[0] == ' ' && command[1] == '\t') { // Subtraction
                    debugPrint("Subtraction\n");
                    stackPointer--;
                    stack[stackPointer] = stack[stackPointer] - stack[stackPointer + 1];
                    stack[stackPointer + 1] = 0;
                }
                else if (command[0] == ' ' && command[1] == '\n') { // Multiplication
                    debugPrint("Multiplication\n");
                    stackPointer--;
                    stack[stackPointer] = stack[stackPointer] * stack[stackPointer + 1];
                    stack[stackPointer + 1] = 0;
                }
                else if (command[0] == '\n' && command[1] == ' ') { // Integer division
                    debugPrint("Integer Division\n");
                    stackPointer--;
                    stack[stackPointer] = stack[stackPointer] / stack[stackPointer + 1];
                    stack[stackPointer + 1] = 0;
                }
                else if (command[0] == '\t' && command[1] == '\t') { // Modulo
                    debugPrint("Modulo\n");
                    stackPointer--;
                    stack[stackPointer] = stack[stackPointer] % stack[stackPointer + 1];
                    stack[stackPointer + 1] = 0;
                }
                else {
                    //printf("No correct command for Arithmetic\n");
                    return freeAll(stack, callStack, heap, jump, chars, -1);
                }

            }

            else if (imp[0] == '\t' && imp[1] == '\t') { // Heap accsess
                debugPrint("Heap Access\n");
                command[0] = chars[charPointer];
                charPointer++;
                if (command[0] == ' ') {  // Store in heap
                    debugPrint("Store in heap\n");
                    while (heapSize <= stack[stackPointer - 1]) { // increase heap if nessesary
                        heapSize = heapSize * 2;
                        heap = realloc(heap, heapSize*sizeof(*heap));
                        if (heap == NULL) {
                            return freeAll(stack, callStack, heap, jump, chars, -1);
                        }
                    }
                    heap[stack[stackPointer - 1]] = stack[stackPointer]; // store value in heap
                    stack[stackPointer] = 0;
                    stack[stackPointer - 1] = 0;
                    stackPointer = stackPointer - 2;
                }
                else if (command[0] == '\t') { // Retrieve from heap
                    debugPrint("Retrieve from heap\n");
                    //stackPointer++;
                    if (stackSize <= stackPointer) {
                        stackSize = stackSize * 2;
                        stack = realloc(stack, stackSize*sizeof(*stack));
                        if (stack == NULL) {
                            return freeAll(stack, callStack, heap, jump, chars, -1);
                        }
                    }

                    if (heapSize > stack[stackPointer]) {
                        stack[stackPointer] = heap[stack[stackPointer]];
                    }
                    else {
                        stack[stackPointer] = 0;
                    }
                }
                else {
                    //printf("No correct command for Heap Access\n");
                    return freeAll(stack, callStack, heap, jump, chars, -1);
                }

            }

            else if (imp[0] == '\t' && imp[1] == '\n') { // I/O
                debugPrint("I/O\n");
                command[0] = chars[charPointer];
                command[1] = chars[charPointer + 1];
                charPointer = charPointer + 2;
                if (command[0] == ' ' && command[1] == ' ') { // Output char at top of stack
                    debugPrint("Output char at top of stack\n");
                    printf("%c", stack[stackPointer]);
                    stack[stackPointer] = 0;
                    stackPointer--;
                }
                else if (command[0] == ' ' && command[1] == '\t') { // output number at top of stack
                    debugPrint("Output number at top of stack\n");
                    printf("%d", stack[stackPointer]);
                    stack[stackPointer] = 0;
                    stackPointer--;
                }
                else if (command[0] == '\t' && command[1] == ' ') { // read a char and place it in location given by top of stack
                    debugPrint("Read a char and place it in the location given by top of stack\n");
                    char buffer;
                    scanf(" %c", &buffer);
                    while (heapSize <= stack[stackPointer]) {
                        heapSize = heapSize * 2;
                        heap = realloc(heap, heapSize*sizeof(*heap));
                        if (heap == NULL) {
                            return freeAll(stack, callStack, heap, jump, chars, -1);
                        }
                    }
                    heap[stack[stackPointer]] = buffer;
                    stack[stackPointer] = 0;
                    stackPointer--;
                }
                else if (command[0] == '\t' && command[1] == '\t') { // read a number and place it in location given by top of stack
                    debugPrint("Read number and place it in the location given by top of stack\n");
                    int buffer;
                    scanf(" %d", &buffer);
                    while (heapSize <= stack[stackPointer]) {
                        heapSize = heapSize * 2;
                        heap = realloc(heap, heapSize*sizeof(*heap));
                        if (heap == NULL) {
                            return freeAll(stack, callStack, heap, jump, chars, -1);
                        }
                    }
                    heap[stack[stackPointer]] = buffer;
                    stack[stackPointer] = 0;
                    stackPointer--;
                }
                else {
                    //printf("No correct command for I/O\n");
                    return freeAll(stack, callStack, heap, jump, chars, -1);
                }
            }

            else {
                //printf("No correct IMP\n");
                return freeAll(stack, callStack, heap, jump, chars, -1);
            }
        }

        //reset IMP
        imp[0] = '0';
        imp[1] = '0';
        // reset command
        command[0] = '0';
        command[1] = '0';

    }

    return freeAll(stack, callStack, heap, jump, chars, 0);
}
