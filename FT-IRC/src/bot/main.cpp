#include "../../include/Bot.hpp"

static bool parseInt(const std::string &s, long &out) {
  if (s.empty())
    return false;
  out = 0;
  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] < '0' || s[i] > '9')
      return false;
    out = out * 10 + (s[i] - '0');
  }
  return true;
}

int main(int ac, char **av) {
  if (ac < 5) {
    std::cerr << "Usage: ./ircbot <host> <port> <password> <nickname> <#channel>"
              << std::endl;
    return 1;
  }

  long portLong;
  if (!parseInt(av[2], portLong) || portLong <= 0 || portLong > 65535) {
    std::cerr << "Invalid port number" << std::endl;
    return 1;
  }

  std::string host = av[1];
  std::string password = av[3];
  std::string nickname = av[4];
  std::string channel = av[5];

  if (channel.empty() || channel[0] != '#') {
    std::cerr << "Channel name must start with '#'" << std::endl;
    return 1;
  }

  Bot bot(host, (int)portLong, password, nickname, channel);
  bot.run();
  return 0;
}