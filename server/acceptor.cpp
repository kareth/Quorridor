#include "server/acceptor.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include <string>
#include <cstring>
#include <memory>

#include "server/socket.h"
#include "logger/logger.h"
#include "server/acceptor_exceptions.h"

using std::cout;
using std::cerr;
using std::endl;

namespace server {

const logger::Logger Acceptor::logger_("server.acceptor");

Acceptor::Acceptor() {
}

void Acceptor::Open() {
  sock_fd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd_ == -1) {
    LOG_ERROR(logger_, "Socket open error: " << strerror(errno))
    throw OpenError(strerror(errno));
  }
}

void Acceptor::Bind(const std::string& port) {
  port_ = port;

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(port.c_str()));
  addr.sin_addr.s_addr = INADDR_ANY;  // TODO(kareth): make it configurable

  if (bind(sock_fd_, (sockaddr*)&addr, sizeof(addr)) == -1) {
    LOG_ERROR(logger_, "Bind error: " << strerror(errno))
    throw BindError(strerror(errno));
  }
}

void Acceptor::Listen() {
  if (listen(sock_fd_, kListenBacklog) == -1) {
    LOG_ERROR(logger_, "Listen error: " << strerror(errno))
    throw ListenError(strerror(errno));
  }
}

void Acceptor::Close() {
  close(sock_fd_);
  LOG_DEBUG(logger_, "Socket closed")
}

void Acceptor::ReuseAddress(bool reuse_address) {
  char option;
  if (reuse_address) {
    option = 1;
    if (setsockopt(sock_fd_, SOL_SOCKET, SO_REUSEADDR, &option,  sizeof(int)) == -1) {
      LOG_ERROR(logger_, "Set reuse address error: " << strerror(errno))
      throw ReuseAddressError(strerror(errno));
    }
  } else {
    option = 0;
    if (setsockopt(sock_fd_, SOL_SOCKET, SO_REUSEADDR, &option,  sizeof(int)) == -1) {
      LOG_ERROR(logger_, "Clear reuse address error: " << strerror(errno))
      throw ReuseAddressError(strerror(errno));
    }
  }
}

std::unique_ptr<server::Socket> Acceptor::Accept() {
  LOG_DEBUG(logger_, "Waiting for socket")

  socklen_t socklen;
  sockaddr_in in_addr;
  socklen = sizeof(in_addr);

  int new_sock_fd = accept(sock_fd_, (sockaddr*)&in_addr, &socklen);
  if (new_sock_fd == -1) {
    LOG_ERROR(logger_, "Accept error: " << strerror(errno))
    throw server::AcceptError(strerror(errno));
  }

  LOG_INFO(logger_, "Accepted connection, socket id: " << new_sock_fd)

  return std::unique_ptr<server::Socket>(new server::Socket(new_sock_fd));
}

}  // namespace server
