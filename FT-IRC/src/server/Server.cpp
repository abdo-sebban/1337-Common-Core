#include "../../include/Server.hpp"


Server::Server(int port, std::string password) : Port(port), Password(password) {}

Server::~Server()
{
}

void Server::ClearClients(int fd) {
  for (size_t i = 0; i < fds.size(); i++) {
    if (fds[i].fd == fd) {
      fds.erase(fds.begin() + i);
      break;
    }
  }
  for (std::list<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
    if (it->GetFd() == fd) {
      clients.erase(it);
      break;
    }
  }
}

void Server::CloseFds() {
  for (std::list<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
    std::cout << "Client <" << it->GetFd() << "> Disconnected"
              << std::endl;
    close(it->GetFd());
  }
  if (SerSocketFd != -1) {
    std::cout << "Server <" << SerSocketFd << "> Disconnected" << std::endl;
    close(SerSocketFd);
  }
}

void Server::AcceptNewClient() {
  Client cli;
  struct sockaddr_in cliadd;
  struct pollfd NewPoll;
  socklen_t len = sizeof(cliadd);

  int incofd = accept(SerSocketFd, (sockaddr *)&(cliadd), &len);
  if (incofd == -1) {
    std::cout << "accept() failed" << std::endl;
    return;
  }

  if (fcntl(incofd, F_SETFL, O_NONBLOCK) == -1) {
    std::cout << "fcntl() failed" << std::endl;
    return;
  }

  cli.SetPassAuthenticated(false);
  cli.SetAuthenticated(false);
  cli.SetuserAuthenticated(false);

  NewPoll.fd = incofd;   
  NewPoll.events = POLLIN;
  NewPoll.revents = 0;

  cli.SetFd(incofd);
  cli.setIpAdd(inet_ntoa((cliadd.sin_addr)));
  clients.push_back(cli);
  fds.push_back(NewPoll);

  std::cout << "Client <" << incofd << "> Connected" << std::endl;
}

void Server::ReceiveNewData(int fd) {
  char buff[1024];
  memset(buff, 0, sizeof(buff));

  ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);

  if (bytes <= 0) {
    std::cout << "Client <" << fd << "> Disconnected" << std::endl;
    ClearClients(fd);
    close(fd);
  }
  else
  {
    buff[bytes] = '\0';
    GetClient(fd).SetBuffer(GetClient(fd).GetBuffer() + std::string(buff));

    std::string &clientBuf = GetClient(fd).GetBuffer();
    size_t pos;
    while ((pos = clientBuf.find("\n")) != std::string::npos) {
      std::string message = clientBuf.substr(0, pos);
      clientBuf.erase(0, pos + 1);
      if (!message.empty() && message[message.size() - 1] == '\r')
        message.erase(message.size() - 1);
      if (!message.empty())
        HandleMessage(fd, message);
    }
  }
}

Client *Server::GetClientByNick(const std::string &nick) {
  for (std::list<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
    if (it->GetNickname() == nick)
      return &(*it);
  }

  return NULL;
}
