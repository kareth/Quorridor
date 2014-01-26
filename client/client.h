#ifndef CLIENT_CLIENT_H_
#define CLIENT_CLIENT_H_

#include <memory>

#include "server/socket.h"
#include "logger/logger.h"
#include "game/board.h"
#include "control/input.h"
#include "visualization/display.h"

namespace client {

class Client {
 public:
  Client(const std::string& address, const std::string& port,
      const visualization::Display& display, const control::Input& input);

  void Start();

 private:
  int Read(int size = server::Socket::kMaxBufferSize);
  int ReadInt();

  void InitializeSocket();

  // Client application methods
  const visualization::Display& display_;
  const control::Input& input_;

  // Socket
  int socket_fd_;
  std::unique_ptr<server::Socket> socket_;

  // Reading buffer
  char buffer_[server::Socket::kMaxBufferSize];

  // Assigned id by game
  int player_id_;

  // Params
  std::string address_;
  std::string port_;

  static const logger::Logger logger_;
};

}  // namespace client

#endif  // CLIENT_CLIENT_H_
