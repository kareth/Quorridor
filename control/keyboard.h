#ifndef CONTROL_KEYBOARD_H_
#define CONTROL_KEYBOARD_H_

#include <map>

#include "game/move.h"
#include "game/field.h"
#include "control/input.h"

namespace control {

class Keyboard : public Input {
 public:
  Keyboard();

  void GetMove(game::Move* move) const;

 private:
  void ReadFields(game::Move* move) const;
  int ReadField(game::Field* field) const;

  std::map<char, int> indexes_;

};

}  // namespace control

#endif  // CONTROL_KEYBOARD_H_
