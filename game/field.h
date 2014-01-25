#ifndef GAME_FIELD_H_
#define GAME_FIELD_H_

namespace game {

struct Field {
  int x, y;
  Field() {}
  Field(int x, int y) : x(x), y(y) {}

  bool operator < (const Field& rhs) const {
    if (x < rhs.x) return 1;
    if (x > rhs.x) return 0;
    return y < rhs.y;
  }
  bool operator == (const Field& rhs) const { return x == rhs.x && y == rhs.y; }
  bool operator != (const Field& rhs) const { return !operator==(rhs); }
};

}  // namespace game

#endif  // GAME_FIELD_H_
