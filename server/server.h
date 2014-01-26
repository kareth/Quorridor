#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include "server/socket.h"
#include "server/acceptor.h"
#include "server/lobby.h"

namespace server {

class Server {
 public:
  Server(const std::string& address, const std::string& port);

  ~Server();

  void Start();

 private:
  static void StaticSignalHandler(int signum);
  void SignalHandler();

  std::string address_;
  std::string port_;

  Lobby lobby_;
  Acceptor acceptor_;

  static std::set<Server*> instances_;  // rly bad lol

  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SERVER_SERVER_H_
