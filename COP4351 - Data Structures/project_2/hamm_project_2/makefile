make: 
	touch output/l1_metric.txt
	touch output/out.txt
	g++ upsample.cpp -lm -o main

test:
	touch output/l1_metric.txt
	touch output/out.txt
	g++ -std=c++11 -o test -I ./googletest/googletest/include/ -L ./googletest/build/lib unittest/UnitTest.cpp -lgtest -lpthread

coverage:
	touch output/l1_metric.txt
	touch output/out.txt
	g++ -std=c++11 -o code_cov_main -fprofile-arcs -ftest-coverage -fPIC upsample.cpp
	g++ -std=c++11 -o code_cov_test -fprofile-arcs -ftest-coverage unittest/UnitTest.cpp -L ./googletest/build/lib/ -I ./googletest/googletest/include -lgtest -lpthread
	./code_cov_main
	./code_cov_test
	~/.local/bin/gcovr

clean:
	rm *.css *.html *.gcno *.gcda code_cov_* main test output/*.txt
	