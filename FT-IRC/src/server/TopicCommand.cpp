#include "../../include/Channel.hpp"
#include "../../include/Server.hpp"

void Server::HandleTopicCommand(Client &client, std::vector<std::string> args)
{
    if (!client.IsAuthenticated())
    {
        SendToClient(client.GetFd(),
                     ":server 451 " + client.GetNickname() + " :You have not registered\r\n");
        return;
    }

    if (args.empty())
    {
        SendToClient(client.GetFd(),
                     ":server 461 " + client.GetNickname() + " TOPIC :Not enough parameters\r\n");
        return;
    }

    std::string channelName = args[0];

    if (channelName.empty() || channelName[0] != '#')
    {
        SendToClient(client.GetFd(),
                     ":server 403 " + client.GetNickname() + " " + channelName + " :No such channel\r\n");
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

    if (args.size() == 1)
    {
        if (channel->GetTopic().empty())
        {
            SendToClient(client.GetFd(),
                         ":server 331 " + client.GetNickname() + " " + channelName +
                         " :No topic is set\r\n");
        }
        else
        {
            SendToClient(client.GetFd(),
                         ":server 332 " + client.GetNickname() + " " + channelName +
                         " :" + channel->GetTopic() + "\r\n");
        }
        return;
    }

    if (channel->IsTopicRestricted())
    {
        if (!channel->IsOperator(&client))
        {
            SendToClient(client.GetFd(),
                         ":server 482 " + client.GetNickname() + " " + channelName + " :You're not channel operator\r\n");
            return;
        }
    }

    std::string newTopic;

    for (size_t i = 1; i < args.size(); ++i)
    {
        if (i > 1)
            newTopic += " ";

        newTopic += args[i];
    }

    channel->SetTopic(newTopic);

    std::string topicMsg = ":" + client.GetNickname() + "!" +
                           client.GetUsername() +
                           "@localhost TOPIC " + channelName +
                           " :" + newTopic + "\r\n";

    channel->BroadcastMessage(topicMsg, NULL);
}
