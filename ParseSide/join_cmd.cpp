#include "ParseSide.hpp"

void parse_Join(const std::string &cmdarg)
{
    std::vector<std::string> line = ft_split(cmdarg, ' ');
    if (line.empty() || line[0] != "JOIN")
    {
        ERR_CMDDISMATCH("JOIN");
        return;
    }
    if (line.size() < 2)
    {
        ERR_NEEDMOREPARAMS();
        return;
    }
    if (line[1] == "0")
    {
        //handleJoinZero() // slimane part;
        return ;
    }
    std::vector<std::string> channels = ft_split(line[1], ',');
    std::vector<std::string> keys;
    if (line.size() == 3)
        keys = ft_split(line[2], ',');
    for (size_t i = 0; i < channels.size(); i++)
    {
        const std::string &ch = channels[i];
        if (ch.empty()){
            ERR_BADCHANMASK(ch);
            continue;
        }
        if (ch[0] != '#' && ch[0] != '&'){
            ERR_BADCHANMASK(ch);
            continue;
        }
        if (ch.find(' ') != std::string::npos ||
            ch.find(',') != std::string::npos){
            ERR_BADCHANMASK(ch);
            continue;
        }
        std::string key = "";
        if (i < keys.size())
            key = keys[i];
       // handleJoinChannel(ch, key);// slimane kmel
    }
}
