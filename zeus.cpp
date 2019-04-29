#include "zeus.hpp"
#include "zssocket.h"


zeus::zeus(std::string ip, int port) {

    bool ret = zssocket::create_socket(ip, port, true, &(this->accept_info));
    if (!ret) {
        printf("listen the port fail\n");
        exit(-1);
    }

}

zeus::~zeus() {
    this->running = false;
    this->accept_pthread.join();
}

void zeus::server_start() {
    this->running = true;
    this->accept_pthread = std::thread(&zeus::accept_socket,this);
}

//accept the socket
void zeus::accept_socket() {
    while (this->running) {
        zssocket::accept_conn(this->accept_info.listenfd_int,&(this->accept_info.sockeaddr_st));
    }
}

int main() {

    //create new socket server
    zeus *zeus_server = new zeus("127.0.0.1", 10086);

    //start server
    zeus_server->server_start();

    while (zeus_server->running){
        sleep(1);
    }
    //release the server
    delete (zeus_server);

}