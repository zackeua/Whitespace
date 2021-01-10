import sys
import os.path

DEBUG = 0

def debugPrint(arg):
    if DEBUG:
        print(arg,end='')

if len(sys.argv) < 2:
    print("No file to run")
    exit()
elif len(sys.argv) > 2:
    print("Too many input arguments")
    exit()
elif sys.argv[1][-3:] != '.ws':
    print("Wrong filetype")
    exit()
elif not os.path.isfile(sys.argv[1]):
    print("File not found")
    exit()

with open(sys.argv[1]) as f:
    text = f.read()
    chars = []
    for c in text:
        if c in [' ', '\t', '\n']:
            chars.append(c)

heap = {}
jumps = {}
#jumps = []
stack = []
calls = []


charPointer = 0

imp = ['0','0']
command = ['0','0']
parse = True
#print(chars)
#print(len(chars))

while charPointer<len(chars) and parse:
    imp[0] = chars[charPointer]
    charPointer += 1
    if imp == [' ','0']: # Stack manipulation
        #debugPrint(f'Stack manipulation ')
        command[0] = chars[charPointer]
        charPointer+=1
        if command == [' ','0']:
            while chars[charPointer] != '\n':
                charPointer += 1
            charPointer += 1
        else:
            command[1] = chars[charPointer]
            charPointer += 1
    elif imp == ['\n','0']: #Flow control
        command[0] = chars[charPointer]
        charPointer += 1
        command[1] = chars[charPointer]
        charPointer += 1
        if command == [' ',' ']: # Set label
            number = 0
            while chars[charPointer] != '\n':
                number = number * 2
                if chars[charPointer] == '\t':
                    number = number + 1
                charPointer += 1
            debugPrint(f'Label created: {number} at {charPointer}\n')
            jumps[number] = charPointer
            debugPrint(f'{jumps}\n')
            charPointer += 1
            debugPrint(f'{jumps}\n')
        elif command == [' ','\t']: # call subroutine
            while chars[charPointer] != '\n':
                charPointer += 1
            charPointer += 1
        elif command == [' ','\n']: #Jump to label
            while chars[charPointer] != '\n':
                charPointer += 1
            charPointer += 1
        elif command == ['\t',' ']: #Jump to label if top of stack is 0
            while chars[charPointer] != '\n':
                charPointer += 1
            charPointer += 1
        elif command == ['\t','\t']: #Jump to label if top of stack is < 0
            while chars[charPointer] != '\n':
                charPointer += 1
            charPointer += 1
        elif command == ['\t','\n']: #End subroutine and transfer control to caller
            pass
            #charPointer += 1
        elif command == ['\n','\n']: #End program
            #print("Here too?")
            parse = False
    else:
        imp[1] = chars[charPointer]
        charPointer += 1

        if imp ==['\t',' ']: #Arithmetic
            command[0] = chars[charPointer]
            charPointer += 1
            command[1] = chars[charPointer]
            charPointer += 1
        elif imp == ['\t','\t']: #Heap accsess
            command[0] = chars[charPointer]
            charPointer += 1
        elif imp == ['\t','\n']: #I/O
            command[0] = chars[charPointer]
            charPointer += 1
            command[0] = chars[charPointer]
            charPointer += 1
        else:
            pass
            #print(1)
            #exit()
    imp = ['0','0']
    command = ['0','0']

charPointer = 0
parse = True


#print(jumps)

while charPointer<len(chars) and parse:
    #if len(stack)>0 and stack[-1] > 11:
    #    exit()
    #print('here')
    imp[0] = chars[charPointer]
    charPointer += 1
    if imp == [' ','0']: #Stack Manipulation
        debugPrint(f'Stack manipulation: ')
        command[0] = chars[charPointer]
        charPointer += 1
        if command == [' ','0']: # Push number to stack
            sign = 0
            number = 0
            while chars[charPointer] != '\n':
                #print(number)
                if not sign:
                    if chars[charPointer] == ' ':
                        sign = 1
                    else:
                        sign = -1
                else:
                    number = number * 2
                    if chars[charPointer] == '\t':
                        number += 1
                charPointer += 1
            charPointer += 1
            #print(number)
            debugPrint(f'Push {sign*number} on to stack\n')
            stack.append(sign*number)
        else:
            command[1] = chars[charPointer]
            charPointer += 1
            if command == ['\n',' ']: #Duplicate top number
                debugPrint(f'Duplicate top number\n')
                stack.append(stack[-1])
            elif command == ['\n','\t']: #Swap top numbers
                debugPrint(f'swap top numbers\n')
                '''
                stack[-1] = a
                stack[-2] = b
                a = a_init - b_init
                a = a - b

                b = a_init - b_inint + b_inint = a_inint
                b = a + b

                a = a_init - (a_inint - b_inint) = b_init
                a = b - a
                '''
                stack[-1] = stack[-1] - stack[-2]
                stack[-2] = stack[-1] + stack[-2]
                stack[-1] = stack[-2] - stack[-1]
            elif command == ['\n','\n']: #Discard top number
                debugPrint(f'discard top number\n')
                stack.pop()
            else: # No correct stack manipulation
                debugPrint(f'No correct stack manipulation\n')
                exit()
        debugPrint(f'Stack: {stack}\n')
    elif imp == ['\n','0']: #Flow control
        debugPrint(f'Flow control: ')
        command[0] = chars[charPointer]
        charPointer += 1
        command[1] = chars[charPointer]
        charPointer += 1
        if command == [' ',' ']: # Set label
            debugPrint(f'passed a label\n')
            while chars[charPointer] != '\n':
                charPointer += 1
            charPointer += 1
        elif command == [' ','\t']: # Call a subroutine
            debugPrint('call subroutine')
            number = 0
            while chars[charPointer] != '\n':
                number = number * 2
                if chars[charPointer] == '\t':
                    number += 1
                charPointer += 1
            calls.append(charPointer)
            debugPrint(f'({number})\n')
            charPointer = jumps[number]
            '''
            for jump in jumps:
                if jump[0] == number:
                    charPointer = jump[1]
            '''
            charPointer += 1
        elif command == [' ','\n']: #Jump to label
            debugPrint(f'Jump to label ')
            number = 0
            while chars[charPointer] != '\n':
                number = number * 2
                if chars[charPointer] == '\t':
                    number += 1
                charPointer += 1
            debugPrint(f'({number})\n')
            charPointer = jumps[number]
            '''
            for jump in jumps:
                if jump[0] == number:
                    charPointer = jump[1]
            '''
            #print(charPointer)
            charPointer += 1
        elif command == ['\t',' ']: #Jump to label if top of stack is 0
            debugPrint(f'Jump to label ')
            number = 0
            while chars[charPointer] != '\n':
                number = number * 2
                if chars[charPointer] == '\t':
                    number += 1
                charPointer += 1
            debugPrint(f'({number}) if stack ({stack[-1]}) is 0 ({stack[-1] == 0})\n')
            if stack.pop() == 0:
                charPointer = jumps[number]
                '''
                for jump in jumps:
                    if jump[0] == number:
                        charPointer = jump[1]
                '''
            charPointer += 1
        elif command == ['\t','\t']: #Jump to label if top of stack is < 0
            debugPrint(f'Jump to label ')
            number = 0
            while chars[charPointer] != '\n':
                number = number * 2
                if chars[charPointer] == '\t':
                    number += 1
                charPointer += 1
            debugPrint(f'({number}) if stack ({stack[-1]}) is < 0 ({stack[-1] < 0})\n')
            print('in here')
            if stack.pop() < 0:
                charPointer = jumps[number]
                '''
                for jump in jumps:
                    if jump[0] == number:
                        charPointer = jump[1]
                '''
            charPointer += 1
        elif command == ['\t','\n']: #End subroutine and transfer control to caller
            charPointer = calls.pop()
            debugPrint(f'End subroutine and transfer control to caller ({charPointer})\n')
            charPointer += 1
        elif command == ['\n','\n']: #End program
            debugPrint(f'End of program\n')
            parse = 0
            print()
            exit()
        else: # No correct flow control
            debugPrint('No correct flow control\n')
            exit()
    else:
        imp[1] = chars[charPointer]
        charPointer += 1
        if imp == ['\t',' ']: #Arithmetic
            debugPrint(f'Arithmetic: ')
            command[0] = chars[charPointer]
            charPointer += 1
            command[1] = chars[charPointer]
            charPointer += 1
            if command == [' ',' ']: #Addition
                debugPrint(f'{stack[-2]} + {stack[-1]}\n')
                stack.append(stack.pop() + stack.pop())
            elif command == [' ','\t']: #Subtraction
                debugPrint(f'{stack[-2]} - {stack[-1]}\n')
                stack.append(-stack.pop() + stack.pop())
            elif command == [' ','\n']: #Multiplication
                debugPrint(f'{stack[-2]} * {stack[-1]}\n')
                stack.append(stack.pop() * stack.pop())
            elif command == ['\n',' ']: #Integer division
                debugPrint(f'{stack[-2]} / {stack[-1]}\n')
                stack.append(int(1//(stack.pop()/stack.pop())))
            elif command == ['\t','\t']: #Modulo
                debugPrint(f'{stack[-2]} % {stack[-1]}\n')
                mod = stack.pop()
                stack.append(stack.pop()%mod)
            else: #No correct arithmetic
                exit()
            debugPrint(f'Stack: {stack}\n')
        elif imp == ['\t','\t']: # Heap access
            debugPrint(f'Heap access: ')
            command[0] = chars[charPointer]
            charPointer += 1
            if command == [' ','0']: # Store in heap
                number = stack.pop()
                location = stack.pop()
                heap[location] = number
                debugPrint(f'store {number} at {location} in heap\n')
            elif command == ['\t','0']:
                location = stack.pop()
                stack.append(heap[location])
                debugPrint(f'retreve {stack[-1]} from heap location {location}\n')
            else: # no correct heap access
                exit()
            debugPrint(f'Stack: {stack}\n')
        elif imp == ['\t','\n']: # I/O
            debugPrint(f'I/O: ')
            command[0] = chars[charPointer]
            charPointer += 1
            command[1] = chars[charPointer]
            charPointer += 1
            if command == [' ',' ']: #Output char at top of stack
                debugPrint(f'print char: ')
                print(f'{chr(stack.pop())}',end='')
                debugPrint(f'\n')
            elif command == [' ','\t']: #Output number at top of stack
                debugPrint(f'print number: ')
                print(f'{stack.pop()}',end='')
                debugPrint(f'\n')
            elif command == ['\t',' ']: #read a char and place it in location given by top if stack
                location = stack.pop()
                debugPrint(f'read char and store it in heap location {location}: ')
                heap[location] = ord(input())
            elif command == ['\t','\t']: #read a number and place it in lication given by top of stack
                location = stack.pop()
                debugPrint(f'read number and store it in heap location {location}: ')
                heap[location] = int(input())
            else: #No correct I/O
                exit()
            debugPrint(f'Stack: {stack}\n')
        else: # No correct imp
            exit()
    imp = ['0','0']
    command = ['0','0']

exit()
