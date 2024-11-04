#include "MutexLock.h"
#include <stdio.h>

Mutexlock::Mutexlock() {
  int ret = pthread_mutex_init(&_lock, nullptr);
  if (ret) {
    perror("pthread_mutex_init");
    return;
  }
}

Mutexlock::~Mutexlock() {}

void Mutexlock::lock() {
  int ret = pthread_mutex_lock(&_lock);
  if (ret) {
    perror("pthread_mutex_lock");
    return;
  }
}
void Mutexlock::unlock() {
  int ret = pthread_mutex_unlock(&_lock);
  if (ret) {
    perror("pthread_mutex_unlock");
    return;
  }
}

pthread_mutex_t *Mutexlock::getlock() { return &_lock; }
