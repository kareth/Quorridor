#include "game/board.h"

#include <cstdio>
#include <stdlib.h>

namespace game {

Board::Board(int size) : size_(size), blocked_(),
  fields_(size, std::vector<int>(size, 0)) {
}

void Board::PlaceMan(const Player& player, const Field& position) {
  fields_[position.x][position.y] = player.id;
}

int Board::PlaceWall(const Field& from, const Field& to) {
  if (from.x == to.x) { // Horizontal
    if (from.y + 1 != to.y) return 0;
    Field from_opp(from.x + 1, from.y);
    Field to_opp(to.x + 1, to.y);
    return AddBlocks(from, from_opp, to, to_opp);
  } else if (from.y == to.y) { // Vertical
    if (from.x + 1 != to.x) return 0;
    Field from_opp(from.x, from.y + 1);
    Field to_opp(to.x, to.y + 1);
    return AddBlocks(from, from_opp, to, to_opp);
  } else {
    return 0;
  }
}

bool Board::AddBlocks(const Field& from, const Field& from_opp,
                      const Field& to, const Field& to_opp) {
  if (IsBlocked(from, from_opp) ||
      IsBlocked(to, to_opp))
    return 0;

  if (IsBlocked(from, to) &&
      IsBlocked(from_opp, to_opp))
    return 0;

  Block(from, from_opp);
  Block(to, to_opp);
  return 1;
}

void Board::Block(const Field& from, const Field& to) {
  blocked_[std::make_pair(from, to)] = true;
  blocked_[std::make_pair(to, from)] = true;
}

int Board::MoveMan(const Field& from, const Field& to) {
  if (fields_[to.x][to.y] != 0)
    return 0;

  if (fields_[from.x][from.y] == 0)
    return 0;

  if (IsBlocked(from, to))
    return 0;

  int dx = abs(from.x - to.x);
  int dy = abs(from.y - to.y);
  if (!((dx == 0 && dy == 1) || (dx == 1 && dy == 0)))
    return 0;

  fields_[to.x][to.y] = fields_[from.x][from.y];
  fields_[from.x][from.y] = 0;
  return 1;
}

bool Board::IsBlocked(const Field& from, const Field& to) const {
  if (blocked_.find(std::make_pair(from, to)) != blocked_.end())
    return true;
  else
    return false;
}

}  // namespace game
