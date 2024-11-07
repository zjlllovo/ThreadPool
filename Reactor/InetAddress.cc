#include "InetAddress.h"
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>

InetAddress::InetAddress(const string ip, unsigned short port) {
  memset(&_addr, 0, sizeof(_addr));
  _addr.sin_family = AF_INET;
  _addr.sin_port = htons(port);
  _addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

InetAddress::InetAddress(sockaddr_in addr) : _addr(addr) {}

InetAddress::~InetAddress() {}

sockaddr_in *InetAddress::getaddr() { return &_addr; }
