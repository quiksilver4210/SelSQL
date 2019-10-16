//
// Created by quiks on 13.10.2019.
//

#ifndef SERVER_WINSERVER_H
#define SERVER_WINSERVER_H

#include <winsock2.h>
#include <string>
#include <vector>
#include "../Exception.h"

static const int MESSAGE_SIZE = 1024;

class Server {
    int server_socket;
    std::vector<int> communication_socket;
    sockaddr_in addr;

   public:
    char recieved_message[MESSAGE_SIZE];
    explicit Server(int max_connection);
    int ListenSocket(int id);
    int SendMessage(std::string response, int id);
    int AcceptSocket(int id);
    ~Server();
};

#endif  // SERVER_WINSERVER_H