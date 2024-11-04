#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "MutexLock.h"

class Condition {
public:
  Condition(Mutexlock &mutexlock);
  ~Condition();

  void notefly();
  void noteflyAll();
  void wait();

private:
  pthread_cond_t _cond;
  Mutexlock &_mutexlock;
};
#endif // __CONDITION_H__
