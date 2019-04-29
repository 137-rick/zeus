#ifndef SOCKET_ZEUS_H
#define SOCKET_ZEUS_H

#include <stdint.h>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include <list>

#include "zssocket.h"

class zeus {

private:

    //accept port info
    struct socket_info accept_info;

    //accept thread id
    std::thread accept_pthread;


public:
    bool running = true;

    zeus(std::string ip, int port);

    ~zeus();

    void server_start();
    void accept_socket();
    void shutdown(){
        this->running = false;
    }

};


#endif //SOCKET_ZEUS_H