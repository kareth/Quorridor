#include "logger/logger.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <ctime>
#include <cstdio>

#include "thread/mutex.h"

using logger::Logger;
using std::cout;
using std::endl;
using std::string;

Logger::Logger(const std::string& name)
  : name_(name) {
}

std::string Logger::CurrentTime() {
  using std::chrono::system_clock;

  auto now = system_clock::now();
  std::time_t tt = system_clock::to_time_t(now);

  char buf[80];
  struct tm tstruct;
  localtime_r(&tt, &tstruct);
  strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
  return std::string(buf);
}

inline static std::string CreateFileLine(const std::string& full_path, int line_number) {
  string file_name;
  std::size_t last_dot_pos = full_path.find_last_of("/");
  if (last_dot_pos != string::npos) {
    file_name = full_path.substr(last_dot_pos + 1);
  } else {
    file_name = full_path;
  }

  file_name += ":";
  file_name += std::to_string(line_number);

  return file_name;
}

void Logger::log(kMessageLevel message_level, const std::string& msg,
    pthread_t thread_id, int line_number,
    const std::string& file_name) const {

  if (message_level == DEBUG) return;

  const bool log_file_line =  false;

  mutex_.Lock();

  cout << std::left;
  cout
    << CurrentTime() << " "
    << MessageLevelToStr(message_level) << " "
    << "[" << std::setw(12) << std::setfill('0') << std::right << thread_id << "] ";
  if (log_file_line == true) {
    cout << std::setw(29) << std::setfill(' ') << std::left
      << CreateFileLine(file_name, line_number);
  } else {
    cout << std::setw(29) << std::setfill(' ') << std::left << name_ << " ";
  }
  cout
    << msg << " "
    << endl;

  mutex_.Unlock();
}

std::string Logger::MessageLevelToStr(kMessageLevel message_level) {
  switch (message_level) {
  case INFO:
    return " INFO";
  case WARN:
    return " WARN";
  case ERROR:
    return "ERROR";
  case DEBUG:
    return "DEBUG";
  default:
    return "-----";
  }
}
