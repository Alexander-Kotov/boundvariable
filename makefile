bin/um: bin src/um.cpp
	g++ -o bin/um -std=c++11 -O3 src/um.cpp

bin:
	mkdir -p bin
