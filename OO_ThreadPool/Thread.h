#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
class ThreadPool;

class Thread {
public:
  Thread(ThreadPool &threadpool);
  ~Thread();
  void start();
  void stop();
  static void *threadFunc(void *args);

  void run();

private:
  bool _isStart;
  pthread_t _pid;
  ThreadPool &_threadpool;
};
#endif // __THREAD_H__
