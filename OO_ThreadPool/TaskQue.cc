#include "TaskQue.h"

TaskQue::TaskQue(size_t quesize)
    : _flag(true), _quesize(quesize), _mutex(), _condtion(_mutex) {}

TaskQue::~TaskQue() {}

bool TaskQue::isFull() { return _que.size() == _quesize; }

bool TaskQue::isEmpty() { return _que.size() == 0; }

void TaskQue::push(ElemType val) {
  _mutex.lock();
  while (isFull()) {
    _condtion.wait();
  }
  _que.push(val);
  _condtion.notefly();
  _mutex.unlock();
}

ElemType TaskQue::pop() {
  _mutex.lock();
  while (_flag && isEmpty()) {
    _condtion.wait();
  }
  if (_flag) {
    ElemType tmp = _que.front();
    _que.pop();
    _condtion.notefly();
    _mutex.unlock();
    return tmp;
  } else {
    _mutex.unlock();
    return nullptr;
  }
}

void TaskQue::wakeup() {
  _flag = false;
  _condtion.noteflyAll();
}
