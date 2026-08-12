#ifndef BOT_HPP
#define BOT_HPP

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <poll.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

class Bot {
  private:
    int fd;
    std::string host;
    int port;
    std::string password;
    std::string nickname;
    std::string channel;
    std::string buffer;

    bool connectToServer();
    void sendRaw(const std::string &msg);

  public:
    Bot(const std::string &host, int port, const std::string &password,
        const std::string &nickname, const std::string &channel);
    ~Bot();

    void run();
};

#endif