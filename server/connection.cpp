#include "server/connection.h"

#include <memory>
#include <iostream>
#include <string>
#include <cassert>

#include "server/socket.h"
#include "server/lobby.h"
#include "logger/logger.h"
#include "protocol/command.h"
#include "server/game_room.h"

namespace server {

const logger::Logger Connection::logger_("server.connection");

Connection::Connection(std::unique_ptr<Socket> socket, Lobby* lobby)
  : socket_(std::move(socket)), lobby_(lobby), room_(nullptr), up_(0) {
}

void* Connection::StartRoutine() {
  LOG_DEBUG(logger_, "Starting connection");
  up_ = true;

  SendCommand(protocol::WaitingForOpponents);

  char buffer[Socket::kMaxBufferSize];

  while (true) {
    int size;
    try {
      size = socket_->Read(buffer, Socket::kMaxBufferSize);
    } catch (...) {
      ConnectionStopped();
      break;
    }

    if (size == 0) {
      ConnectionStopped();
      break;
    }

    if (waiting_ == true) {
      memcpy(waiting_object_, buffer, size);
      waiting_ = false;
      room_->Unlock();
    } else {
      protocol::Command* command = (struct protocol::Command*) buffer;
      LOG_DEBUG(logger_, "Unhandled command")
    }
  }
  return nullptr;
}

void Connection::SendCommand(const protocol::Command& command) {
  if (up_)
    socket_->Write(&command, sizeof(command));
}

void Connection::SendInteger(int data) {
  if (up_)
    socket_->Write(&data, sizeof(data));
}

void Connection::AssignRoom(std::shared_ptr<GameRoom> room) {
  room_ = room;
}

void Connection::Stop() {
  socket_->Close();
}

void Connection::ConnectionStopped() {
  up_ = false;
  LOG_INFO(logger_, "Client disconnected");
  if (room_) {
    room_->Unlock();
    room_->StopGame();
  }
}

void Connection::WaitFor(char* data) {
  waiting_ = true;
  waiting_object_ = data;
}

void Connection::SendBoard(const protocol::Board& board) {
  if (up_)
    socket_->Write(&board, sizeof(struct protocol::Board));
}

}  // namespace server
