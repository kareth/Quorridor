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
  winner_(-1), manager_(9, players) {
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
      if (winner_ != -1)
        break;
    }
    if (winner_ != -1)
      break;
  }

  BroadcastWinner();

  lobby_->GameFinished(shared_from_this());
  return nullptr;
}

void GameRoom::AddPlayer(std::shared_ptr<Connection> connection) {
  players_.push_back(connection);
}

void GameRoom::BroadcastBoard() {
  protocol::Board board = manager_.board().Serialize();
  for (auto connection : players_) {
    connection->SendCommand(protocol::kBoardInfo);
    connection->SendBoard(board);
  }
}

void GameRoom::ProcessTurn(std::shared_ptr<Connection> connection, int id) {
  for (int i = 0; i < players_.size(); i++)
    if (i + 1 != id)
      players_[i]->SendCommand(protocol::kAnotherPlayerTurn);

  // TODO slow?
  char data[server::Socket::kMaxBufferSize];
  mutex_.Lock();
  connection->WaitFor(data);
  connection->SendCommand(protocol::kMoveRequest);

  // Connection is supposed to unlock it once data is received
  mutex_.Lock();
  // Assure that its unlocked all the time outside this method
  mutex_.Unlock();

  game::Move* move = (struct game::Move*)&data;

  if (manager_.DoMove(id, *move)) {
    connection->SendCommand(protocol::kCorrectMove);
  } else {
    connection->SendCommand(protocol::kInvalidMove);
    ProcessTurn(connection, id);
  }
}

void GameRoom::BroadcastWinner() {
  for (auto c : players_) {
    c->SendCommand(protocol::kGameFinished);
    c->SendInteger(winner_);
  }
}

void GameRoom::Lock() {
  mutex_.Lock();
}

void GameRoom::Unlock() {
  mutex_.Unlock();
}

}  // namespace server
