/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 22:18:59 by omaezzem          #+#    #+#             */
/*   Updated: 2026/04/17 17:11:11 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

void ParseSide::parse_KICK(std::string &cmdarg, std::vector<Channel> &channels, std::vector<Client *> &Clients, Client &cls)
{
    std::vector<std::string> line = ft_split(cmdarg, 0);
    if (line.size() < 3){
        ERR_NEEDMOREPARAMS("KICK", cls);
        return;
    }
    if (line[0] != "KICK"){
        ERR_CMDDISMATCH("KICK", cls);
        return;
    }
    std::vector<std::string> channelList = ft_split(line[1], ',');
    std::vector<std::string> userList = ft_split(line[2], ',');
    std::string reason;
    if (line.size() > 3 && line[3][0] == ':'){
        reason = line[3].substr(1);
        for (size_t i = 4; i < line.size(); i++)
            reason += " " + line[i];
    }
    for (size_t i = 0; i < userList.size(); i++){
        if (userList[i].empty())
            continue;
        std::string channelName;
        if (channelList.size() == 1)
            channelName = channelList[0];
        else if (i < channelList.size())
            channelName = channelList[i];
        else
            continue;
        
        if (channelName[0] != '#' && channelName[0] != '&')
        {
            ERR_BADCHANMASK(channelName, cls);
            continue;
        }
        Channel targetChannel;
        bool is_in = false;
        for (size_t j = 0; j < channels.size(); j++){
            if (channels[j].getname() == channelName){
                targetChannel = channels[j];
                is_in = true;
                break;
            }
        }
        if (!is_in){
            ERR_NOSUCHCHANNEL(channelName, cls);
            continue;
        }
        if (!targetChannel.isUserInChannel(userList[i])){
            ERR_USERNOTINCHANNEL(userList[i], targetChannel.getname(), cls);
            continue;
        }
        RPL_KICK(userList[i], targetChannel.getname(), reason);
    }
    std::map<std::string, std::vector<std::string> > kicks;
    for (size_t i = 0; i < channelList.size(); i++) {
        std::string channelName = channelList[i];
            kicks[channelName] = userList;
    }
    std::map<std::string, std::vector<std::string> >::iterator it = kicks.begin();
    for (size_t i = 0; i < kicks.size(); i++)
    {
        for (size_t j = 0; j < channels.size(); j++)
        {
            if (it->first == channels[j].get_name())
            {
                for (size_t k = 0; k < it->second.size(); k++)
                    channels[j].remove_member(get_client(Clients, it->second[k]) , cls);
            }
            if (channels[j].size() == 0)
                channels.erase(channels.begin() + j);
        }
        it++; 
    }
}