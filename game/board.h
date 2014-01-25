#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <vector>
#include <map>
#include "game/field.h"
#include "game/player.h"

namespace game {

class Board {
 public:
  explicit Board(int size);

  int PlaceWall(const Field& from, const Field& to);
  int MoveMan(const Field& from, const Field& to);

  void PlaceMan(const Player& player, const Field& position);

  int size() const { return size_; }
  bool IsBlocked(const Field& from, const Field& to) const;
  int At(const Field& pos) const { return fields_[pos.x][pos.y]; }

 private:
  bool AddBlocks(const Field& from, const Field& from_opp,
                      const Field& to, const Field& to_opp);
  void Block(const Field& from, const Field& from_opp);

  int size_;
  std::vector<std::vector<int>> fields_;
  std::map<std::pair<Field, Field>, bool> blocked_;
};

}  // namespace game

#endif  // GAME_BOARD_H_
