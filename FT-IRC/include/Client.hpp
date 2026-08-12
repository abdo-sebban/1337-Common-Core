#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Server.hpp"
#include <iostream>

class Client {
    private:
        int Fd;
        std::string IPadd;
        std::string buffer;
        bool authenticated;
        std::string nickname;
        std::string username;
        bool passAuthenticated;
        bool userAuthenticated;

    public:
        Client();

        int GetFd();
        std::string &GetBuffer();
        const std::string &GetBuffer() const;
        bool IsAuthenticated();
        bool getuserAuthenticated();
        std::string GetNickname();
        std::string GetUsername();

        void SetBuffer(std::string buf);
        void SetNickname(std::string nick);
        void SetUsername(std::string user);
        void SetAuthenticated(bool auth);
        void SetuserAuthenticated(bool auth);
        void SetFd(int fd);
        void setIpAdd(std::string ipadd);

        bool HasPassedAuth();
        void SetPassAuthenticated(bool pass);
};

#endif