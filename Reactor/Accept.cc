#include "Accept.h"
#include <asm-generic/socket.h>
#include <cstdio>
#include <sys/socket.h>

Accept::Accept(const string ip, unsigned short port)
    : _socket(), _inetaddr(ip, port) {}
Accept::~Accept() {}

void Accept::setReusePort() {
  int opt = 0;
  int ret =
      setsockopt(_socket.getfd(), SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
  if (ret) {
    perror("setReusePort");
    return;
  }
}
void Accept::setReuseAddr() {

  int opt = 0;
  int ret =
      setsockopt(_socket.getfd(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  if (ret) {
    perror("setReuseAddr");
    return;
  }
}

void Accept::bind() {
  int ret = ::bind(_socket.getfd(), (struct sockaddr *)(_inetaddr.getaddr()),
                   sizeof(sockaddr_in));
  if (ret < 0) {
    perror("bind");
    return;
  }
}
void Accept::listen() {
  int ret = ::listen(_socket.getfd(), 0);
  if (ret < 0) {
    perror("listen");
    return;
  }
}
int Accept::accpet() {
  int ret = ::accept(_socket.getfd(), nullptr, nullptr);
  if (ret < 0) {
    perror("accpet");
    return -1;
  }
  return ret;
}

int Accept::getfd() { return _socket.getfd(); }
void Accept::ready() {
  setReuseAddr();
  setReusePort();
  bind();
  listen();
}
