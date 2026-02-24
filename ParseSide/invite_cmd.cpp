/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite_cmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:16:48 by omaezzem          #+#    #+#             */
/*   Updated: 2026/02/24 03:34:32 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

void    ParseSide::Parse_invite(std::string &sender, std::string &cmdarg, std::vector<Channel *> channels)
{
    std::vector<std::string> line = ft_split(cmdarg, ' ');
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
    std::vector<std::string> nicknames = ft_split(line[1], ',');
    Channel *target = NULL;
    std::string ch = line[2];
    if (ch[0] != '#' && ch[0] != '&'){
        ERR_BADCHANMASK(ch);
        return ;
    }
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (channels[i]->getname() == ch)
        {
            target = channels[i];
            break;
        }
    }
    if (!target)
    {
        ERR_NOSUCHCHANNEL_INVITE(ch);
        return;
    }
    std::vector<Client*> members = target->getmembers();
    bool isinch = false;
    for (size_t i = 0; i < members.size(); i++)
    {
        if (members[i]->getnickname() == sender)
        {
            isinch = true;
            break;
        }
    }
    if (!isinch)
    {
        ERR_NOTONCHANNEL(sender);
        return ;
    }
    for (size_t i = 0; i < nicknames.size(); i++)
    {
        bool alreadyInChannel = false;
        for (size_t j = 0; j < members.size(); j++)
        {
            if (members[j]->getnickname() == nicknames[i])
            {
                alreadyInChannel = true;
                break;
            }
        }
        if (alreadyInChannel)
        {
            ERR_USERONCHANNEL_INVITE(nicknames[i], target->getname());
            continue;
        }
        bool foundnick = false;
        for (size_t  k = 0; k < nick.size(); k++){
            if (nicknames[i] == nick[k]){
                foundnick = true;
                break;
            }
        }
        if (!foundnick)
        {
            ERR_NOSUCHNICK_INVITE(nicknames[i]);
            continue;
        }
        RPL_INVITING(sender, nicknames[i], target->getname());
    }
}