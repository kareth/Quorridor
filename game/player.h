#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

namespace game {

struct Player {
  int id;
  Player();
  Player(int id) : id(id) {}
};

}  // namespace gamem

#endif  // GAME_PLAYER_H_
