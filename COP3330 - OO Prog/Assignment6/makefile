hamstud: main.o student.o studentlist.o
	g++ -o hamstud main.o student.o studentlist.o

main.o: main.cpp student.h studentlist.h
	g++ -c main.cpp

student.o: student.cpp student.h
	g++ -c student.cpp

studentlist.o: studentlist.cpp studentlist.h
	g++ -c studentlist.cpp

clean: hamstud
	rm *.o hamstud
