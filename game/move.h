#ifndef GAME_MOVE_H_
#define GAME_MOVE_H_

#include "game/field.h"

namespace game {

enum MoveType {
  kWall = 0,
  kMove
};

struct Move {
  MoveType type;
  Field from;
  Field to;

  Move() {}
  Move(MoveType type, const Field& from, const Field& to)
    : type(type), from(from), to(to) {}
};

}  // namespace game

#endif  // GAME_MOVE_H_
