/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg_cmd.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:21:32 by omaezzem          #+#    #+#             */
/*   Updated: 2026/02/28 06:29:38 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

void    ParseSide::parse_PRIVMSG(std::string &cmdarg, std::vector<Channel > &channels, Client &cls, std::vector<Client> &Clients)
{
    std::vector<std::string> line = ft_split(cmdarg, 0);
    if (line.empty() || line[0] != "PRIVMSG")
    {
        ERR_CMDDISMATCH("PRIVMSG");
        return;
    }
    if (line.size() <= 2){
        ERR_NEEDMOREPARAMS();
        return;
    }
    std::vector<std::string> receivers = ft_split(line[1], ',');
    std::vector<std::string>  chan;
    std::vector<std::string> usrs;
    for (size_t i = 0; i < receivers.size(); i++) {
        // if (receivers[i].empty() == false)
        //     continue;
        bool found = false;
        if (receivers[i][0] == '#' || receivers[i][0] == '&')
        {
            for (size_t j = 0; j < channels.size(); j++)
            {
                if (channels[j].get_name() == receivers[i])
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
            for (size_t j = 0; j < nick.size(); j++) {
                if (nick[j] == receivers[i])
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
        msg += "\r\n";
    }
    else
        msg = line[2].substr(1) + "\r\n";

    std::string str;
    for (size_t i = 0; i < chan.size(); i++)
    {
        for (size_t j = 0; j < channels.size(); j++)
        {
            if (channels[j].get_name() == chan[i])
            {
                
                str =  ":" + cls.get_name() + "!~Server_irc PRIVMSG " + chan[i] + " :" + msg;;
                channels[j].ft_broadcast(cls, str);
            }
        }
    }
    for (size_t i = 0; i < usrs.size(); i++)
    {
        str = ":"+ cls.get_name() + "!~Server_irc PRIVMSG " + usrs[i] + " :" + msg;
        ft_send(get_client(Clients, usrs[i]), str.c_str());
    } 
}