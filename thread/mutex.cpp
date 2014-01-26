#include "thread/mutex.h"

#include <pthread.h>

using thread::Mutex;

Mutex::Mutex() {
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutex_init(&mutex_, &attr);
}

Mutex::~Mutex() {
  pthread_mutex_destroy(&mutex_);
}

void Mutex::Lock() {
  pthread_mutex_lock(&mutex_);
}

void Mutex::Unlock() {
  pthread_mutex_unlock(&mutex_);
}
