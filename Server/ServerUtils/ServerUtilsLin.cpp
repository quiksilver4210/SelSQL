//
// Created by User on 10.11.2019.
//

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "ServerUtils.h"

void ServerUtils::startServer() {}

void ServerUtils::closeServer(int server_socket) { shutdown(server_socket, SHUT_RDWR); }

void ServerUtils::setSockOpt(int server_socket) {
    int enable = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0;
}