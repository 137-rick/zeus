#ifndef SOCKET_EPOLL_H
#define SOCKET_EPOLL_H

#include "sys/epoll.h"

#define SOCKET_MAX_EVENTS 4096
int create_epoll();
void add_epoll_event(int epollfd, int eventfd, uint32_t events);


#endif //SOCKET_EPOLL_H
