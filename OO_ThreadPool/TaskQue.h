#ifndef __TASKQUE_H__
#define __TASKQUE_H__

#include "Condition.h"
#include "MutexLock.h"
#include "Task.h"
#include <queue>

using std::queue;

using ElemType = Task *;

class TaskQue {
public:
  TaskQue(size_t quesize);
  ~TaskQue();

  void push(ElemType val);
  ElemType pop();

  bool isFull();
  bool isEmpty();

private:
  size_t _quesize;
  queue<ElemType> _que;
  Mutexlock _mutex;
  Condition _condtion;
};
#endif // __TASKQUE_H__
