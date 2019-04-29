#ifndef SOCKET_EPOLL_H
#define SOCKET_EPOLL_H

#include "sys/epoll.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SOCKET_MAX_EVENTS 4096

class zsepoll {
private:

public:

    int static create_epoll() {
        int epollfd = epoll_create(SOCKET_MAX_EVENTS);
        if (epollfd < 0) {
            printf("create epoll fail %d, error:%s", epollfd, strerror(epollfd));
            return -1;
        }
        return epollfd;
    }

    void static add_epoll_event(int epollfd, int eventfd, uint32_t events) {
        struct epoll_event event;
        memset(&event, 0, sizeof(event));

        event.events = events;
        event.data.fd = eventfd;

        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, eventfd, &event) < 0) {
            printf("epoll event add fail");
            return;
        }
    }

};


#endif //SOCKET_EPOLL_H
