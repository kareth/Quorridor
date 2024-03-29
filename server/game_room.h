#ifndef SERVER_GAME_ROOM_H_
#define SERVER_GAME_ROOM_H_

#include <memory>
#include <vector>

#include "thread/thread_interface.h"
#include "logger/logger.h"
#include "game/manager.h"
#include "thread/mutex.h"
#include "protocol/command.h"
#include "server/socket.h"

namespace server {

class Lobby;
class Connection;

class GameRoom : public thread::ThreadInterface, public std::enable_shared_from_this<GameRoom>  {
 public:
  GameRoom(Lobby* lobby, int players);
  void AddPlayer(std::shared_ptr<Connection> connection);
  void StopGame();

  void Unlock();

  int players() const { return players_.size(); }
  const std::vector<std::shared_ptr<Connection>>& connections() const {
    return players_; }

 private:
  virtual void* StartRoutine();

  void BroadcastBoard();
  void BroadcastWinner();
  void ProcessTurn(std::shared_ptr<Connection> connection, int id);
  void AskForData(std::shared_ptr<Connection> connection, protocol::Command command);
  void GameFailed();

  void Lock();

  char data_[server::Socket::kMaxBufferSize];
  Lobby* lobby_;
  game::Manager manager_;
  int winner_;
  bool failed_;

  thread::Mutex mutex_;

  std::vector<std::shared_ptr<Connection>> players_;

  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SERVER_GAME_ROOM_H_

