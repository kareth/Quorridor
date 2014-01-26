#ifndef SERVER_SOCKET_H_
#define SERVER_SOCKET_H_

#include <cstddef>
#include <string>

#include "logger/logger.h"

namespace server {

class Socket {
 public:
  explicit Socket(int sock_fd);
  ~Socket();

  // blocks, returns number of bytes read
  size_t Read(void* array, std::size_t max_bytes_count);
  // blocks, waits max tv_sec seconds and tv_usec microseconds
  // returns number of bytes read
  size_t Read(void* array, std::size_t max_bytes_count, int tv_sec, int tv_usec);

  void Write(const void* array, std::size_t bytes_count);

  void Connect(const std::string& address, const std::string& port);

  void Close();

  static const size_t kMaxBufferSize = 131072; //8192;

 private:
  const int sock_fd_;

  static const logger::Logger logger_;
};

}  // namespace server

#endif  // SERVER_SOCKET_H_
