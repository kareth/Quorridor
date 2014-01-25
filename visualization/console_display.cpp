#include "visualization/console_display.h"

namespace visualization {

ConsoleDisplay::ConsoleDisplay() {}

void ConsoleDisplay::ShowBoard(const game::Board& board) const {
  printf("I\n");
  //printf("\033[1;31mbu\033[0m\n");
  printf("[ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]\n\n");
  printf("[ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]\n\n");
  printf("[ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]\n");
  printf("                -------     \n");
  printf("[ ] [ ] [ ] [ ] \033[1;31m[x]\033[0m|[ ] [ ] [ ]\n");
  printf("                   |       \n");
  printf("[ ] [ ] [ ] [ ] [ ]|[ ] [ ] [ ]\n\n");
  printf("[ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]\n\n");
  printf("[ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]\n\n");
  printf("[ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]\n\n");
}

}  // namespace visualization

