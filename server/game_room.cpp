#include "server/game_room.h"
#include "server/lobby.h"
#include "server/connection.h"
#include "protocol/command.h"
#include "server/socket.h"
#include "game/move.h"
#include "game/field.h"

namespace server {

const logger::Logger GameRoom::logger_("server.game_room");

GameRoom::GameRoom(Lobby* lobby, int players) : lobby_(lobby),
  winner_(-1), manager_(9, players), failed_(false) {
}

void* GameRoom::StartRoutine() {

  for (int i = 0; i < players_.size(); i++) {
    players_[i]->SendCommand(protocol::kGameStarted);
    players_[i]->SendInteger(i + 1);
  }

  while (true) {
    for (int i = 0; i < players_.size(); i++) {
      BroadcastBoard();
      ProcessTurn(players_[i], i+1);
      winner_ = manager_.getWinner();
      if (winner_ != -1 || failed_ == true)
        break;
    }
    if (winner_ != -1 || failed_ == true)
      break;
  }

  if (failed_)
    GameFailed();
  else
    BroadcastWinner();

  lobby_->GameFinished(shared_from_this());
  return nullptr;
}

void GameRoom::AddPlayer(std::shared_ptr<Connection> connection) {
  players_.push_back(connection);
}

void GameRoom::BroadcastBoard() {
  protocol::Board board = manager_.board().Serialize();
  for (int i = 0; i < players_.size(); i++) {
    auto connection = players_[i];
    connection->SendCommand(protocol::kBoardInfo);
    connection->SendBoard(board);
    connection->SendCommand(protocol::kWalls);
    connection->SendInteger(manager_.walls(i+1));
  }
}

void GameRoom::ProcessTurn(std::shared_ptr<Connection> connection, int id) {
  if (failed_ == true) return;
  for (int i = 0; i < players_.size(); i++)
    if (i + 1 != id)
      players_[i]->SendCommand(protocol::kAnotherPlayerTurn);

  AskForData(connection, protocol::kMoveRequest);

  game::Move* move = (struct game::Move*)&data_;

  if (manager_.DoMove(id, *move)) {
    connection->SendCommand(protocol::kCorrectMove);
  } else {
    connection->SendCommand(protocol::kInvalidMove);
    ProcessTurn(connection, id);
  }
}

void GameRoom::AskForData(std::shared_ptr<Connection> connection, protocol::Command command) {
  // TODO slow?
  mutex_.Lock();
  connection->WaitFor(data_);
  connection->SendCommand(command);

  // Connection is supposed to unlock it once data is received
  mutex_.Lock();
  // Assure that its unlocked all the time outside this method
  mutex_.Unlock();
}

void GameRoom::BroadcastWinner() {
  for (auto c : players_) {
    c->SendCommand(protocol::kGameFinished);
    c->SendInteger(winner_);
  }
}

void GameRoom::GameFailed() {
  LOG_ERROR(logger_, "Game failed")
  for (auto c : players_) {
    c->SendCommand(protocol::kGameFailed);
  }
}

void GameRoom::StopGame() {
  failed_ = true;
}

void GameRoom::Lock() {
  mutex_.Lock();
}

void GameRoom::Unlock() {
  mutex_.Unlock();
}

}  // namespace server
