# Kaedon Hamm
# COP 3353
# 12/7/2017
# Assignment 7


CC = g++
# CC Macro is created and set to compile g++

CFLAG = -c -g
# CFLAG provides -c and -g arguments

LFLAG = -g -I.
# LFLAG provides -g and -I. arguments




# assignment7 executable will be created when make is ran exe will contain compiled versions fo mainbox.cpp, messages.cpp and box.cpp
assignment7: mainbox.o messages.o box.o
	$(CC) $(LFLAG) -o assignment7 mainbox.o messages.o box.o


# mainbox.cpp is compiled and debugged (using Macros)
mainbox.o: mainbox.cpp
	$(CC) $(CFLAG)  mainbox.cpp


# messages.cpp is compiled and debugged (using Macros)
messages.o: messages.cpp messages.h
	$(CC) $(CFLAG) messages.cpp


# box.cpp is compiled and debugged (using Macros)
box.o: box.cpp box.h
	$(CC) $(CFLAG) box.cpp


# removes all '.o' files
clean:
	rm *.o assignment7
