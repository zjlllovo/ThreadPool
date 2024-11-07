#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__

#include "Accept.h"
#include "TcpConnection.h"
#include <sys/epoll.h>

#include <functional>
#include <map>
#include <memory>
#include <vector>

using std::function;
using std::map;
using std::shared_ptr;
using std::vector;

using TcpConnectionptr = shared_ptr<TcpConnection>;
using eventcb = function<void(const TcpConnectionptr &)>;

class EventLoop {
public:
  EventLoop(Accept &accept);
  ~EventLoop();

  void loop();
  void unloop();

  void waitEvent();
  void handNewMsg();
  void handOldCon(int fd);

  int createEpfd();
  void addFdEvlist(int fd);
  void delFdEvlist(int fd);

  void setNewEventCb(const eventcb &newEventfunc);
  void setOldEventCb(const eventcb &oldEventfunc);
  void setCloEventCb(const eventcb &cloEventfunc);

private:
  bool _isLooping;
  int _epfd;
  Accept &_accept;
  map<int, shared_ptr<TcpConnection>> _tcpcon;
  vector<struct epoll_event> _evlist;

  eventcb _newconncb;
  eventcb _oldconncb;
  eventcb _closecb;
};
#endif // __EVENTLOOP_H__
