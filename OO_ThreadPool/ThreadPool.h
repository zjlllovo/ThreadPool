#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "TaskQue.h"
#include "Thread.h"
#include <iostream>
#include <vector>

class ThreadPool {
public:
  ThreadPool(int poolsize, int quesize);
  ~ThreadPool();
  void start();
  void stop();

  void addTask(ElemType task);
  ElemType getTask();
  void doTask();

private:
  bool _isExit;
  int _poolsize;
  int _quesize;
  std::vector<Thread> _tpool;
  TaskQue _taskque;
};
#endif // __THREADPOOL_H__
