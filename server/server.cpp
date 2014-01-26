#include "server/server.h"

#include <string>
#include <iostream>
#include <memory>
#include <signal.h>
#include <set>

namespace server {

const logger::Logger Server::logger_("server.server");

std::set<Server*> Server::instances_;

void Server::SignalHandler() {
  acceptor_.Close();
  lobby_.StopAll();
}

void Server::StaticSignalHandler(int signum) {
  LOG_INFO(Server::logger_, "Signal: " << signum)
  for (auto item : Server::instances_) {
    item->SignalHandler();
  }
}

Server::~Server() {
  instances_.erase(this);
}

Server::Server(const std::string& address, const std::string& port)
  : address_(address),
    port_(port),
    lobby_(),
    acceptor_() {
  LOG_INFO(logger_, "Address: " << address_)
  LOG_INFO(logger_, "Port: " << port_)

  // init acceptor
  acceptor_.Open();
  acceptor_.ReuseAddress(true);
  acceptor_.Bind(port_);
  acceptor_.Listen();

  // register signals
  instances_.insert(this);
  signal(SIGINT, StaticSignalHandler);
  signal(SIGTERM, StaticSignalHandler);
}

void Server::Start() {
  LOG_INFO(logger_, "Server is running")

  // accept
  while (true) {
    try {
      std::unique_ptr<Socket> socket = std::move(acceptor_.Accept());
      lobby_.Start(std::make_shared<Connection>(std::move(socket), &lobby_));
    }
    catch (...) {
      LOG_ERROR(logger_, "Unhandled exception")
      break;
    }
  }
}

}  // namespace server
