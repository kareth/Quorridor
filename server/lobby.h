#ifndef SERVER_LOBBY_H_
#define SERVER_LOBBY_H_

#include <set>
#include <memory>

#include "server/connection.h"
#include "logger/logger.h"

namespace server {

class Lobby {
 public:
  Lobby();

  void Start(std::shared_ptr<Connection> connection);
  void Stop(std::shared_ptr<Connection> connection);
  void StopAll();
  void GameFinished(std::shared_ptr<GameRoom> room);

 private:
  void StartGame();

  std::set<std::shared_ptr<Connection>> connections_;
  std::set<std::shared_ptr<Connection>> waiting_;
  std::set<std::shared_ptr<GameRoom>> rooms_;

  int players_per_game_;

  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SERVER_LOBBY_H_
