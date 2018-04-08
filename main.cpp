#include "system.h"

void key_test();

int main (int argc, char ** argv)
{
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();

  /* Eventually, command line argument for ch8 rom to load... hardcoded to tetris for now
  if(argc != 2)
    return 0;
  */

  key_test();

  refresh();
  getch();
  endwin();

  /*
  char test_rom[] = "tetris.ch8";
  System ch8(test_rom);
  ch8.run();
  */

  return 0;
}

void key_test()
{
  int command;
  printw("Press arrow key for recognition\n");

  command = getch();

  if(command == KEY_LEFT)
    printw("Left arrow");
  else if(command == KEY_UP)
    printw("Up arrow");
  else if(command == KEY_RIGHT)
    printw("Right arrow");
  else if(command == KEY_DOWN)
    printw("Down arrow");
  else
    printw("Not recognized");
}
