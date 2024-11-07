#include "Socket.h"
#include <stdio.h>
#include <sys/socket.h>

Socket::Socket() {
  _fd = socket(AF_INET, SOCK_STREAM, 0);
  if (_fd < 0) {
    perror("socket init");
    return;
  }
}

Socket::Socket(int fd) : _fd(fd) {}

Socket::~Socket() {}

int Socket::getfd() { return _fd; }
