#include "system.h"

char key_test();

int main (int argc, char ** argv)
{
  initscr();
  raw();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  scrollok(stdscr,TRUE);
  noecho();
  curs_set(FALSE);

  /* Eventually, command line argument for ch8 rom to load... hardcoded to tetris for now
  if(argc != 2)
    return 0;
  */
  while(key_test() != '0')
  {
    refresh();
    usleep(100000);

  }

  getch();
  endwin();

  /*
  char test_rom[] = "tetris.ch8";
  System ch8(test_rom);
  ch8.run();
  */

  return 0;
}

char key_test()
{
  int command;
  printw("Press arrow key for recognition\n");

  command = getch();

  if(command == KEY_LEFT)
    printw("Left arrow\n");
  else if(command == KEY_UP)
    printw("Up arrow\n");
  else if(command == KEY_RIGHT)
    printw("Right arrow\n");
  else if(command == KEY_DOWN)
    printw("Down arrow\n");
  else if(command == ERR)
    printw("No input");
  else
    addch(command);

  return command;
}
