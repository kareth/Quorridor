#include "client/client.h"

#include <cstdio>
#include "game/manager.h"
#include "game/move.h"

namespace client {

Client::Client(const visualization::Display& display,
               const control::Input& input)
  : display_(display), input_(input) {
}

void Client::Start() {
  game::Board b;
  game::Manager manager(&b);
  while(1) {
    display_.ShowBoard(b);
    game::Move move;
    input_.GetMove(&move);
    while (!manager.DoMove(0, move)) {
      printf("Invalid move.\n");
      input_.GetMove(&move);
    }
    printf("OK.\n");
  }
}

}  // namespace client
