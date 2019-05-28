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

    static int create_epoll() {
        int epollfd = epoll_create(SOCKET_MAX_EVENTS);
        if (epollfd < 0) {
            printf("create epoll fail %d, error:%s\r\n", epollfd, strerror(epollfd));
            return -1;
        }
        return epollfd;
    }

    static void add_epoll_event(const int epollfd, const int eventfd, const uint32_t events) {
        struct epoll_event event;
        memset(&event, 0, sizeof(event));

        event.events = events;
        event.data.fd = eventfd;

        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, eventfd , &event) < 0) {
            printf("epoll event add fail\r\n");
            return;
        }
    }

    static void remove_epoll_event(const int epollfd, const int eventfd) {
        if (epoll_ctl(epollfd, EPOLL_CTL_DEL, eventfd, NULL) < 0) {
            printf("epoll event remove fail\r\n");
            return;
        }
    }

};


#endif //SOCKET_EPOLL_H
