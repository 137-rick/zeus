#ifndef ZEUS_ZSSOCKET_H
#define ZEUS_ZSSOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>


#define SOCKET_BUFFER_MAXSIZE 4096

#define SOCKET_BACKLOG 4096

struct socket_info {
    int listenfd_int;
    struct sockaddr_in sockeaddr_st;
    bool isblock;
};

class zssocket {
private:

public:
    bool static create_socket(std::string ip, int port, bool isblock, struct socket_info *socketInfo) {

        // addr
        memset(&socketInfo->sockeaddr_st, 0, sizeof(socketInfo->sockeaddr_st));

        //init  addr
        socketInfo->sockeaddr_st.sin_family = AF_INET;
        inet_pton(AF_INET, ip.data(), &(socketInfo->sockeaddr_st.sin_addr));

        //init port
        socketInfo->sockeaddr_st.sin_port = htons(port);

        // listenfd
        socketInfo->listenfd_int = socket(AF_INET, SOCK_STREAM, 0);

        // addr reuse
        int option = 1;
        if (setsockopt(socketInfo->listenfd_int, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int)) != 0) {
            printf("set reuse addr error\n");
            return false;
        }

        // port reuse
        if (setsockopt(socketInfo->listenfd_int, SOL_SOCKET, SO_REUSEPORT, &option, sizeof(int)) != 0) {
            printf("set reuse port error\n");
            return false;
        }

        //zeus send buffer
        uint32_t buffer_size = SOCKET_BUFFER_MAXSIZE;
        if (setsockopt(socketInfo->listenfd_int, SOL_SOCKET, SO_SNDBUF, &buffer_size, sizeof(buffer_size)) != 0) {
            printf("set send buff error\n");
            return false;
        }

        // receive buffer
        if (setsockopt(socketInfo->listenfd_int, SOL_SOCKET, SO_RCVBUF, &buffer_size, sizeof(buffer_size)) != 0) {
            printf("set recive buff error\n");
            return false;
        }

        //set is blocking io
        int flags = fcntl(socketInfo->listenfd_int, F_GETFL, 0);

        if (isblock) {
            if(fcntl(socketInfo->listenfd_int, F_SETFL, flags & ~O_NONBLOCK) < 0 ){
                printf("set blocking error\n");
                return false;
            }
            socketInfo->isblock = true;
        } else {
            if(fcntl(socketInfo->listenfd_int, F_SETFL, flags & O_NONBLOCK) < 0 ){
                printf("set non blocking  error\n");
                return false;
            }
            socketInfo->isblock = false;
        }

        //bind
        if (bind(socketInfo->listenfd_int, (struct sockaddr *) &socketInfo->sockeaddr_st,
                 sizeof(socketInfo->sockeaddr_st)) < 0) {
            printf("bind port error\n");
            return false;
        }

        //listen
        if (listen(socketInfo->listenfd_int, (int) SOCKET_BACKLOG) < 0) {
            printf(" listen port error\n");
            return false;
        }
        return true;
    }


    int static accept_conn(int listen_fd, struct sockaddr_in *sockaddr_st) {
        socklen_t len = sizeof(struct sockaddr_in);

        int confd = accept(listen_fd, (struct sockaddr *) &sockaddr_st, &len);

        if (confd < 0) {
            printf("accept fail\n");
            return -1;
        } else {
            printf("accept connection %d\n", confd);
        }

        return confd;
        //add_epoll_event(global_server.epollfd_int,confd,EPOLLIN );

    }

    int static recv_data(int fd) {
        char read_buff[SOCKET_BUFFER_MAXSIZE];
        int recive_length = recv(fd, read_buff, sizeof(read_buff), 0);
        if (recive_length <= 0) return 0;

        read_buff[recive_length] = '\0';
        //printf("recv msg from client %s\n", read_buff);
        return recive_length;
    }

    int static send_data(std::string data, int fd) {
        //send
        int ret = send(fd, data.data(), data.length(), 0);
        return ret;
    }

    void static close(int fd) {
        close(fd);
    }

};


#endif //ZEUS_ZSSOCKET_H
