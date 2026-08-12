#include "../../include/Channel.hpp"
#include "../../include/Server.hpp"

void Server::HandleJoinCommand(Client &client, std::vector<std::string> args) {
  if (!client.IsAuthenticated()) {
    SendToClient(client.GetFd(), ":server 451 " + client.GetNickname() +
                                     " :You have not registered\r\n");
    return;
  }

  if (args.empty()) {
    SendToClient(client.GetFd(), ":server 461 " + client.GetNickname() +
                                     " JOIN :Not enough parameters\r\n");
    return;
  }
  std::string channelsName = args[0];
  std::string keysStr = (args.size() > 1) ? args[1] : "";

  std::vector<std::string> channelNames;
  std::vector<std::string> keys;

  std::stringstream ssChannels(channelsName);
  std::string token;
  while (std::getline(ssChannels, token, ',')) {
    channelNames.push_back(token);
  }

  std::stringstream ssKeys(keysStr);
  while (std::getline(ssKeys, token, ',')) {
    keys.push_back(token);
  }

  for (size_t i = 0; i < channelNames.size(); ++i) {
    std::string channelName = channelNames[i];
    std::string key = (i < keys.size()) ? keys[i] : "";

    if (channelName.empty() || channelName[0] != '#') {
      SendToClient(client.GetFd(), ":server 476 " + client.GetNickname() + " " +
                                       channelName + " :Bad Channel Mask\r\n");
      continue;
    }
    Channel *channel = GetChannel(channelName);

    if (channel == NULL) {
      Channel newChannel(channelName, key);
      newChannel.AddClient(&client);
      newChannel.AddOperator(&client);
      channels.push_back(newChannel);
      channel = &channels.back();
      std::string joinMsg = ":" + client.GetNickname() + "!" +
                            client.GetUsername() +
                            "@localhost JOIN :" + channelName + "\r\n";
      channel->BroadcastMessage(joinMsg, NULL);
      std::string modeMsg = ":" + client.GetNickname() + "!" +
                            client.GetUsername() + "@localhost MODE " +
                            channelName + " +o " + client.GetNickname() +
                            "\r\n";
      channel->BroadcastMessage(modeMsg, NULL);
    } else {
      if (channel->IsInviteOnly() &&
          !channel->IsInvited(client.GetNickname()) &&
          !channel->IsOperator(&client)) {
        SendToClient(client.GetFd(), ":server 473 " + client.GetNickname() +
                                         " " + channelName +
                                         " :Cannot join channel (+i)\r\n");
        continue;
      }
      if (channel->GetPassword() != "" && channel->GetPassword() != key) {
        SendToClient(client.GetFd(), ":server 475 " + client.GetNickname() +
                                         " " + channelName +
                                         " :Cannot join channel (+k)\r\n");
        continue;
      }
      if (channel->HasLimit() &&
          channel->countClients() >= channel->GetLimit()) {
        SendToClient(client.GetFd(), ":server 471 " + client.GetNickname() +
                                         " " + channelName +
                                         " :Cannot join channel (+l)\r\n");
        continue;
      }
      channel->AddClient(&client);

      if (channel->IsInvited(client.GetNickname()))
        channel->RemoveInvite(client.GetNickname());
      std::string joinMsg = ":" + client.GetNickname() + "!" +
                            client.GetUsername() +
                            "@localhost JOIN :" + channelName + "\r\n";
      channel->BroadcastMessage(joinMsg, NULL);
      std::string names;

      const std::vector<Client *> &members = channel->getClients();

      for (size_t j = 0; j < members.size(); ++j) {
        if (channel->IsOperator(members[j]))
          names += "@";

        names += members[j]->GetNickname();

        if (j + 1 < members.size())
          names += " ";
      }

      SendToClient(client.GetFd(), ":server 353 " + client.GetNickname() +
                                       " = " + channelName + " :" + names +
                                       "\r\n");

      SendToClient(client.GetFd(), ":server 366 " + client.GetNickname() + " " +
                                       channelName +
                                       " :End of /NAMES list.\r\n");
    }

    if (channel->GetTopic().empty()) {
      SendToClient(client.GetFd(), ":server 331 " + client.GetNickname() + " " +
                                       channelName + " :No topic is set\r\n");
    } else {
      SendToClient(client.GetFd(), ":server 332 " + client.GetNickname() + " " +
                                       channelName + " :" +
                                       channel->GetTopic() + "\r\n");
    }
  }
}

Channel *Server::GetChannel(std::string name) {
  for (size_t i = 0; i < channels.size(); i++) {
    if (channels[i].GetName() == name)
      return &channels[i];
  }
  return NULL;
}

int Channel::countClients() { return (clients.size()); }
