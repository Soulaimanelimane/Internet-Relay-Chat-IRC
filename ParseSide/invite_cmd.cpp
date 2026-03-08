/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite_cmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:16:48 by omaezzem          #+#    #+#             */
/*   Updated: 2026/03/08 02:36:55 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

Client &ParseSide::get_client(std::vector<Client *> &Clients, std::string &nickname)
{
    size_t i;
    for (i = 0; i < Clients.size(); i++)
    {
        if (nickname == Clients[i]->get_name())
            break;
    }
    return  *Clients[i];
}

void    ParseSide::Parse_invite(Client &sender, std::string &cmdarg, std::vector<Channel> &channels, std::vector<Client *> & Clients)
{
    std::vector<std::string> line = ft_split(cmdarg, 0);
    if (line.size() < 3)
    {
        ERR_NEEDMOREPARAMS_INVITE();
        return ;
    }
    if (line.size() > 3)
    {
        ERR_TOOMANYPARAMS();
        return ;
    }
    std::string cmd = line[0];
    if (cmd != "INVITE"){
        ERR_CMDDISMATCH(cmd);
        return ;
    }
    std::string nickname = line[1];
    std::string ch = line[2];
    if (ch[0] != '#' && ch[0] != '&'){
        ERR_BADCHANMASK(ch);
        return ;
    }
    Channel *target = NULL;
    bool    is_in = false;
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (channels[i].getname() == ch)
        {
            target = &channels[i];
            is_in = true;
            break;
        }
    }
    if (!is_in)
    {
        ERR_NOSUCHCHANNEL(ch);
        return;
    }
    std::vector<Client*> members = target->getmembers();
    bool isinch = false;
    for (size_t i = 0; i < members.size(); i++)
    {
        if (members[i]->getnickname() == sender.get_name())
        {
            isinch = true;
            break;
        }
    }
    if (!isinch)
    {
        ERR_NOTONCHANNEL(sender.get_name());
        return ;
    }
    // for (size_t i = 0; i < nicknames.size(); i++)
    // {
        bool alreadyInChannel = false;
        for (size_t j = 0; j < members.size(); j++)
        {
            if (members[j]->getnickname() == nickname)
            {
                alreadyInChannel = true;
                break;
            }
        }
        if (alreadyInChannel)
        {
            ERR_USERONCHANNEL_INVITE(nickname, target->getname());
            return ;
        }
        bool foundnick = false;
        for (size_t  k = 0; k < nick.size(); k++){
            if (nickname == nick[k]){
                foundnick = true;
                break;
            }
        }
        if (!foundnick)
        {
            ERR_NOSUCHNICK_INVITE(nickname);
        }
        else
        {
            target->invite_member(sender , get_client(Clients, nickname));
            RPL_INVITING(sender.get_name(), nickname, target->getname());
        }
        // execution 
    // }
}