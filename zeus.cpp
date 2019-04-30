#include "zeus.hpp"
#include "zssocket.h"


zeus::zeus(std::string ip, int port) {

    //create socket for listen
    bool ret = zssocket::create_socket(ip, port, true, &(this->accept_info));
    if (!ret) {
        printf("listen the port fail\n");
        exit(-1);
    }


}

void zeus::on_receive_thread(int fd) {

}

void zeus::server_start() {
    //running flag
    this->running = true;

    //accept thread
    this->accept_thread = std::thread(&zeus::accept_socket_thread, this);

    //create the wait event thread
    for (int thread_id = 0; thread_id < 16; thread_id++) {
        event_thread_list[thread_id].id = thread_id;
        event_thread_list[thread_id].event_epoll_fd = zsepoll::create_epoll();
        event_thread_list[thread_id].thread = std::thread(&zeus::event_wait_thread, this, thread_id);
    }
}

//accept the socket
void zeus::accept_socket_thread() {
    while (this->running) {
        //accept
        int connfd = zssocket::accept_conn(this->accept_info.listenfd_int, &(this->accept_info.sockeaddr_st));
        if (connfd > 0) {

            int thread_id = connfd % 16;

            //add request event monitor with epoll
            zsepoll::add_epoll_event(this->event_thread_list[thread_id].event_epoll_fd
                    , connfd, EPOLLIN);
        }
    }

}

//wait event
void zeus::event_wait_thread(int thread_id) {
    struct epoll_event eventlist_st[SOCKET_MAX_EVENTS];

    while (this->running) {

        int ret = epoll_wait(this->event_thread_list[thread_id].event_epoll_fd
                , eventlist_st, SOCKET_MAX_EVENTS, 3000);
        if (ret < 0) {
            printf("epoll error %d,%s\n", errno, strerror(errno));
            break;
        } else if (ret == 0) {
            //printf("timeout\n");
            continue;
        }

        for (int i = 0; i < ret; i++) {
            if (eventlist_st[i].events & EPOLLERR ||
                eventlist_st[i].events & EPOLLHUP ||
                !(eventlist_st[i].events & EPOLLIN)) {
                printf("epoll event error event:%d fd:%d\n", eventlist_st[i].events, eventlist_st[i].data.fd);
                close(eventlist_st[i].data.fd);
                continue;
            }

            //http process

        }
    }
}

zeus::~zeus() {
    this->running = false;
    this->accept_thread.join();
}

int main() {

    //create new socket server
    zeus *zeus_server = new zeus("127.0.0.1", 10086);

    //start server
    zeus_server->server_start();

    //main wait
    //todo wait fork worker process
    while (zeus_server->running) {
        sleep(1);
    }
    //release the server
    delete (zeus_server);

}