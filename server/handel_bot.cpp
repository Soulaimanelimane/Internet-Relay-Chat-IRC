/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_bot.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 02:08:16 by slimane           #+#    #+#             */
/*   Updated: 2026/03/12 03:19:48 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "../ParseSide/ParseSide.hpp"

void ft_handel_bot(Client &client, std::string &line, std::vector<Client *> &array, std::vector<Channel> &channels)
{
    std::vector<std::string> cmdLine = ft_split(line, 0);
    std::string cmd = cmdLine[0];
    std::string str;
    if (cmd != "BOT")
    {
        ERR_CMDDISMATCH(cmd);
        return;
    }
    if (cmdLine.size() < 2)
    {
        ERR_NONICKNAMEGIVEN();
        return;
    }
    if (cmdLine.size() > 2)
    {
        ERR_TOOMANYPARAMS();
        return;
    }
    cmd = ft_toupper(cmdLine[1]);
    if (cmd == "LIST")
    {
        str = "NOTE:the members who have @ in their name are admins of this channel \r\n";
        for (size_t i = 0; i < channels.size(); i++)
        {
            if (channels[i].getmembers().size() > 0)
            {
                str = "The members of  this Channel " + channels[i].get_name() + " are :\r\n";
                ft_send(client, str.c_str());
                channels[i].List_members(client);       
            
            }
        }
        
    }
}