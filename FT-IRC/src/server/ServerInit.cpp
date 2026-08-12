#include "../../include/Server.hpp"

void Server::SerSocket() {
    struct sockaddr_in add;
	struct pollfd NewPoll;
    add.sin_family = AF_INET;
    add.sin_port = htons(this->Port);
    add.sin_addr.s_addr = INADDR_ANY;

    SerSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (SerSocketFd == -1)
        throw(std::runtime_error("faild to create socket"));

    int en = 1;
    if(setsockopt(SerSocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throw(std::runtime_error("faild to set option (SO_REUSEADDR) on socket"));
    if (fcntl(SerSocketFd, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("faild to set option (O_NONBLOCK) on socket"));
    if (bind(SerSocketFd, (struct sockaddr *)&add, sizeof(add)) == -1)
		throw(std::runtime_error("faild to bind socket"));
    if (listen(SerSocketFd, SOMAXCONN) == -1)
            throw(std::runtime_error("listen() faild"));

    NewPoll.fd = SerSocketFd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	fds.push_back(NewPoll);
}

void Server::ServerInit()
{
    SerSocket();

    std::cout << "Server <" << SerSocketFd << "> Connected" << std::endl;
	std::cout << "Waiting to accept a connection...\n";

    while (Server::Signal == false)
    {
        if ((poll(fds.data(), fds.size(), -1) == -1) && Server::Signal == false)
            throw(std::runtime_error("poll() faild"));
        for (size_t i = 0;i < fds.size(); i++)
        {
            if (fds[i].revents & POLLIN)
            {
                if (fds[i].fd == SerSocketFd)
                    AcceptNewClient();
                else
                    ReceiveNewData(fds[i].fd);
            }
        }
    }
    CloseFds();
}