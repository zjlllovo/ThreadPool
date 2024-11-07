#include "TcpConnection.h"
#include <sys/socket.h>

TcpConnection::TcpConnection(int fd) : _tcpio(fd) {}

TcpConnection::~TcpConnection() {}

void TcpConnection::send(const string msg) {
  _tcpio.sendn(msg.c_str(), msg.size());
}

string TcpConnection::recive() {
  char buf[65535] = {0};
  _tcpio.readLine(buf, sizeof(buf));
  return buf;
}

void TcpConnection::setNewEventCb(const eventcb &newEventfunc) {
  _newconncb = newEventfunc;
}
void TcpConnection::setOldEventCb(const eventcb &oldEventfunc) {
  _oldconncb = oldEventfunc;
}
void TcpConnection::setCloEventCb(const eventcb &cloEventfunc) {
  _closecb = cloEventfunc;
}

void TcpConnection::handNewConncb() { _newconncb(shared_from_this()); }
void TcpConnection::handOldConncb() { _oldconncb(shared_from_this()); }
void TcpConnection::handCloConncb() { _closecb(shared_from_this()); }

bool TcpConnection::isclosed() {
  char buf[10] = {0};
  int ret = ::recv(_tcpio.getfd(), buf, sizeof(buf), MSG_PEEK);
  return 0 == ret;
}
