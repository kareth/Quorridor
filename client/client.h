#ifndef CLIENT_CLIENT_H_
#define CLIENT_CLIENT_H_

#include <memory>

#include "game/board.h"
#include "visualization/display.h"
#include "control/input.h"
#include "server/socket.h"

#include "logger/logger.h"

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

  const visualization::Display& display_;
  const control::Input& input_;

  int socket_fd_;
  char buffer_[server::Socket::kMaxBufferSize];
  int player_id_;
  std::unique_ptr<server::Socket> socket_;

  std::string address_;
  std::string port_;
  static const logger::Logger logger_;
};

}  // namespace client

#endif  // CLIENT_CLIENT_H_
