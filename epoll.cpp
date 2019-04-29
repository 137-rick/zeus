#include "epoll.hpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int create_epoll() {
    //epoll event
    int epollfd = epoll_create(SOCKET_MAX_EVENTS);
    if (epollfd < 0) {
        printf("create epoll fail %d, error:%s", epollfd, strerror(epollfd));
        exit(-1);
    }
    return epollfd;
}

void add_epoll_event(int epollfd, int eventfd, uint32_t events) {
    struct epoll_event event;
    memset(&event, 0, sizeof(event));

    event.events = events;
    event.data.fd = eventfd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, eventfd, &event) < 0) {
        printf("epoll event add fail");
        exit(-1);
    }
}
