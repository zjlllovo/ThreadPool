#include "EventLoop.h"
#include "TcpConnection.h"
#include <cerrno>
#include <iostream>
#include <sys/epoll.h>

EventLoop::EventLoop(Accept &accept)
    : _isLooping(false), _epfd(createEpfd()), _accept(accept), _evlist(1024) {
  addFdEvlist(_accept.getfd());
}

EventLoop::~EventLoop() {}

void EventLoop::loop() {
  _isLooping = true;
  while (_isLooping) {
    waitEvent();
  }
}

void EventLoop::unloop() { _isLooping = false; }

void EventLoop::waitEvent() {
  int nready = epoll_wait(_epfd, &*_evlist.begin(), _evlist.size(), 3000);
  if (nready == -1 && errno & EINTR) {
    return;
  } else if (nready == -1) {
    perror("epoll_wait error");
    return;
  } else if (nready == 0) {
    std::cout << ">>epoll_wait timeout<<" << std::endl;
  } else {
    for (int idx = 0; idx < nready; idx++) {
      int fd = _evlist[idx].data.fd;
      if (fd == _accept.getfd()) {
        handNewMsg();
      } else {
        handOldCon(fd);
      }
    }
  }
}

void EventLoop::handNewMsg() {
  int connfd = _accept.accpet();
  addFdEvlist(connfd);
  shared_ptr<TcpConnection> tcp(new TcpConnection(connfd));
  tcp->setNewEventCb(_newconncb);
  tcp->setOldEventCb(_oldconncb);
  tcp->setCloEventCb(_closecb);
  _tcpcon.insert(make_pair(connfd, tcp));
  tcp->handNewConncb();
}

void EventLoop::handOldCon(int fd) {
  auto it = _tcpcon.find(fd);
  if (it != _tcpcon.end()) {
    // 找到了
    if (it->second->isclosed()) {
      it->second->handCloConncb();
      delFdEvlist(fd);
    } else {
      it->second->handOldConncb();
    }
  } else {
    std::cout << "conn no exit" << std::endl;
    return;
  }
}

int EventLoop::createEpfd() {
  int fd = epoll_create1(0);
  if (fd < 0) {
    perror("create epfd");
    return -1;
  }
  return fd;
}

void EventLoop::addFdEvlist(int fd) {
  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = fd;
  int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &ev);
  if (ret < 0) {
    perror("epoll_ctl_ADD");
    return;
  }
}

void EventLoop::delFdEvlist(int fd) {
  struct epoll_event ev;
  ev.events = EPOLLOUT;
  ev.data.fd = fd;
  int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &ev);
  if (ret < 0) {
    perror("epoll_ctl_DEL");
    return;
  }
}

void EventLoop::setNewEventCb(const eventcb &newEventfunc) {
  _newconncb = newEventfunc;
}

void EventLoop::setOldEventCb(const eventcb &oldEventfunc) {
  _oldconncb = oldEventfunc;
}

void EventLoop::setCloEventCb(const eventcb &cloEventfunc) {
  _closecb = cloEventfunc;
}
