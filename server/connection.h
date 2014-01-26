#ifndef SERVER_CONNECTION_H_
#define SERVER_CONNECTION_H_

#include <memory>

#include "thread/thread_interface.h"
#include "server/socket.h"
#include "logger/logger.h"
#include "protocol/command.h"
#include "protocol/board.h"
#include "game/move.h"

namespace server {

class Lobby;
class GameRoom;

class Connection : public thread::ThreadInterface, public std::enable_shared_from_this<Connection> {
 public:
  explicit Connection(std::unique_ptr<Socket> socket,
    Lobby* lobby);

  void AssignRoom(std::shared_ptr<GameRoom> room);
  void SendCommand(const protocol::Command& command);
  void SendInteger(int data);
  void SendBoard(const protocol::Board& board);

  void WaitFor(char* data);

  void Stop();

 private:
  virtual void* StartRoutine();

  std::unique_ptr<Socket> socket_;
  Lobby* lobby_;
  std::shared_ptr<GameRoom> room_;

  int waiting_;
  char* waiting_object_;

  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SERVER_CONNECTION_H_
