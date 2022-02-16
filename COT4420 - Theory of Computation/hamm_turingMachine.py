""" 
Kaedon Hamm
COT4420 - Theory of Computation
Final Exam - Programming Assignment - Turing Machine for the following Languages:
    L = {(a^i)(b^j)(c^k) : k = i * j}
    L = {w is an element of {0,1}* : w is a binary palendrome


Command to execute:
    python3 hamm_turingMachine.py 1     (Used for Language 1)
    python3 hamm_turingMachine.py 2     (Used for Language 2)

If forgotten just run without args and program will remind you.

Thanks for a great semester! Stay Healthy!
"""


import sys

class tm_input:
    def __init__(self, symbol):
        self.symbol = symbol
        self.mark = symbol


# -------------------------------- Input  --------------------------------- #
def __main__():
    if len(sys.argv) > 1:
        if sys.argv[1] == '1':
            print("You have chosen: L = {(a^i)(b^j)(c^k) : k = i * j}\n")
            input_string = input("Please insert the tape: ")
            print(lang1_inputCheck(input_string))
        elif sys.argv[1] == '2':
            print("You have chosen: L = {w is an element of {0,1}* : w is a binary palendrome\n")
            input_string = input("Please insert the tape: ")
            print(lang2_inputCheck(input_string))
        else:
            print("Please choose either 1 or 2\n")
    else:
        print("This program requires arguments. Please use:\n\t 1 : for L = {(a^i)(b^j)(c^k) : k = i * j}\n\t 2 : for L = {w is an element of {0,1}* : w is a binary palendrome}")
# ------------------------------ End of Input ------------------------------ #



# ------------------------------- Langauge 1 ------------------------------- #
def lang1_inputCheck(input_string):
    print("Checking tape for correct symbols...")
    for chr in input_string:
        if chr == 'a' or chr == 'b' or chr == 'c':
            tape.append(tm_input(chr))
        else:
            print("Tape contains symbol {} which is not in language. Aborting...\n".format(chr))
            return False
    if tape[0].symbol != 'a':
        lang1_langCheck(False)
    else:
        mark_a(0)


def mark_a(ptr):
    print_TapeAndMarks(ptr)
    for i in range(ptr, len(tape), 1):
        if tape[i].symbol == 'a' and tape[i].mark != 'x':
            tape[i].mark = 'x'
            mark_b(i)
        elif tape[i].symbol == 'b':
            lang1_checkTapeMarks()


def move_toStart(ptr):
    for i in range(ptr, -1 -1):
        print_TapeAndMarks(i)
    mark_a(0)


def mark_b(ptr):
    for i in range(ptr, len(tape), 1):
        if tape[i].symbol == 'b' and tape[i].mark != 'x':
            tape[i].mark = 'x'
            print_TapeAndMarks(i)
            mark_c(i)
        print_TapeAndMarks(i)

        
def move_back_b(ptr):
    for i in range(ptr, -1, -1):
        if tape[i].symbol == 'b' and tape[i].mark != 'x':
            mark_b(i)
        elif tape[i].symbol == 'a':
            unmark_b(i)
        print_TapeAndMarks(i)


def unmark_b(ptr):
    for i in range(ptr, len(tape), 1):
        if tape[i].symbol == 'b' and tape[i].mark == 'x':
            tape[i].mark = tape[i].symbol
        elif tape[i].symbol == 'c':
            move_toStart(i)
        print_TapeAndMarks(i)


def mark_c(ptr):
    num_marked = 0
    for i in range(ptr, len(tape), 1):
        if tape[i].symbol == 'c' and tape[i].mark != 'x':
            tape[i].mark = 'x'
            move_back_b(i)
        print_TapeAndMarks(i)
    lang1_langCheck(False)


def lang1_checkTapeMarks():
    for m in tape:
        if m.mark != 'x' and m.symbol != 'b':
            lang1_langCheck(False)
    lang1_langCheck(True)


def lang1_langCheck(torf):
    if torf:
        print(True)
    else:
        print(False)
    exit()
            
            
# --------------------------- End of Langauge 1 --------------------------- #



# ------------------------------- Langauge 2 ------------------------------- #
def lang2_inputCheck(input_string):
    print("Checking tape for correct symbols...")
    for chr in input_string:
        if chr == '1' or chr == '0':
            tape.append(tm_input(chr))
        else:
            print("Tape contains symbol {} which is not in language. Aborting...\n".format(chr))
            return False
    lang2_langCheck()


def lang2_langCheck():
    print("Symbols passed. Checking Lanuage...")
    print_TapeAndMarks(0)
    ping(0)


# Will start from beginning of tape and work its way in
def ping(ptr):
    for i in range(ptr, len(tape), 1):
        if tape[i].mark != 'x':
            tape[i].mark = 'x'
            mirror = tape[i].symbol
            if tape[i+1].mark == 'x':
                print_TapeAndMarks(i)
                print("checkTape")
                lang2_checkTapeMarks()
            compare_mirror(i, mirror)
        print_TapeAndMarks(i)
    lang2_checkTapeMarks()


# Compares symbol to mirror symbol
def compare_mirror(ptr, mirror):
    # Pointer send all the way to end
    for i in range(ptr, len(tape), 1):
        print_TapeAndMarks(i)
        ptr = i
    # Traversing backwards until non-mark is reached
    for i in range(ptr, -1, -1):
        if tape[i].mark != 'x' and tape[i].symbol == mirror:
            tape[i].mark = 'x'
            print_TapeAndMarks(i)
            send_to_beginning(i)
        elif tape[i].mark != 'x' and tape[i].symbol != mirror:
            results_pingPong(False)
        print_TapeAndMarks(i)


# Send pointer to beginning
def send_to_beginning(ptr):
    for i in range(ptr, -1, -1):
        print_TapeAndMarks(i)
        ptr = i
    ping(ptr)


def results_pingPong(torf):
    if torf:
        print(True)
    else:
        print(False)
    exit()


def lang2_checkTapeMarks():
    for i in range(0, len(tape), 1):
        if tape[i].mark != 'x':
            results_pingPong(False)
    results_pingPong(True)


# --------------------------- end of Langauge 2 --------------------------- #


# Prints out Point and Tape
def print_TapeAndMarks(ptr):
    print(" ", end="")
    for i in range(0, len(tape), 1):
        if i == ptr:
            print(" .  ", end="")
        else:
            print("    ", end="")
    print("\tr/w head\n|", end="")
    for m in tape:
        print(" {} |".format(m.mark), end="")
    print("\ttape\n")


tape = []
__main__()