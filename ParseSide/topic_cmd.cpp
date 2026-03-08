/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic_cmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 22:56:32 by omaezzem          #+#    #+#             */
/*   Updated: 2026/03/08 02:34:03 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

void    ParseSide::Parse_topic(std::string &user, std::string &cmdarg, std::vector<Channel > &channels, std::vector<Client *> &Clients)
{
    std::vector<std::string> line = ft_split(cmdarg, 0);
    if (line.size() < 2)
    {
        ERR_NEEDMOREPARAMS();
        return ;
    }
    std::string cmd = line[0];
    
    if (cmd != "TOPIC")
    {
        ERR_CMDDISMATCH("TOPIC");
        return ;
    }
    std::string ch = line[1];
    if (ch[0] != '#' && ch[0] != '&'){
        ERR_BADCHANMASK(ch);
        return ;
    }
    Channel target;
    bool    is_in = false;
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (channels[i].getname() == ch)
        {
            target = channels[i];
            is_in = true;
            break;
        }
    }
    if (!is_in)
    {
        ERR_NOSUCHCHANNEL(ch);
        return;
    }
    bool isinch = false;
    std::vector<Client *>   members = target.getmembers();
    for (size_t i = 0; i < members.size(); i++)
    {
        if (members[i]->getnickname() == user)
        {
            isinch = true;
            break;
        }
    }
    if (!isinch)
    {
        ERR_NOTONCHANNEL(ch);
        return ;
    }
    std::string topic;
    Client &cls = get_client(Clients, user);
    if (line.size() > 2)
    {
        if (line[2] == ":")
            topic = "";
        else if (line[2][0] == ':' && line.size() == 3){
            topic = line[2].substr(1);
        }
        else if (line[2][0] == ':' && line.size() > 3){
            topic = line[2].substr(1);
            for (size_t i = 3; i < line.size(); i++){
                topic += " ";
                topic += line[i];
            }
        }
        target.ft_topic(cls, topic);
    }
    else
        target.ft_topic(cls);
}