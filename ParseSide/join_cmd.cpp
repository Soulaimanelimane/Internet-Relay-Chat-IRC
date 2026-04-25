/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:22:03 by omaezzem          #+#    #+#             */
/*   Updated: 2026/04/25 11:29:38 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

int is_already_exist(std::string &name_channel , std::vector<Channel> &all_channels)
{
    for (size_t i = 0; i < all_channels.size(); i++)
    {
        if(name_channel == all_channels[i].get_name())
            return 1;
    }
    return 0;
}

void ParseSide::parse_Join(const std::string &cmdarg, std::vector<Channel> &all_channels, Client &cls)
{
    std::vector<std::string> line = ft_split(cmdarg, 0);
    if (line.empty() || line[0] != "JOIN")
    {
        ERR_CMDDISMATCH("JOIN\r\n", cls);
        return;
    }
    if (line.size() < 2)
    {
        ERR_NEEDMOREPARAMS("JOIN\r\n", cls);
        return;
    }
    if (line[1] == "0")
    {
        for (size_t i = 0; i < all_channels.size(); i++)
            all_channels[i].remove_itself(cls);
        long long k = 0;
        long long channel_size = all_channels.size();
        while (k < channel_size)
        {
            if (all_channels[k].size() == 0)
            {
                all_channels.erase(all_channels.begin() + k);
                k = -1;
            }
            channel_size = all_channels.size();
            k++;
        }
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
            ERR_BADCHANMASK(ch, cls);
            continue;
        }
        if (ch[0] != '#' && ch[0] != '&'){
            ERR_BADCHANMASK(ch, cls);
            continue;
        }
        if (ch.find(' ') != std::string::npos ||
            ch.find(',') != std::string::npos){
            ERR_BADCHANMASK(ch, cls);
            continue;
        }
        std::string key = "";
        if (i < keys.size())
            key = keys[i];
        if (is_already_exist(channels[i], all_channels) == 0)
        {
            Channel t =  Channel(cls, channels[i]);
            if (key != "")
                t.set_password(key);
            all_channels.push_back(t);
        }
        else
        {
            for (size_t j = 0; j < all_channels.size(); j++)
            {
                if (all_channels[j].get_name() == channels[i])
                {
                    if (all_channels[j].get_permession() == true)
                    {
                        if (all_channels[j].get_pass() == key)
                            all_channels[j].add_member(cls);
                        else
                            ft_send(cls, "Warning : go check the password bcs is incorrect\r\n");
                    }
                    else
                        all_channels[j].add_member(cls);
                }
                    
            }
        }
    }
}
