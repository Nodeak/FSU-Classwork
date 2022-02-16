hamint: myint.o main.o
	g++ -o hamint myint.o main.o
	
myint.o: myint.cpp myint.h
	g++ -c myint.cpp
	
main.o: main.cpp myint.h
	g++ -c main.cpp
	
clean: 
	rm *.o hamint
