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
  void ShowWalls(int count) const;

 private:
  void PrintColoredField(int who) const;
  void SetColor(int color) const;
  void ClearColor() const;

};

}  // namespace visualization

#endif  // VISUALIZATION_CONSOLE_DISPLAY_H_
