#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__
#include <pthread.h>

class Mutexlock {
public:
  Mutexlock();
  ~Mutexlock();

  void lock();
  void unlock();

  pthread_mutex_t *getlock();

private:
  pthread_mutex_t _lock;
};
#endif // __MUTEXLOCK_H__
