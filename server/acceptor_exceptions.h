#ifndef SERVER_ACCEPTOR_EXCEPTIONS_H_
#define SERVER_ACCEPTOR_EXCEPTIONS_H_

#include <stdexcept>

namespace server {

typedef std::runtime_error AcceptorError;

class AcceptError : public AcceptorError {
 public:
  explicit AcceptError(const char* error)
    : AcceptorError(error) {
  }
};

class OpenError : public AcceptorError {
 public:
  explicit OpenError(const char* error)
    : AcceptorError(error) {
  }
};

class BindError : public AcceptorError {
 public:
  explicit BindError(const char* error)
    : AcceptorError(error) {
  }
};

class ListenError : public AcceptorError {
 public:
  explicit ListenError(const char* error)
    : AcceptorError(error) {
  }
};

class ReuseAddressError : public AcceptorError {
 public:
  explicit ReuseAddressError(const char* error)
    : AcceptorError(error) {
  }
};

}  // namespace server

#endif  // SERVER_ACCEPTOR_EXCEPTIONS_H_
