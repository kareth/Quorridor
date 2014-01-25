#ifndef GAME_FIELD_H_
#define GAME_FIELD_H_

namespace game {

struct Field {
 int x, y;
 Field() {}
 Field(int x, int y) : x(x), y(y) {}
};

}  // namespace game

#endif  // GAME_FIELD_H_
