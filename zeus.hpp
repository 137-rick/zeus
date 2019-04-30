#ifndef SOCKET_ZEUS_H
#define SOCKET_ZEUS_H

#include <stdint.h>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include <list>

#include "zssocket.h"
#include "zsepoll.hpp"

class zeus {

private:

    //accept port info
    struct socket_info accept_info;

    //accept thread id
    std::thread accept_thread;

    //epoll fd
    int event_epoll_fd;

    //waite thread
    std::thread wait_event_thread;

public:
    bool running = true;

    zeus(std::string ip, int port);

    ~zeus();

    void server_start();
    void accept_socket_thread();
    void event_wait_thread();
    void on_receive_thread(int fd);

    void shutdown(){
        this->running = false;
    }

};


#endif //SOCKET_ZEUS_H