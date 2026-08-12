#include "../../include/Client.hpp"

Client::Client() {}

int Client::GetFd() {
    return Fd;
}

std::string &Client::GetBuffer() {
    return buffer;
}

const std::string &Client::GetBuffer() const {
    return buffer;
}

bool Client::IsAuthenticated() {
    return authenticated;
}

bool Client::getuserAuthenticated() {
    return userAuthenticated;
}

std::string Client::GetNickname() {
    return nickname;
}

std::string Client::GetUsername() {
    return username;
}

void Client::SetBuffer(std::string buf) {
    buffer = buf;
}

void Client::SetNickname(std::string nick) {
    nickname = nick;
}

void Client::SetUsername(std::string user) {
    username = user;
}

void Client::SetAuthenticated(bool auth) {
    authenticated = auth;
}

void Client::SetuserAuthenticated(bool auth) {
    userAuthenticated = auth;
}

void Client::SetFd(int fd) {
    Fd = fd;
}

void Client::setIpAdd(std::string ipadd) {
    IPadd = ipadd;
}

bool Client::HasPassedAuth() {
    return passAuthenticated;
}

void Client::SetPassAuthenticated(bool pass) {
    passAuthenticated = pass;
}