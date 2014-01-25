#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

namespace game {

struct Player {
  int id;
  Player();
  Player(int id) : id(id) {}

  bool operator < (const Player& p) const { return id < p.id; }
  bool operator == (const Player& rhs) const { return id == rhs.id; }
  bool operator != (const Player& rhs) const { return !operator==(rhs); }

};

}  // namespace gamem

#endif  // GAME_PLAYER_H_
