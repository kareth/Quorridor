#include "game/manager.h"

namespace game {

Manager::Manager(Board* board) : board_(board) {
}

Manager::~Manager() {
}

int Manager::DoMove(const Player& player, const Move& move) {
  // TODO
  if (move.type == kMove) {
    return MoveMan(player, move.from, move.to);
  } else if (move.type == kMove) {
    return PlaceWall(player, move.from, move.to);
  }

  return 1;
}

int Manager::MoveMan(const Player& player, const Field& from, const Field& to) {
  printf("Moving man\n");
  printf("%d %d -> %d %d\n",from.x, from.y, to.x, to.y);

  // TODO
  return 1;
}

int Manager::PlaceWall(const Player& player, const Field& from, const Field& to) {
  // TODO
  printf("Placing wall\n");
  printf("%d %d -> %d %d\n",from.x, from.y, to.x, to.y);

  return 1;
}

}
