#include "ParseSide.hpp"

void    ParseSide::parse_NICK(Client &client, std::string &cmdarg)
{
    std::vector<std::string> line = ft_split(cmdarg, ' ');
    std::string cmd = line[0];
    if (cmd != "NICK")
        ERR_CMDDISMATCH(cmd);
    if (line.size() < 2){
        ERR_NONICKNAMEGIVEN();
        return;
    }
    if (line.size() > 2){
        ERR_TOOMANYPARAMS();
        return ;
    }
    if (line.size() == 2){
        std::string nickname = line[1];
        if (nickname.length() > 9){
            ERR_ERRONEUSNICKNAME(nickname);
            return ;
        }
        if (nickname[0] == '-' ||  isdigit(nickname[0])){
            ERR_ERRONEUSNICKNAME(nickname);
            return;
        }
        for (size_t i = 0; i < nickname.length(); i++)
        {
            char c = nickname[i];
            if (!std::isalpha(c) && !std::isdigit(c)
                && c != '_' && c != '-'){
                ERR_ERRONEUSNICKNAME(nickname);
                return;
            }
        }
        for (size_t  i = 0; i < nick.size(); i++){
            if (nickname == nick[i]){
                ERR_NICKNAMEINUSE(nickname);
                return ;
            }
        }
        nick.push_back(nickname);
        client.set_nick() = true;
    }
    // check if is registred before pass
}

