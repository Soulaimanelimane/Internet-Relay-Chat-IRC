/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_bot.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 02:08:16 by slimane           #+#    #+#             */
/*   Updated: 2026/04/23 21:52:40 by slimane          ###   ########.fr       */
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
        ERR_CMDDISMATCH(cmd, client);
        return;
    }
    if (cmdLine.size() < 2)
    {
        ERR_NONICKNAMEGIVEN(client);
        return;
    }
    if (cmdLine.size() > 2)
    {
        ERR_TOOMANYPARAMS(cmd, client);
        return;
    }
    cmd = ft_toupper(cmdLine[1]);
    if (cmd == "LIST")
    {
        if(channels.size() == 0)
        {
            str = "There are no channels available on the server.\r\n";
            ft_send(client, str.c_str());
            return;
        }
        str = "NOTE:the members who have @ in their name are admins of this channel \r\n";
        ft_send(client, str.c_str());   
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

    if(cmd == "CHANNELS")
    {
        if(channels.size() == 0)
        {
            str = "There are no channels available on the server.\r\n";
            ft_send(client, str.c_str());
            return;
        }
        str = "The available channels are :\r\n";
        ft_send(client, str.c_str());
        for (size_t i = 0; i < channels.size(); i++)
        {
            str = channels[i].get_name() + "\r\n";
            ft_send(client, str.c_str());
        }
    }

    if(cmd == "USERS")
    {
        str = "The available users are :\r\n";
        ft_send(client, str.c_str());
        for (size_t i = 0; i < array.size(); i++)
        {
            str = array[i]->get_name() + "\r\n";
            ft_send(client, str.c_str());
        }
    }
    if(cmd == "INFO")
    {
        str = "This bot is designed to provide information about the channels and users on the server. It can list the members of each channel, display the available channels, and show the registered users. Use the commands 'BOT LIST', 'BOT CHANNELS', 'BOT USERS', and 'BOT HELP' for more details.\r\n";
        ft_send(client, str.c_str());
    }
    if(cmd == "STATS")
    {
        str = "Server Statistics:\r\n";
        std::stringstream ss1, ss2;

        ss1 << channels.size();
        str += "Total Channels: " + ss1.str() + "\r\n";

        ss2 << array.size();
        str += "Total Users: " + ss2.str() + "\r\n";
        ft_send(client, str.c_str());
    }
    if(cmd == "HELP")
    {
        str = "Available BOT Commands:\r\n";
        str += "BOT LIST - List members of each channel\r\n";
        str += "BOT CHANNELS - List all available channels\r\n";
        str += "BOT USERS - List all registered users\r\n";
        str += "BOT INFO - Get information about the bot\r\n";
        str += "BOT STATS - Get server statistics\r\n";
        ft_send(client, str.c_str());
    }
    if (cmd == "CMD")
    {
        str = "available  commands in our server:\r\n";
        str += "PASS 'the password to connect with server'\r\n";
        str += "NICK 'your <nickname>'\r\n";
        str += "USER  'your  <username> 0 * : <realname>'\r\n";
        str += "JOIN '<channel>{,<channel>} [<key>{,<key>}]'\r\n";
        str += "PRIVMSG '<target>{,<target>} : <text to be sent>'\r\n";
        str += "KICK '<channel> <user> *( ',' <user> ) [<reason>]'\r\n";
        str += "INVITE '<nickname> <channel name>'\r\n";
        str += "TOPIC '<channel>  :<topic>'\r\n";
        str += "TOPIC '<channel>'\r\n";
        str += "MODE '<channel name> [<modestring> [<mode arguments>...]]'\r\n";
        ft_send(client, str.c_str());
    }
    else if (cmd != "LIST" && cmd != "CHANNELS" && cmd != "USERS" && cmd != "INFO" && cmd != "STATS" && cmd != "HELP" && cmd != "CMD")
    {
        ERR_CMDDISMATCH(cmd, client);
        return;
    }
}