#ifndef __TCPIO_H__
#define __TCPIO_H__

#include "Socket.h"

class TcpIO {
public:
  TcpIO(int fd);

  ~TcpIO();

  int sendn(const char *buf, int len);
  int readn(char *buf, int len);
  int readLine(char *buf, int len);
  int getfd();

private:
  int _fd;
};
#endif // __TCPIO_H__
