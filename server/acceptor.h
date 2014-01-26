#ifndef SERVER_ACCEPTOR_H_
#define SERVER_ACCEPTOR_H_

#include <string>
#include <memory>

#include "server/socket.h"
#include "logger/logger.h"

namespace server {

class Acceptor {
 public:
  Acceptor();

  void Open();
  void Bind(const std::string& port);
  void Listen();

  void Close();

  // blocks until the connection is present
  std::unique_ptr<server::Socket> Accept();

  void ReuseAddress(bool reuse_address);

  static const int kListenBacklog = 5;
 private:
  int sock_fd_;

  std::string port_;

  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SERVER_ACCEPTOR_H_
