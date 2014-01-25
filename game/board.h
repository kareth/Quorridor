#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <vector>
#include <map>
#include "game/field.h"
#include "game/player.h"

namespace game {

class Board {
 public:
  Board();

  void AddWall(const Field& from, const Field& to);
  void Move(const Field& from, const Field& to);

 private:
  std::map<Player, bool> players_;
  std::vector<std::vector<int>> fields_;
  std::map<std::pair<Field, Field>, bool> passing_;
};

}  // namespace game

#endif  // GAME_BOARD_H_
