#include "Accept.h"
#include "EventLoop.h"
#include <iostream>

using std::cout;
using std::endl;

void onNewfunc(const TcpConnectionptr &on) { cout << "connection" << endl; }

void onMessge(const TcpConnectionptr &on) {
  string msg = on->recive();
  on->send(msg);
  cout << ">>recv client msg = " << msg << endl;
}

void onClofunc(const TcpConnectionptr &on) {
  cout << "connection is closed" << endl;
}

int main() {
  Accept acp("127.0.0.1", 8888);
  acp.ready();

  EventLoop loop(acp);
  loop.setNewEventCb(onNewfunc);
  loop.setOldEventCb(onMessge);
  loop.setCloEventCb(onClofunc);
  loop.loop();
  loop.unloop();
}
