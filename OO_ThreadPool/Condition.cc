#include "Condition.h"
#include <pthread.h>
#include <stdio.h>

Condition::Condition(Mutexlock &mutexlock) : _mutexlock(mutexlock) {
  int ret = pthread_cond_init(&_cond, nullptr);
  if (ret) {
    perror("pthread_cond_init");
    return;
  }
}

Condition::~Condition() {}

void Condition::notefly() {
  int ret = pthread_cond_signal(&_cond);
  if (ret) {
    perror("pthread_cond_signal");
    return;
  }
}

void Condition::noteflyAll() {
  int ret = pthread_cond_broadcast(&_cond);
  if (ret) {
    perror("pthread_cond_broadcast");
    return;
  }
}

void Condition::wait() {
  int ret = pthread_cond_wait(&_cond, _mutexlock.getlock());
  if (ret) {
    perror("pthread_cond_wait");
    return;
  }
}
