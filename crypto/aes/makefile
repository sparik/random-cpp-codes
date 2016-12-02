all: main.o aes.o
	g++ main.o aes.o -o main
main.o: main.cpp
	g++ -c main.cpp
aes.o: aes.cpp
	g++ -c aes.cpp
clean:
	rm *o main
