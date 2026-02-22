#ifndef PARSESIDE_HPP
#define PARSESIDE_HPP

#include "../clients/client.hpp"
#include "../channels/channel.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

class ParseSide {
private:
    void parse_PASS(std::string &cmdarg);
    void parse_NICK(std::string &cmdarg);
    void parse_USER(std::string &cmdarg);
    void addusernicktoclient(std::vector<Client*> &clients);
    void parse_PRIVMSG(std::string &cmdarg);

public:
    std::vector<std::string> nick;
    std::vector<std::string> user;
    std::vector<std::string> rname;

    // void get_nickname();
};


std::vector<std::string> ft_split(const std::string& str, char delim);
bool    check_is_contain_space(std::string var);


void ERR_NEEDMOREPARAMS_PASS();
void ERR_ALREADYREGISTERED_PASS();
void ERR_PASSWDMISMATCH();
void ERR_EXCEEDLIMIT();
void ERR_NONICKNAMEGIVEN();
void ERR_ERRONEUSNICKNAME(const std::string &nick);
void ERR_NICKNAMEINUSE(const std::string &nick);
void ERR_NICKCOLLISION(const std::string &nick);
void ERR_NEEDMOREPARAMS_USER();
void ERR_INVALIDUSERNAME(const std::string &username);
void ERR_CMDDISMATCH(const std::string &cmd);
void ERR_CONTAINSPACE();
void ERR_BADCHANMASK(const std::string &channel);
void ERR_NEEDMOREPARAMS();
void ERR_TOOMANYPARAMS();
void ERR_USERNOTFOUND(std::string &var);

#endif 
// part quit no need 
