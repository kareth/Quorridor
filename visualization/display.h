#ifndef VISUALIZATION_DISPLAY_H_
#define VISUALIZATION_DISPLAY_H_

#include "game/board.h"
#include "protocol/command.h"

namespace visualization {

class Display {
 public:
  ~Display() {}

  virtual void ShowBoard(const game::Board& board) const = 0;
  virtual void ShowWalls(int count) const = 0;
  virtual void ShowMessageFor(const protocol::Command& command) const = 0;
  virtual void ShowPlayerInfo(int id) const = 0;
  virtual void ShowWinner(int winner, int me) const = 0;

 private:

};

}  // namespace visualization

#endif  // VISUALIZATION_DISPLAY_H_
