#include "../../include/Server.hpp"

bool isNickFirstChar(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '[' ||
         c == ']' || c == '\\' || c == '`' || c == '_' || c == '^' ||
         c == '{' || c == '}';
}
bool isNickChar(char c) {
  return isNickFirstChar(c) || (c >= '0' && c <= '9') || c == '-';
}
std::string replyNick(Client &client) {
  std::string n = client.GetNickname();
  return n.empty() ? std::string("*") : n;
}

static void sendWelcome(Server &s, Client &client) {
  if (client.IsAuthenticated())
    return;
  if (!client.HasPassedAuth() || client.GetNickname().empty() ||
      client.GetUsername().empty())
    return;
  client.SetAuthenticated(true);
  std::string n = client.GetNickname();
  std::string u = client.GetUsername();
  s.SendToClient(client.GetFd(),
                 ":server 001 " + n + " :Welcome to the Internet Relay Network " +
                     n + "!" + u + "@localhost\r\n");
  s.SendToClient(client.GetFd(),
                 ":server 002 " + n +
                     " :Your host is server, running version 1.0\r\n");
  s.SendToClient(client.GetFd(),
                 ":server 003 " + n + " :This server was created just now\r\n");
  s.SendToClient(client.GetFd(),
                 ":server 004 " + n + " server 1.0 o oitklb\r\n");
}

Client &Server::GetClient(int fd)
{
  for (std::list<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
    if (it->GetFd() == fd)
      return *it;
  }
  throw std::runtime_error("Client not found");
}

void Server::SendToClient(int fd, std::string message)
{
  send(fd, message.c_str(), message.length(), 0);
}

void Server::HandleMessage(int fd, std::string message)
{
  std::istringstream iss(message);
  std::string cmd;
  std::vector<std::string> args;

  iss >> cmd;
  std::string arg;
  while (iss >> arg) {
    if (!arg.empty() && arg[0] == ':') {
      std::string trailing = arg.substr(1);
      std::string rest;
      std::getline(iss, rest);
      if (!rest.empty() && rest[0] == ' ')
        rest.erase(0, 1);
      if (!rest.empty())
        trailing += " " + rest;
      args.push_back(trailing);
      break;
    }
    args.push_back(arg);
  }

  Client &client = GetClient(fd);

  if (cmd == "PASS")
    HandlePassCommand(client, args);
  else if (cmd == "NICK")
    HandleNickCommand(client, args);
  else if (cmd == "USER")
    HandleUserCommand(client, args);
  else if (cmd == "JOIN")
    HandleJoinCommand(client, args);
  else if (cmd == "TOPIC")
    HandleTopicCommand(client, args);
  else if (cmd == "KICK")
    HandleKickCommand(client, args);
  else if (cmd == "INVITE")
    HandleInviteCommand(client, args);
  else if (cmd == "PRIVMSG")
    HandlePrivmsgCommand(client, args);
  else if (cmd == "NOTICE")
    HandleNoticeCommand(client, args);
  else if (cmd == "MODE")
    HandleModeCommand(client, args);
  else {
    if (client.IsAuthenticated()) {
      SendToClient(client.GetFd(), ":server 421 " + client.GetNickname() + " " + cmd + " :Unknown command\r\n");
    }
  }
}

void Server::HandlePassCommand(Client &client, std::vector<std::string> args) {
  if (client.HasPassedAuth()){
    SendToClient(client.GetFd(),
                 ":server 462 " + replyNick(client) +
                 " :Unauthorized command (already registered)\r\n");
    return;
  }
  if (args.size() < 1) {
    SendToClient(client.GetFd(),
                 ":server 461 " + replyNick(client) +
                 " PASS :Not enough parameters\r\n");
    return;
  }
  if (args[0] == Password) {
    client.SetPassAuthenticated(true);
    sendWelcome(*this, client);
  } else {
    SendToClient(client.GetFd(),
                 ":server 464 " + replyNick(client) +
                 " :Password incorrect\r\n");
  }
}

void Server::HandleNickCommand(Client &client, std::vector<std::string> args) {
  if (args.size() < 1 || args[0].empty()) {
    SendToClient(client.GetFd(),
                 ":server 431 " + replyNick(client) + " :No nickname given\r\n");
    return;
  }

  std::string newNick = args[0];
  if (newNick.size() > 9 || !isNickFirstChar(newNick[0])) {
    SendToClient(client.GetFd(),
                 ":server 432 " + replyNick(client) + " " + newNick +
                 " :Erroneus nickname\r\n");
    return;
  }
  for (size_t i = 1; i < newNick.size(); ++i) {
    if (!isNickChar(newNick[i])) {
      SendToClient(client.GetFd(),
                   ":server 432 " + replyNick(client) + " " + newNick +
                   " :Erroneus nickname\r\n");
      return;
    }
  }

  for (std::list<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
      if (it->GetNickname() == newNick && it->GetFd() != client.GetFd()) {
        SendToClient(client.GetFd(),
                     ":server 433 " + replyNick(client) + " " + newNick +
                     " :Nickname is already in use\r\n");
        return ;
      }
  }

  client.SetNickname(newNick);

  sendWelcome(*this, client);
}

void Server::HandleUserCommand(Client &client, std::vector<std::string> args) {
  if(client.getuserAuthenticated()){
    SendToClient(client.GetFd(),
                 ":server 462 " + replyNick(client) +
                 " :Unauthorized command (already registered)\r\n");
    return;
  }
  if (args.size() < 4) {
    SendToClient(client.GetFd(),
                 ":server 461 " + replyNick(client) +
                 " USER :Not enough parameters\r\n");
    return;
  }
  client.SetUsername(args[0]);
  client.SetuserAuthenticated(true);

  sendWelcome(*this, client);
}
