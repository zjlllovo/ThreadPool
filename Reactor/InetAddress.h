#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>

using std::string;

class InetAddress {
public:
  InetAddress(const string ip, unsigned short port);
  InetAddress(sockaddr_in addr);
  ~InetAddress();
  sockaddr_in *getaddr();

private:
  sockaddr_in _addr;
};

#endif // __INETADDRESS_H__
