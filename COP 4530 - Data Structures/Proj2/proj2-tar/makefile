proj2.x: test_vector.o
	g++ -std=c++11 -o proj2.x test_vector.o
	
test_vector.o: test_vector.cpp Vector.hpp
	g++ -std=c++11 -c test_vector.cpp
	
clean:
	rm *.o*