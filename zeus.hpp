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

struct event_info {
    //io fd
    int fd;

    //event type 0 read 1 write
    int event_type;
};

struct event_thread_epoll {

    int id;

    //epoll fd
    int event_epoll_fd;

    //wait event
    std::unordered_map<int, event_info> event_queue;

    //thread for process
    std::thread thread;

};

class zeus {

private:

    //accept port info
    struct socket_info accept_info;

    //accept thread id
    std::thread accept_thread;

    //event thread
    std::unordered_map<int,event_thread_epoll> event_thread_list;


public:
    bool running = true;

    zeus(const std::string ip, const int port);

    ~zeus();

    void server_start();

    void accept_socket_thread();

    void event_wait_thread(const int thread_id);

    void on_receive_thread(const int fd);

    void shutdown() {
        this->running = false;
    }

};


#endif //SOCKET_ZEUS_H