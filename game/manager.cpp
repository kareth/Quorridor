#include "game/manager.h"

namespace game {

Manager::Manager(int size, int players) : board_(size) {
  int walls = 24 / players;

  // No player with ID 0
  positions_.push_back(Field(0, 0));
  walls_.push_back(0);

  for (int i = 1; i <= players; i++) {
    Player player(i);
    Field position = Field(0, i);
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

}
