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
  : socket_(std::move(socket)), lobby_(lobby) {
}

void* Connection::StartRoutine() {
  LOG_DEBUG(logger_, "Starting connection")

  while (true) {
    char buffer[Socket::kMaxBufferSize];

      int size = socket_->Read(buffer, Socket::kMaxBufferSize);

    // TODO kareth
    if (size == 0)
      return nullptr;

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
  socket_->Write(&command, sizeof(command));
}

void Connection::SendInteger(int data) {
  socket_->Write(&data, sizeof(data));
}

void Connection::AssignRoom(std::shared_ptr<GameRoom> room) {
  room_ = room;
}

void Connection::Stop() {
  socket_->Close();
}

void Connection::WaitFor(char* data) {
  waiting_ = true;
  waiting_object_ = data;
}

void Connection::SendBoard(const protocol::Board& board) {
  socket_->Write(&board, sizeof(struct protocol::Board));
}

}  // namespace server
