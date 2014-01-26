#ifndef VISUALIZATION_CONSOLE_DISPLAY_H_
#define VISUALIZATION_CONSOLE_DISPLAY_H_

#include <cstdio>

#include "game/board.h"
#include "visualization/display.h"
#include "protocol/command.h"

namespace visualization {

class ConsoleDisplay : public Display {
 public:
  ConsoleDisplay();

  void ShowBoard(const game::Board& board) const;
  void ShowWalls(int count) const;
  void ShowMessageFor(const protocol::Command& command) const;
  void ShowPlayerInfo(int id) const;
  void ShowWinner(int winner, int me) const;

 private:
  void PrintColoredField(int who) const;
  void SetColor(int color) const;
  void ClearColor() const;

};

}  // namespace visualization

#endif  // VISUALIZATION_CONSOLE_DISPLAY_H_
