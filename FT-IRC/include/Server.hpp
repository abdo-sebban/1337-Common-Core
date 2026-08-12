#ifndef SERVER_HPP
#define SERVER_HPP

#include "Channel.hpp"
#include "Client.hpp"
#include <algorithm>
#include <arpa/inet.h>
#include <csignal>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <list>
#include <poll.h>
#include <sstream>
#include <vector>

class Channel;
class Client;

class Server 
{
  private:
    int                         Port;
    int                         SerSocketFd;
    static bool                 Signal;
    std::string                 Password;
    std::list<Client>           clients;
    std::vector<struct pollfd>  fds;
    std::vector<Channel>        channels;

  public:
    Server(int port, std::string password);
    ~Server();

    void ServerInit();
    void SerSocket();
    void AcceptNewClient();
    void ReceiveNewData(int fd);
    static void SignalHandler(int signum);

    Client &GetClient(int fd);
    void HandleMessage(int fd, std::string message);
    void HandlePassCommand(Client &client, std::vector<std::string> args);
    void HandleNickCommand(Client &client, std::vector<std::string> args);
    void HandleUserCommand(Client &client, std::vector<std::string> args);
    void HandleJoinCommand(Client &client, std::vector<std::string> args);
    void HandleModeCommand(Client &client, std::vector<std::string> args);
    void HandleTopicCommand(Client &client, std::vector<std::string> args);
    void HandleKickCommand(Client &client, std::vector<std::string> args);
    void HandleInviteCommand(Client &client, std::vector<std::string> args);
    void HandlePrivmsgCommand(Client &client, std::vector<std::string> args);
    void HandleNoticeCommand(Client &client, std::vector<std::string> args);

    void SendToClient(int fd, std::string message);

    Channel *GetChannel(std::string name);
    Client *GetClientByNick(const std::string &nick);

    void CloseFds();
    void ClearClients(int fd);
};

#endif
