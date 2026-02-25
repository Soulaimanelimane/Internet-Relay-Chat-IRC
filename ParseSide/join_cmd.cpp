#include "ParseSide.hpp"

int is_already_exist(std::string name_channel , std::vector<Channel *> &all_channels)
{
    for (size_t i = 0; i < all_channels.size(); i++)
    {
        if(name_channel == all_channels[i]->get_name())
            return 1;
    }
    return 0;
}

void parse_Join(const std::string &cmdarg, std::vector<Channel *> &all_channels, Client &cls)
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
        for (size_t i = 0; i < all_channels.size(); i++)
            all_channels[i]->remove_itself(cls);
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
        Channel t =  Channel(cls, channels[i]);
        // handleJoinChannel(ch, key);// slimane kmel--------------------------------------
        if (is_already_exist(channels[i], all_channels) == 0)
            all_channels.push_back(&t);
        else
        {
            for (size_t i = 0; i < all_channels.size(); i++)
            {
                if (all_channels[i]->get_name() == channels[i])
                    all_channels[i]->add_member(cls);
            }
        }
    }
}
