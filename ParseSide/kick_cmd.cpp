#include "ParseSide.hpp"

void    ParseSide::parse_KICK(std::string &cmdarg, std::vector<Channel *>channels)
{
    std::vector<std::string> line = ft_split(cmdarg, ' ');
    if (line.size() < 3){
        ERR_NEEDMOREPARAMS();
        return;
    }
    if (line[0] != "KICK"){
        ERR_CMDDISMATCH("KICK");
        return;
    }
    std::vector<std::string> users = ft_split(line[2], ',');

    std::string channel = line[1];
    if (channel[0] != '#' && channel[0] != '&'){
        ERR_BADCHANMASK(channel);
        return;
    }
    bool found = false;
    for (size_t i = 0; i < channels.size(); i++){
        if (channel == channels[i]->getname()){
            found = true;
            break;
        }
    }
    if (!found){
        ERR_NOSUCHCHANNEL(channel);
        return;
    }
    std::string reason;
    if (line.size() > 3)
    {
        reason = line[3].substr(1);
        for (size_t i = 4; i < line.size(); i++){
            reason += " ";
            reason += line[i];
        }
    }
    if (!found){
        ERR_USERNOTFOUND(line[1]);
    }
}
