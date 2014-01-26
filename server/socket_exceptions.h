#ifndef SERVER_SOCKET_EXCEPTIONS_H_
#define SERVER_SOCKET_EXCEPTIONS_H_

#include <stdexcept>

namespace server {

typedef std::runtime_error SocketError;

class ReadError : public SocketError {
 public:
  explicit ReadError(const char* error)
    : SocketError(error) {
  }
};

class WriteError : public SocketError {
 public:
  explicit WriteError(const char* error)
    : SocketError(error) {
  }
};

class SelectError : public SocketError {
 public:
  explicit SelectError(const char* error)
    : SocketError(error) {
  }
};

class ConnectError : public SocketError {
 public:
  explicit ConnectError(const char* error)
    : SocketError(error) {
  }
};

}  // namespace server

#endif  // SERVER_SOCKET_EXCEPTIONS_H_
