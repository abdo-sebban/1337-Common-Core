#ifndef CHANNEL_HPP

#define CHANNEL_HPP

#include "Client.hpp"
#include <cstddef>
#include <string>
#include <vector>

class Client;

class Channel {
private:
  std::string name;
  std::string topic;
  std::string password;
  std::vector<Client *> clients;
  std::vector<Client *> operators;
  bool inviteOnly;
  bool topicRestricted;
  std::vector<std::string> invited;
  int limit;

public:
  Channel(std::string name);
  Channel(std::string name, std::string password);
  ~Channel();

  std::string GetName() const;
  std::string GetTopic() const;
  std::string GetPassword() const;
  std::vector<Client *> getClients() const;

  void SetTopic(std::string topic);
  void SetPassword(std::string password);
  void SetInviteOnly(bool invite);

  bool IsInviteOnly() const;
  void AddInvite(const std::string &nick);
  bool IsInvited(const std::string &nick) const;
  void RemoveInvite(const std::string &nick);

  void AddClient(Client *client);
  void RemoveClient(Client *client);
  bool IsClientInChannel(Client *client);
  int countClients();

  void AddOperator(Client *client);
  bool IsOperator(Client *client);

  void SetTopicRestricted(bool restricted);
  bool IsTopicRestricted() const;

  void SetLimit(int limit);
  int GetLimit() const;
  bool HasLimit() const;

  void RemoveOperator(Client *client);
  void ClearPassword();

  void BroadcastMessage(std::string message, Client *exclude = NULL);
};

#endif
