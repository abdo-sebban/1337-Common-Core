#include "../../include/Channel.hpp"
#include "../../include/Server.hpp"

void Server::HandleKickCommand(Client &client, std::vector<std::string> args)
{
    if (!client.IsAuthenticated())
    {
        SendToClient(client.GetFd(), ":server 451 " + client.GetNickname() + " :You have not registered\r\n");
        return;
    }

    if (args.size() < 2)
    {
        SendToClient(client.GetFd(), ":server 461 " + client.GetNickname() + " KICK :Not enough parameters\r\n");
        return;
    }

    std::string channelName = args[0];
    std::string targetNickname = args[1];

    if (targetNickname.empty())
    {
        SendToClient(client.GetFd(), ":server 461 " + client.GetNickname() + " KICK :Not enough parameters\r\n");
        return;
    }

    if (channelName.empty() || channelName[0] != '#')
    {
        SendToClient(client.GetFd(), ":server 403 " + client.GetNickname() + " " + channelName + " :No such channel\r\n");
        return;
    }

    Channel *channel = GetChannel(channelName);
    if (!channel)
    {
        SendToClient(client.GetFd(),
                     ":server 403 " + client.GetNickname() + " " + channelName + " :No such channel\r\n");
        return;
    }

    if (!channel->IsClientInChannel(&client))
    {
        SendToClient(client.GetFd(),
                     ":server 442 " + client.GetNickname() + " " + channelName + " :You're not on that channel\r\n");
        return;
    }

    if (!channel->IsOperator(&client))
    {
        SendToClient(client.GetFd(),
                     ":server 482 " + client.GetNickname() + " " + channelName + " :You're not channel operator\r\n");
        return;
    }

    Client *targetClient = NULL;
    for (std::list<Client>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if (it->GetNickname() == targetNickname)
        {
            targetClient = &(*it);
            break;
        }
    }

    if (!targetClient)
    {
        SendToClient(client.GetFd(),
                     ":server 401 " + client.GetNickname() + " " + targetNickname + " :No such nick/channel\r\n");
        return;
    }

    if (!channel->IsClientInChannel(targetClient))
    {
        SendToClient(client.GetFd(),
                     ":server 441 " + client.GetNickname() + " " + targetNickname + " " + channelName + " :They aren't on that channel\r\n");
        return;
    }

    std::string reason = "kicked";
    if (args.size() > 2)
    {
        reason.clear();
        for (size_t i = 2; i < args.size(); ++i)
        {
            if (i > 2)
                reason += " ";
            reason += args[i];
        }
    }

    std::string kickMsg = ":" + client.GetNickname() + "!" + client.GetUsername() +
                          "@localhost KICK " + channelName + " " + targetNickname +
                          " :" + reason + "\r\n";

    channel->BroadcastMessage(kickMsg, NULL);
    channel->RemoveClient(targetClient);
}
