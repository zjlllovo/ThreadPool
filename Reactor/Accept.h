#ifndef __ACCEPT_H__
#define __ACCEPT_H__

#include "InetAddress.h"
#include "Socket.h"

class Accept {
public:
  Accept(const string ip, unsigned short port);
  ~Accept();

  void setReusePort();
  void setReuseAddr();

  void bind();
  void listen();
  int accpet();

  void ready();

  int getfd();

private:
  Socket _socket;
  InetAddress _inetaddr;
};
#endif // __ACCEPT_H__
