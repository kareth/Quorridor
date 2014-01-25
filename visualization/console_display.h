#ifndef VISUALIZATION_CONSOLE_DISPLAY_H_
#define VISUALIZATION_CONSOLE_DISPLAY_H_

#include <cstdio>

#include "game/board.h"
#include "visualization/display.h"

namespace visualization {

class ConsoleDisplay : public Display {
 public:
  ConsoleDisplay();

  void ShowBoard(const game::Board& board) const;

 private:

};

}  // namespace visualization

#endif  // VISUALIZATION_CONSOLE_DISPLAY_H_
