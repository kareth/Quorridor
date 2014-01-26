#include "game/manager.h"

namespace game {

Manager::Manager(int size, int players) : board_(size) {
  int walls = 24 / players;

  // No player with ID 0
  positions_.push_back(Field(0, 0));
  walls_.push_back(0);

  for (int i = 1; i <= players; i++) {
    Player player(i);
    Field position;
    if (i == 1) position = Field(0, 4);
    else if (i == 2) position = Field(8, 4);
    else if (i == 3) position = Field(4, 0);
    else if (i == 4) position = Field(4, 8);
    board_.PlaceMan(player, position);
    positions_.push_back(position);
    walls_.push_back(6);
  }
}

Manager::~Manager() {
}

int Manager::DoMove(const Player& player, const Move& move) {
  // TODO
  if (move.type == kMove) {
    return MoveMan(player, move.from, move.to);
  } else if (move.type == kWall) {
    return PlaceWall(player, move.from, move.to);
  }

  return 1;
}

int Manager::MoveMan(const Player& player, const Field& from, const Field& to) {
  if (from != positions_[player.id])
    return 0;

  if (board_.MoveMan(from, to)) {
    positions_[player.id] = to;
    return 1;
  } else {
    return 0;
  }
}

int Manager::PlaceWall(const Player& player, const Field& from, const Field& to) {
  if (walls_[player.id] == 0)
    return 0;

  if (board_.PlaceWall(from, to)) {
    walls_[player.id]--;
    return 1;
  } else {
    return 0;
  }

  return 1;
}

int Manager::getWinner() const {
  for (int id = 1; id <= positions_.size(); id++) {
    if (id == 1 && positions_[id].x == 8) return id;
    else if (id == 2 && positions_[id].x == 0) return id;
    else if (id == 3 && positions_[id].y == 8) return id;
    else if (id == 4 && positions_[id].y == 0) return id;
    return -1;
  }
}

}  // namespace game
