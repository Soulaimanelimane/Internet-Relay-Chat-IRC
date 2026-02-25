#include "ParseSide.hpp"

void    ParseSide::parse_USER(Client &client, std::string &cmdarg)
{
    std::vector<std::string> line = ft_split(cmdarg, ' ');
    if (line.size() < 5){
        ERR_NEEDMOREPARAMS_USER();
        return;
    }
    std::string cmd = line[0];
    if (cmd != "USER") {
        ERR_CMDDISMATCH(cmd);
        return;
    }
    std::string username = line[1];
    std::string placeholder1 = line[2];
    std::string placeholder2 = line[3];
    std::string realname;
    if (line.size() > 4)
    {
        realname = line[4].substr(1);
        for (size_t i = 5; i < line.size(); i++){
            realname += " ";
            realname += line[i];
        }
    }
    if (!check_is_contain_space(username)){
        ERR_CONTAINSPACE();
        return;
    }
    if (placeholder1 != "0" || placeholder2 != "*"){
        ERR_NEEDMOREPARAMS_USER();
        return;
    }
    user.push_back(username);
    rname.push_back(realname);
    client.set_user() = true;
}

bool    check_is_contain_space(std::string var)
{
    for (int i = 0; var[i]; i++)
    {
        if (var[i] == ' ')
            return false;
    }
    return true;
}