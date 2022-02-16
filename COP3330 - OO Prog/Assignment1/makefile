hamtri: triangle.o driver.o
	g++ -o hamtri triangle.o driver.o

driver.o: driver.cpp triangle.h
	g++ -c driver.cpp

triangle.o: triangle.cpp triangle.h
	g++ -c triangle.cpp

clean:
	rm *.o hamtri
