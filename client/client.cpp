#include "client/client.h"

#include <cstdio>
#include "game/manager.h"
#include "game/move.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>

#include "protocol/command.h"
#include "protocol/board.h"


namespace client {

const logger::Logger Client::logger_("client.client");

Client::Client(const std::string& address, const std::string& port,
    const visualization::Display& display, const control::Input& input)
  : address_(address), port_(port), display_(display), input_(input),
    socket_() {
}

void Client::InitializeSocket() {
  socket_fd_ = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (socket_fd_ == -1) {
    LOG_ERROR(logger_, "Socket open error: " << strerror(errno))
    throw;
  }
  std::unique_ptr<server::Socket> sock(new server::Socket(socket_fd_));
  socket_ = std::move(sock);
}

void Client::Start() {
  InitializeSocket();

  try {
    socket_->Connect(address_, port_);
  } catch (...) {
    LOG_ERROR(logger_, "Unhandled exception")
  }

  //signal(SIGINT, [](int signum) { sock.Close(); raise(signum);});
  //signal(SIGTERM, [](int signum) { sock.Close(); raise(signum);});

  while (1) {
    int status;
    try {
      status = Read(sizeof(struct protocol::Command));
    } catch (...) {
      LOG_ERROR(logger_, "Server socked stopped working");
      break;
    }

    if (status == 0) {
      LOG_ERROR(logger_, "Server socked stopped working");
      break;
    }

    protocol::Command* command = (struct protocol::Command*)&buffer_;

    if (command->type == protocol::kGameStarted) {
      display_.ShowMessageFor(*command);
      player_id_ = ReadInt();
      display_.ShowPlayerInfo(player_id_);
    }
    else if (command->type == protocol::kMoveRequest) {
      game::Move move;
      input_.GetMove(&move);
      socket_->Write(&move, sizeof(struct game::Move));
    }
    else if (command->type == protocol::kBoardInfo) {
      Read(sizeof(struct protocol::Board));
      protocol::Board* serialized_board = (struct protocol::Board*)&buffer_;
      game::Board board(*serialized_board);
      display_.ShowBoard(board);
    }
    else if (command->type == protocol::kGameFinished) {
      int winner_id = ReadInt();
      display_.ShowWinner(winner_id, player_id_);
      return;
    }
    else if (command->type == protocol::kWalls) {
      int walls = ReadInt();
      display_.ShowWalls(walls);
    }
    else if (command->type == protocol::kGameFailed) {
      display_.ShowMessageFor(*command);
      return;
    }
    else {
      display_.ShowMessageFor(*command);
    }
  }
}

int Client::Read(int size) {
  int status = socket_->Read(buffer_, size);

  if (status == 0) {
    LOG_ERROR(logger_, "Server error: " << strerror(errno));
  }
  return status;
}

int Client::ReadInt() {
  Read(sizeof(int));
  int* val = (int*) &buffer_;
  return *val;
}

}  // namespace client
