hambit: main.o bitarray.o
	g++ -o hambit main.o -g bitarray.o 

main.o: main.cpp bitarray.h sieve.h
	g++ -c main.cpp

bitarray.o: bitarray.cpp bitarray.h
	g++ -c bitarray.cpp

clean:
	rm *.o hambit