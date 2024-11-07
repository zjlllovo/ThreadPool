#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <cstring>
class Socket {
public:
  Socket();
  explicit Socket(int fd);
  ~Socket();

  int getfd();

private:
  int _fd;
};
#endif // __SOCKET_H__
