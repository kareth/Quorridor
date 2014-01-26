#ifndef GAME_MOVE_H_
#define GAME_MOVE_H_

#include "game/field.h"

namespace game {

enum MoveType {
  kWall = 1,
  kMove
};

struct Move {
  int type;
  Field from;
  Field to;

  Move() {}
  Move(int type, const Field& from, const Field& to)
    : type(type), from(from), to(to) {}
};

}  // namespace game

#endif  // GAME_MOVE_H_
