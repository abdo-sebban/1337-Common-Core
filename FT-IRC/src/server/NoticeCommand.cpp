#include "../../include/Channel.hpp"
#include "../../include/Server.hpp"

void Server::HandleNoticeCommand(Client &client, std::vector<std::string> args) {

    if (!client.IsAuthenticated())
        return;
    if (args.empty() || args[0].empty())
        return;
    if (args.size() < 2 || args[1].empty())
        return;
    std::string target = args[0];
    std::string msg = args[1];

    if (target[0] == '#') {
        Channel *channel = GetChannel(target);
        if (!channel || !channel->IsClientInChannel(&client))
            return;
        channel->BroadcastMessage(":" + client.GetNickname() + "!" +
                                      client.GetUsername() +
                                      "@localhost NOTICE " + target + " :" +
                                      msg + "\r\n", &client);
    }
    else {
        for (std::list<Client>::iterator it = clients.begin();
             it != clients.end(); ++it) {
            if (it->GetNickname() == target) {
                SendToClient(it->GetFd(),
                             ":" + client.GetNickname() + "!" +
                                 client.GetUsername() +
                                 "@localhost NOTICE " + target + " :" + msg +
                                 "\r\n");
                return;
            }
        }
    }
}
