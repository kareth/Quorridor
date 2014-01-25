#ifndef CONTROL_INPUT_H_
#define CONTROL_INPUT_H_

#include "game/move.h"

namespace control {

class Input {
 public:
  ~Input() {}

  virtual void GetMove(game::Move* move) const = 0;

 private:

};

}  // namespace control

#endif  // CONTROL_INPUT_H_
