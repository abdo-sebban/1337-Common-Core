#include "../../include/Bot.hpp"

Bot::Bot(const std::string &host, int port, const std::string &password,
         const std::string &nickname, const std::string &channel)
    : fd(-1), host(host), port(port), password(password),
      nickname(nickname), channel(channel) {}

Bot::~Bot() {
  if (fd != -1)
    close(fd);
}

bool Bot::connectToServer() {
  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    std::cerr << "bot: socket() failed" << std::endl;
    return false;
  }

  struct sockaddr_in addr;
  std::memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);

  addr.sin_addr.s_addr = inet_addr(host.c_str());
  if (addr.sin_addr.s_addr == INADDR_NONE) {
    std::cerr << "bot: invalid IP address " << host << std::endl;
    return false;
  }

  if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    std::cerr << "bot: connect() failed" << std::endl;
    return false;
  }
  return true;
}

void Bot::sendRaw(const std::string &msg) {
  std::string packet = msg + "\r\n";
  send(fd, packet.c_str(), packet.size(), 0);
}

void Bot::run() {
  if (!connectToServer())
    return;

  sendRaw("PASS " + password);
  sendRaw("NICK " + nickname);
  sendRaw("USER " + nickname + " 0 * :" + nickname);

  struct pollfd pfd;
  pfd.fd = fd;
  pfd.events = POLLIN;

  char chunk[1024];

  while (true) {
    pfd.revents = 0;
    if (poll(&pfd, 1, -1) <= 0 || !(pfd.revents & POLLIN))
      break;

    ssize_t bytes = recv(fd, chunk, sizeof(chunk) - 1, 0);
    if (bytes <= 0)
      break;
    chunk[bytes] = '\0';
    buffer += chunk;

    size_t pos;
    while ((pos = buffer.find("\r\n")) != std::string::npos) {
      std::string line = buffer.substr(0, pos);
      buffer.erase(0, pos + 2);

      if (line.find(" 001 ") != std::string::npos)
        sendRaw("JOIN " + channel);
      else if (line.find(" JOIN ") != std::string::npos)
        sendRaw("PRIVMSG " + channel + " :Hi!");
    }
  }
}