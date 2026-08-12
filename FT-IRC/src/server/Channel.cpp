#include "../../include/Channel.hpp"

Channel::Channel(std::string name)
    : name(name), topic(""), password(""), inviteOnly(false),
      topicRestricted(false), limit(0) {}

Channel::Channel(std::string name, std::string password)
    : name(name), topic(""), password(password), inviteOnly(false),
      topicRestricted(false), limit(0) {}

Channel::~Channel() {}

std::string Channel::GetName() const { return name; }
std::string Channel::GetTopic() const { return topic; }
std::string Channel::GetPassword() const { return password; }
std::vector<Client *> Channel::getClients() const { return clients; }

void Channel::SetTopicRestricted(bool restricted) {
  topicRestricted = restricted;
}

void Channel::SetTopic(std::string topic) { this->topic = topic; }
void Channel::SetPassword(std::string password) { this->password = password; }

void Channel::AddClient(Client *client) {
  if (!IsClientInChannel(client))
    clients.push_back(client);
}
bool Channel::IsTopicRestricted() const { return topicRestricted; }

void Channel::RemoveClient(Client *client) {
  for (std::vector<Client *>::iterator it = clients.begin();
       it != clients.end(); ++it) {
    if (*it == client) {
      clients.erase(it);
      break;
    }
  }
}

bool Channel::IsClientInChannel(Client *client) {
  for (std::vector<Client *>::iterator it = clients.begin();
       it != clients.end(); ++it) {
    if (*it == client)
      return true;
  }
  return false;
}

void Channel::AddOperator(Client *client) {
  if (!IsOperator(client))
    operators.push_back(client);
}

void Channel::SetInviteOnly(bool invite) { inviteOnly = invite; }

bool Channel::IsInviteOnly() const { return inviteOnly; }

void Channel::AddInvite(const std::string &nick) {
  for (size_t i = 0; i < invited.size(); ++i) {
    if (invited[i] == nick)
      return;
  }
  invited.push_back(nick);
}

bool Channel::IsInvited(const std::string &nick) const {
  for (size_t i = 0; i < invited.size(); ++i) {
    if (invited[i] == nick)
      return true;
  }
  return false;
}

void Channel::RemoveInvite(const std::string &nick) {
  for (size_t i = 0; i < invited.size(); ++i) {
    if (invited[i] == nick) {
      invited.erase(invited.begin() + i);
      break;
    }
  }
}

bool Channel::IsOperator(Client *client) {
  for (std::vector<Client *>::iterator it = operators.begin();
       it != operators.end(); ++it) {
    if (*it == client)
      return true;
  }
  return false;
}

void Channel::SetLimit(int l) { limit = l; }
int Channel::GetLimit() const { return (limit); }
bool Channel::HasLimit() const { return limit > 0; }

void Channel::ClearPassword() { password.clear(); }
void Channel::RemoveOperator(Client *client) {
  for (std::vector<Client *>::iterator it = operators.begin();
       it != operators.end(); ++it) {
    if (*it == client) {
      operators.erase(it);
      return;
    }
  }
}

void Channel::BroadcastMessage(std::string message, Client *exclude) {
  for (std::vector<Client *>::iterator it = clients.begin();
       it != clients.end(); ++it) {
    if (*it != exclude) {
      send((*it)->GetFd(), message.c_str(), message.length(), 0);
    }
  }
}
