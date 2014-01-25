#ifndef VISUALIZATION_DISPLAY_H_
#define VISUALIZATION_DISPLAY_H_

#include "game/board.h"

namespace visualization {

class Display {
 public:
  ~Display() {}

  virtual void ShowBoard(const game::Board& board) const = 0;
  virtual void ShowWalls(int count) const = 0;

 private:

};

}  // namespace visualization

#endif  // VISUALIZATION_DISPLAY_H_
