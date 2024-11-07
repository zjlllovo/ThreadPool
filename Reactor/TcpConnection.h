#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "TcpIO.h"
#include <functional>
#include <memory>
#include <string>

using std::function;
using std::shared_ptr;
using std::string;

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
  using TcpConnectionptr = shared_ptr<TcpConnection>;
  using eventcb = function<void(const TcpConnectionptr &)>;

public:
  TcpConnection(int fd);
  ~TcpConnection();

  void send(const string);
  string recive();

  void setNewEventCb(const eventcb &newEventfunc);
  void setOldEventCb(const eventcb &oldEventfunc);
  void setCloEventCb(const eventcb &cloEventfunc);

  void handNewConncb();
  void handOldConncb();
  void handCloConncb();

  bool isclosed();

private:
  TcpIO _tcpio;

  eventcb _newconncb;
  eventcb _oldconncb;
  eventcb _closecb;
};
#endif // __TCPCONNECTION_H__
