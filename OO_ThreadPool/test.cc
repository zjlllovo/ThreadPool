#include "Task.h"
#include "ThreadPool.h"

int main() {
  Task *ptask;
  ThreadPool tpl(4, 10);
  tpl.start();
  int cnt = 20;
  while (cnt--) {
    tpl.addTask(ptask);
  }
  tpl.stop();
}
