#ifndef __TASK_H__
#define __TASK_H__

#include <iostream>

#include <stdlib.h>
#include <time.h>

class Task {
public:
  Task();
  ~Task();
  void process() {
    ::srand(::clock());
    int number = ::rand() % 100;
    std::cout << ">>myTask process number is " << number << std::endl;
  }

private:
};
#endif // __TASK_H__
