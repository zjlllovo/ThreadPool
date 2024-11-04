#include "Thread.h"
#include "ThreadPool.h"
#include <iostream>
#include <pthread.h>

Thread::Thread(ThreadPool &threadpool)
    : _isStart(false), _pid(0), _threadpool(threadpool) {}

Thread::~Thread() {}

void Thread::start() {
  int ret = pthread_create(&_pid, nullptr, threadFunc, this);
  if (ret) {
    perror("pthread_start");
    return;
  }
  _isStart = true;
}

void Thread::stop() {
  int ret = pthread_join(_pid, nullptr);
  if (ret) {
    perror("pthread_join");
    return;
  }
}

void *Thread::threadFunc(void *args) {
  Thread *pth = static_cast<Thread *>(args);
  if (pth) {
    pth->_threadpool.doTask();
  } else {
    std::cout << "pth is null" << std::endl;
  }
  pthread_exit(nullptr);
}
