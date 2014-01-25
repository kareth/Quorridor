#ifndef CLIENT_CLIENT_H_
#define CLIENT_CLIENT_H_

#include "game/board.h"
#include "visualization/display.h"
#include "control/input.h"

namespace client {

class Client {
 public:
  Client(const visualization::Display& display, const control::Input& input);

  void Start();

 private:

  const visualization::Display& display_;
  const control::Input& input_;
};

}  // namespace client

#endif  // CLIENT_CLIENT_H_
