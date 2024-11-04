#include "ThreadPool.h"
#include "TaskQue.h"
#include <unistd.h>

ThreadPool::ThreadPool(int poolsize, int quesize)
    : _isExit(false), _poolsize(poolsize), _quesize(quesize),
      _taskque(_quesize) {}

ThreadPool::~ThreadPool() {}

void ThreadPool::start() {
  for (int i = 0; i < _poolsize; i++) {
    Thread th(*this);
    _tpool.push_back(th);
  }
  for (auto &it : _tpool) {
    it.start();
  }
}

void ThreadPool::stop() {
  while (!_taskque.isEmpty()) {
    sleep(1);
  }
  _isExit = true;
  for (auto &it : _tpool) {
    it.stop();
  }
}

ElemType ThreadPool::getTask() { return _taskque.pop(); }

void ThreadPool::addTask(ElemType task) { _taskque.push(task); }

void ThreadPool::doTask() {
  while (!_isExit) {
    ElemType ptask = getTask();
    if (ptask) {
      ptask->process();
    } else {
      std::cout << "ptask is null" << std::endl;
    }
  }
}
