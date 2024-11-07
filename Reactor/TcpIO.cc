#include "TcpIO.h"
#include <cerrno>

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

TcpIO::TcpIO(int fd) : _fd(fd) {}

TcpIO::~TcpIO() {}

int TcpIO::sendn(const char *buf, int len) {
  const char *pstr = buf;
  int left = len;
  while (left > 0) {
    int ret = write(_fd, pstr, left);
    if (-1 == ret && ret & EINTR) {
      continue;
    } else if (-1 == ret) {
      perror("Tcpio write ret == -1");
      return -1;
    } else if (0 == ret) {
      break;
    } else {
      left -= ret;
      pstr += ret;
    }
  }
  return len - left;
}

int TcpIO::readn(char *buf, int len) {
  int left = len;
  char *pstr = buf;
  while (left > 0) {
    int ret = read(_fd, pstr, left);
    if (-1 == ret && ret & EINTR) {
      continue;
    } else if (-1 == ret) {
      perror("TcpIO read ret == -1");
      return -1;
    } else if (0 == ret) {
      break;
    } else {
      left -= ret;
      pstr += ret;
    }
  }
  return len - left;
}

int TcpIO::readLine(char *buf, int len) {
  char *pstr = buf;
  int left = len - 1;
  int total = 0;
  while (left > 0) {
    int ret = recv(_fd, pstr, left, MSG_PEEK);
    if (-1 == ret && ret & EINTR) {
      continue;
    } else if (-1 == ret) {
      perror("Tcpio write ret == -1");
      return -1;
    } else if (0 == ret) {
      break;
    } else {
      // ret
      for (int idx = 0; idx < ret; idx++) {
        if (pstr[idx] == '\n') {
          int sz = idx + 1;
          readn(pstr, sz);
          pstr += sz;
          *pstr = '\0';
          return total + sz;
        }
      }
      readn(pstr, ret);
      total += ret;
      pstr += ret;
      left -= ret;
    }
  }
  *pstr = '\0';
  return total - left;
}

int TcpIO::getfd() { return _fd; }
