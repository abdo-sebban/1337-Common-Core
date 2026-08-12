#include "../include/Server.hpp"
#include "../include/Client.hpp"

bool Server::Signal = false;

void Server::SignalHandler (int signum)
{
    (void)signum;
    std::cout << std::endl << "Signal Received" << std::endl;
    Server::Signal = true;
}

bool parseInt(const std::string &s, long &out)
{
  if (s.empty()) 
    return false;
  out = 0;
  for (size_t i = 0; i < s.size(); ++i)
  {
    if (s[i] < '0' || s[i] > '9')
        return false;
    long n = out * 10 + (s[i] - '0');
    if (n < out)
        return false;
    out = n;
  }
  return true;
}

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
        return (1);
    }

    long portLong;
    portLong = 0;
    if (!parseInt(av[1], portLong) || portLong <= 0 || portLong > 65535)
    {
        std::cerr << "Invalid port number" << std::endl;
        return 1;
    }

    int port = static_cast<int>(portLong);
    std::string password = av[2];

    Server ser(port, password);
    std::cout << "Server starting on port " << port << std::endl;
    try
    {
        signal(SIGINT, Server::SignalHandler); // signal (ctrl + c)
        signal(SIGQUIT, Server::SignalHandler); // signal (ctrl + \)
        ser.ServerInit();
    }
    catch (const std::exception &e)
    {
        ser.CloseFds();
        std::cerr << e.what() << std::endl;
    }
    std::cout << "Server Close" << std::endl;
}