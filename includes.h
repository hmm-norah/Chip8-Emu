#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
#include <stdint.h>
#include <iomanip>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

typedef uint8_t byte;

#define WIDTH 64
#define HEIGHT 32
#define PIXELS WIDTH*HEIGHT

enum controller
{
  zero, one, two, three, four, five, six, seven, eight, nine, ten, a = 'a', c, d, e, f
};

#endif
