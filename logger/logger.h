#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include <iostream>
#include <string>
#include <sstream>
#include <pthread.h>
#include <sys/types.h>

#include "thread/mutex.h"

namespace logger {

enum kMessageLevel {
  INFO,
  DEBUG,
  WARN,
  ERROR
};

class Logger {
 public:
  explicit Logger(const std::string& name);
  void log(kMessageLevel message_level, const std::string& msg,
    pthread_t thread_id, int line_number,
    const std::string& file_name) const;

  static std::string MessageLevelToStr(kMessageLevel message_level);

 private:
  static std::string CurrentTime();

  const std::string name_;
  mutable thread::Mutex mutex_;
};

}  // namespace logger

#define LOG_INFO(lg, msg) {\
  std::stringstream ss; ss << msg;\
  lg.log(logger::INFO, ss.str(), pthread_self(), __LINE__, __FILE__);\
  };

#define LOG_DEBUG(lg, msg) {\
  std::stringstream ss; ss << msg;\
  lg.log(logger::DEBUG, ss.str(), pthread_self(), __LINE__, __FILE__);\
  };

#define LOG_WARN(lg, msg) {\
  std::stringstream ss; ss << msg;\
  lg.log(logger::WARN, ss.str(), pthread_self(), __LINE__, __FILE__);\
  };

#define LOG_ERROR(lg, msg) {\
  std::stringstream ss; ss << msg;\
  lg.log(logger::ERROR, ss.str(), pthread_self(), __LINE__, __FILE__);\
  };

#endif  // LOGGER_LOGGER_H_
