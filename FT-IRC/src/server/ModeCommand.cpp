#include "../../include/Channel.hpp"
#include "../../include/Server.hpp"
#include <cerrno>

void Server::HandleModeCommand(Client &client, std::vector<std::string> args) {
  if (!client.IsAuthenticated()) {
    SendToClient(client.GetFd(), ":server 451 " + client.GetNickname() +
                                     " :You have not registered\r\n");
    return;
  }
  if (args.empty()) {
    SendToClient(client.GetFd(), ":server 461 " + client.GetNickname() +
                                     " MODE :Not enough parameters\r\n");
    return;
  }
  std::string ChannelName = args[0];
  if (ChannelName[0] != '#') {
    SendToClient(client.GetFd(), ":server 476 " + client.GetNickname() + " " +
                                     ChannelName + " :Bad Channel Mask\r\n");
    return;
  }
  Channel *channel = GetChannel(ChannelName);
  if (channel == NULL) {
    SendToClient(client.GetFd(), ":server 403 " + client.GetNickname() + " " +
                                     ChannelName + " :No such channel\r\n");
    return;
  }
  std::string mode = args[1];

  if (mode[0] != '+' && mode[0] != '-') {
    SendToClient(client.GetFd(), ":server 461 " + client.GetNickname() +
                                     " MODE :Not enough parameters\r\n");
    return;
  }
  if (!channel->IsOperator(&client)) {
    SendToClient(client.GetFd(), ":server 482 " + client.GetNickname() + " " +
                                     ChannelName +
                                     " :You're not channel operator\r\n");
    return;
  }
  bool adding = mode[0] == '+';
  size_t paramIndex = 2;
  for (size_t i = 1; i < mode.length(); i++) {
    switch (mode[i]) {
    case 'i': {
      channel->SetInviteOnly(adding);

      std::string msg = ":" + client.GetNickname() + "!" +
                        client.GetUsername() + "@localhost MODE " +
                        ChannelName + " " + (adding ? "+i" : "-i") + "\r\n";
      channel->BroadcastMessage(msg, NULL);
      break;
    }

    case 't': {
      channel->SetTopicRestricted(adding);

      std::string msg = ":" + client.GetNickname() + "!" +
                        client.GetUsername() + "@localhost MODE " +
                        ChannelName + " " + (adding ? "+t" : "-t") + "\r\n";
      channel->BroadcastMessage(msg, NULL);
      break;
    }

    case 'k': {
      if (adding) {
        if (paramIndex >= args.size()) {
          SendToClient(client.GetFd(), ":server 461 " + client.GetNickname() +
                                           " MODE :Not enough parameters\r\n");
          return;
        }

        std::string key = args[paramIndex++];
        channel->SetPassword(key);

        std::string msg = ":" + client.GetNickname() + "!" +
                          client.GetUsername() + "@localhost MODE " +
                          ChannelName + " +k " + key + "\r\n";
        channel->BroadcastMessage(msg, NULL);
      } else {
        channel->ClearPassword();

        std::string msg = ":" + client.GetNickname() + "!" +
                          client.GetUsername() + "@localhost MODE " +
                          ChannelName + " -k\r\n";
        channel->BroadcastMessage(msg, NULL);
      }
      break;
    }

    case 'o': {
      if (paramIndex >= args.size()) {
        SendToClient(client.GetFd(), ":server 461 " + client.GetNickname() +
                                         " MODE :Not enough parameters\r\n");
        return;
      }

      Client *target = GetClientByNick(args[paramIndex++]);

      if (!target) {
        SendToClient(client.GetFd(), ":server 401 " + client.GetNickname() +
                                         " " + args[paramIndex - 1] +
                                         " :No such nick/channel\r\n");
        return;
      }

      if (adding)
        channel->AddOperator(target);
      else
        channel->RemoveOperator(target);

      std::string msg = ":" + client.GetNickname() + "!" +
                        client.GetUsername() + "@localhost MODE " +
                        ChannelName + " " + (adding ? "+o " : "-o ") +
                        target->GetNickname() + "\r\n";

      channel->BroadcastMessage(msg, NULL);
      break;
    }

    case 'l': {
      if (adding) {
        if (paramIndex >= args.size()) {
          SendToClient(client.GetFd(), ":server 461 " + client.GetNickname() +
                                           " MODE :Not enough parameters\r\n");
          return;
        }

        char *end;
        errno = 0;

        long limit = std::strtol(args[paramIndex++].c_str(), &end, 10);

        if (limit <= 0 || errno == ERANGE || *end != '\0') {
          SendToClient(client.GetFd(), ":server 461 " + client.GetNickname() +
                                           " MODE :Not enough parameters\r\n");
          return;
        }

        channel->SetLimit(limit);

        std::ostringstream ss;
        ss << ":" << client.GetNickname() << "!" << client.GetUsername()
           << "@localhost MODE " << ChannelName << " +l " << limit << "\r\n";

        channel->BroadcastMessage(ss.str(), NULL);
      } else {
        channel->SetLimit(-1);

        std::string msg = ":" + client.GetNickname() + "!" +
                          client.GetUsername() + "@localhost MODE " +
                          ChannelName + " -l\r\n";

        channel->BroadcastMessage(msg, NULL);
      }
      break;
    }

    default:
      SendToClient(client.GetFd(), ":server 472 " + client.GetNickname() + " " +
                                       std::string(1, mode[i]) +
                                       " :is unknown mode char to me for " +
                                       ChannelName + "\r\n");
      break;
    }
  }
}
