#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "game/move.h"
#include "game/board.h"
#include "game/player.h"

namespace game {

class Manager {
 public:
  Manager(int size, int players);
  ~Manager();

  int DoMove(const Player& player, const Move& move);

  const Board& board() const { return board_; }
  int walls(int player) const { return walls_[player]; }

 private:
  int MoveMan(const Player& player, const Field& from, const Field& to);
  int PlaceWall(const Player& player, const Field& from, const Field& to);

  Board board_;
  std::vector<Field> positions_;
  std::vector<int> walls_;
};

}  // namespace game

#endif  // GAME_MANAGER_H_
