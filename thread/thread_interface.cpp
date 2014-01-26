#include "thread/thread_interface.h"

#include <pthread.h>

namespace thread {

ThreadInterface::ThreadInterface() {
}

ThreadInterface::~ThreadInterface() {
}

void ThreadInterface::Run() {
  pthread_create(&thread, NULL, StaticRoutine, (void*)this);
}

void ThreadInterface::Wait() {
  pthread_join(thread, NULL);
}

void* ThreadInterface::StaticRoutine(void* arg) {
  ThreadInterface *ithread = (ThreadInterface*)arg;
  return ithread->StartRoutine();
}

}  // namespace thread
