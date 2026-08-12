#include "../../include/Channel.hpp"
#include "../../include/Server.hpp"

void Server::HandlePrivmsgCommand(Client &client, std::vector<std::string> args) {

    if (!client.IsAuthenticated()) {
        SendToClient(client.GetFd(), ":server 451 " + client.GetNickname() + " :You have not registered\r\n");
        return ;
    }
    if (args.empty() || args[0].empty()) {
        SendToClient(client.GetFd(), ":server 411 " + client.GetNickname() + " :No recipient given (PRIVMSG)\r\n");
        return;
    }
    if (args.size() < 2 || args[1].empty()) {
        SendToClient(client.GetFd(), ":server 412 " + client.GetNickname() + " :No text to send\r\n");
        return;
    }
    std::string target = args[0];

    std::string msg = args[1];
    
    if (target[0] == '#') {
        Channel *channel = GetChannel(target);
        if (!channel) {
            SendToClient(client.GetFd(), ":server 401 " + client.GetNickname() + " " + target + " :No such nick/channel\r\n");
            return;
        }
        if (!channel->IsClientInChannel(&client)) {
            SendToClient(client.GetFd(), ":server 404 " + client.GetNickname() + " " + target + " :Cannot send to channel\r\n");
            return;
        }
        channel->BroadcastMessage(":" + client.GetNickname() + "!" + client.GetUsername() + "@localhost PRIVMSG " + target + " :" + msg + "\r\n", &client);
    }
    else {
        for (std::list<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
            if (it->GetNickname() == target) {
                SendToClient(it->GetFd(), ":" + client.GetNickname() + "!" + client.GetUsername() + "@localhost PRIVMSG " + target + " :" + msg + "\r\n");
                return;
            }
        }
        SendToClient(client.GetFd(),
                     ":server 401 " + client.GetNickname() + " " + target +
                     " :No such nick/channel\r\n");
    }
}