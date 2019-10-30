//
// Created by quiks on 23.10.2019.
//

#ifndef SELSQL_SERVER_H
#define SELSQL_SERVER_H

#ifdef __WIN32
#include "Win/WinServer.h"
#elif __linux
#include "Linux/LinuxServer.h"
#endif
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include "Exception.h"

#define MAX_CONN 1
#define DEBUG 1

void RunServer();
int ListenClient(int id, Server* server);
std::string ExecuteRequest(const std::string& request);

#endif  // SELSQL_SERVER_H
