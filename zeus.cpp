#include "zeus.hpp"
#include "zssocket.h"


zeus::zeus(std::string ip, int port) {

    //create socket for listen
    bool ret = zssocket::create_socket(ip, port, true, &(this->accept_info));
    if (!ret) {
        printf("listen the port fail\n");
        exit(-1);
    }

    //create epoll for read write event
    this->event_epoll_fd = zsepoll::create_epoll();


}

void zeus::on_receive_thread(int fd) {

}

void zeus::server_start() {
    //running flag
    this->running = true;

    //accept thread
    this->accept_thread = std::thread(&zeus::accept_socket_thread,this);

    //event loop
    this->wait_event_thread = std::thread(&zeus::event_wait_thread,this);

}

//accept the socket
void zeus::accept_socket_thread() {
    while (this->running) {
        //accept
        int connfd = zssocket::accept_conn(this->accept_info.listenfd_int,&(this->accept_info.sockeaddr_st));
        if(connfd>0){
            //add request event monitor with epoll
            zsepoll::add_epoll_event(this->event_epoll_fd,connfd,EPOLLIN);
        }
    }

}

void zeus::event_wait_thread(){
    while (this->running) {
        /*
        nt ret = epoll_wait(global_server.epollfd_int, global_server.eventlist_st, SOCKET_MAX_EVENTS, timeout);
        if (ret < 0) {
            printf("1epoll error %d,%s\n", errno, strerror(errno));
            break;
        } else if (ret == 0) {
            //printf("timeout\n");
            continue;
        }*/
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
    while (zeus_server->running){
        sleep(1);
    }
    //release the server
    delete (zeus_server);

}