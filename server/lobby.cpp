#include "server/lobby.h"
#include "server/connection.h"
#include "server/game_room.h"
#include <set>
#include <memory>
#include <unistd.h>

namespace server {

const logger::Logger Lobby::logger_("server.lobby");

Lobby::Lobby() {
  players_per_game_ = 2;
}

// TODO(kareth): mutex on sets!

void Lobby::Start(std::shared_ptr<Connection> connection) {
  connections_.insert(connection);
  waiting_.insert(connection);
  connection->Run();

  if (waiting_.size() >= players_per_game_)
    StartGame();
}

void Lobby::Stop(std::shared_ptr<Connection> connection) {
  connections_.erase(connection);
  if (waiting_.find(connection) != waiting_.end())
    waiting_.erase(connection);
  connection->Stop();
}

void Lobby::StopAll() {
  for (auto c : connections_) {
    c->Stop();
  }
  connections_.clear();
}

void Lobby::StartGame() {
  std::shared_ptr<GameRoom> room(new GameRoom(this, players_per_game_));
  for (auto c : waiting_) {
    if (room->players() < players_per_game_) {
      room->AddPlayer(c);
      c->AssignRoom(room);
    }
  }
  rooms_.insert(room);
  LOG_DEBUG(logger_, "Starting Game!");
  room->Run();
}

void Lobby::GameFinished(std::shared_ptr<GameRoom> room) {
  LOG_INFO(logger_, "Stopping game...");
  sleep(10);
  for (auto c : room->connections())
    Stop(c);
  rooms_.erase(room);
  LOG_INFO(logger_, "Game stopped");
}

}  // namespace server
