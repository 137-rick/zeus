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

    //accept fd
    int accept_fd;

    //accept info
    struct socket_info accept_info;

    //accept thread id
    std::thread accept_pthread;

    //------------------------------
    //function ---------------------
    //------------------------------


public:
    zeus(char* ip, int port);

    ~zeus();

    void server_start();
    void accept_socket();

};


#endif //SOCKET_ZEUS_H