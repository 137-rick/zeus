#include "zeus.hpp"
#include "zssocket.h"


zeus::zeus(char *ip, int port) {

    this->accept_fd = zssocket::create_socket(ip, port, &this.accept_info);
    if (this->accept_fd <= 0) {
        printf("listen the port fail");
        exit(-1);
    }
    //this->accept_pthread =  std::thread(&zeus::accept_socket,this);
}

zeus::~zeus() {

}

void zeus::server_start() {

}

//accept the socket
void zeus::accept_socket() {

    while (1) {

    }
}

int main() {

    zeus *zeus_server = new zeus("127.0.0.1", 10086);

    zeus_server->server_start();

}