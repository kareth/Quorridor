#ifndef SRC_THREAD_MUTEX_H_
#define SRC_THREAD_MUTEX_H_

#include <pthread.h>

namespace thread {

class Mutex {
 public:
  Mutex();
  ~Mutex();

  void Lock();
  void Unlock();

 private:
  pthread_mutex_t mutex_;
};

}  // namespace thread

#endif  // SRC_THREAD_MUTEX_H_
