/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg_cmd.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:21:32 by omaezzem          #+#    #+#             */
/*   Updated: 2026/02/27 00:10:31 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

void    ParseSide::parse_PRIVMSG(std::string &cmdarg, std::vector<Channel > &channels, Client &cls, std::vector<Client> &Clients)
{
    std::vector<std::string> line = ft_split(cmdarg, ' ');
    if (line.empty() || line[0] != "PRVIMSG")
    {
        ERR_CMDDISMATCH("PRVIMSG");
        return;
    }
    if (line.size() < 2){
        ERR_NEEDMOREPARAMS();
        return;
    }
    std::vector<std::string> receivers = ft_split(line[1], ',');
    std::vector<std::string>  chan;
    std::vector<std::string> usrs;
    for (size_t i = 0; i < receivers.size(); i++) {
        bool found = false;
        if (receivers[i][0] == '#' || '&')
        {
            for (size_t i = 0; i < channels.size(); i++)
            {
                if (channels[i].get_name() == receivers[i])
                {
                    found = true;
                    break;
                }
            }
            if (found == false)
                ERR_NOSUCHCHANNEL(receivers[i]);
            else
                chan.push_back(receivers[i]);
        }
        else
        {
            for (size_t j = 0; j < user.size(); j++) {
                if (user[j] == receivers[i])
                {
                    found = true;
                    break;
                }
                    
            }
            if (!found)
                ERR_USERNOTFOUND(receivers[i]);
            else
                usrs.push_back(receivers[i]);
        }
    }
    std::string msg;
    if (line.size() > 3)
    {
        msg = line[2].substr(1);
        for (size_t i = 3; i < line.size(); i++){
            msg += " ";
            msg += line[i];
        }
    }
    for (size_t i = 0; i < chan.size(); i++)
    {
        for (size_t j = 0; j < channels.size(); j++)
        {
            if (channels[i].get_name() == chan[i])
                channels[i].ft_broadcast(cls, msg);
        }
    }
    for (size_t i = 0; i < usrs.size(); i++)
    {
        ft_send(get_client(Clients, usrs[i]), msg.c_str());
    } 
}