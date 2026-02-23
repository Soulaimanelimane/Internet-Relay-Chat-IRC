#include "ParseSide.hpp"

void ERR_NEEDMOREPARAMS_PASS() {
    std::cout << "461 PASS :Not enough parameters" << std::endl;
}

void ERR_ALREADYREGISTRED_PASS() {
    std::cout << "462 PASS :You may not reregister" << std::endl;
}

void ERR_PASSWDMISMATCH() {
    std::cout << "464 :Password incorrect" << std::endl;
}

void ERR_EXCEEDLIMIT() {
    std::cout << "exceed limit" << std::endl;
}

void ERR_CMDDISMATCH(std::string &cmd) {
    std::cout << "cmd must be "<< cmd << std::endl;
}

void ERR_NONICKNAMEGIVEN() {
    std::cout << "431 :No nickname given" << std::endl;
}

void ERR_ERRONEUSNICKNAME(const std::string& nick) {
    std::cout << "432 " << nick << " :Erroneous nickname" << std::endl;
}

void ERR_NICKNAMEINUSE(const std::string& nick) {
    std::cout << "433 " << nick << " :Nickname is already in use" << std::endl;
}


void ERR_NICKCOLLISION(const std::string& nick) {
    std::cout << "436 " << nick << " :Nickname collision" << std::endl;
}

void ERR_NEEDMOREPARAMS_USER() {
    std::cout << "461 USER :Not enough parameters" << std::endl;
}

void ERR_CONTAINSPACE() {
    std::cout << "must be without white spaces" << std::endl;
}


void ERR_INVALIDUSERNAME(const std::string& username) {
    std::cout << "464 " << username << " :Invalid username" << std::endl;
}

void ERR_CMDMISMATCH(const std::string &expected)
{
    std::cout << "Error: Expected command " << expected << std::endl;
}

void ERR_NEEDMOREPARAMS()
{
    std::cout << "Error: Not enough parameters for " << std::endl;
}

void ERR_BADCHANMASK(const std::string &channel)
{
    std::cout << "Error: Invalid channel name: " << channel << std::endl;
}
void ERR_TOOMANYPARAMS()
{
    std::cout << "Error: too many parameteres : " << std::endl;
}
void ERR_USERNOTFOUND(std::string &var)
{
    std::cout << "Error: " << var << " is not a valid user.\n";
}