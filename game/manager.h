#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "game/move.h"
#include "game/board.h"
#include "game/player.h"

namespace game {

class Manager {
 public:
  Manager(Board* board);
  ~Manager();

  int DoMove(const Player& player, const Move& move);

 private:
  int MoveMan(const Player& player, const Field& from, const Field& to);
  int PlaceWall(const Player& player, const Field& from, const Field& to);

  Board* board_;
};

}  // namespace game

#endif  // GAME_MANAGER_H_
