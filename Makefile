.PHONY: clean

CFLAGS= -ansi -pedantic -O0 -Wall -g

all: chip8

chip8: main.o system.o cpu.o 
		g++ -o a.out $(CFLAGS) main.o cpu.o system.o

main.o: main.cpp
		g++ -c -o main.o $(CFLAGS) main.cpp

system.o: system.cpp
		g++ -c -o system.o $(CFLAGS) system.cpp

cpu.o: cpu.cpp
		g++ -c -o cpu.o $(CFLAGS) cpu.cpp


clean:
		rm -f *.o a.out
