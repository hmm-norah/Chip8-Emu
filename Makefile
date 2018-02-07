.PHONY: clean

CFLAGS= -pedantic -O0 -Wall -g

all: chip8

chip8: main.o system.o cpu.o gfx.o
		g++ -o a.out $(CFLAGS) main.o cpu.o system.o gfx.o

main.o: main.cpp
		g++ -c -o main.o $(CFLAGS) main.cpp 

system.o: system.cpp
		g++ -c -o system.o $(CFLAGS) system.cpp

cpu.o: cpu.cpp
		g++ -c -o cpu.o $(CFLAGS) cpu.cpp

gfx.o: gfx.cpp
		g++ -c -o gfx.o $(CFLAGS) gfx.cpp


clean:
		rm -f *.o a.out
