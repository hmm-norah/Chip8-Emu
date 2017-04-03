.PHONY: clean

CFLAGS= -ansi -pedantic -O0 -Wall -g
SDL_FLAGS = -I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2

all: chip8

chip8: main.o system.o cpu.o gfx.o
		g++ -o a.out $(CFLAGS) main.o cpu.o system.o gfx.o $(SDL_FLAGS)

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
