/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg_cmd.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:21:32 by omaezzem          #+#    #+#             */
/*   Updated: 2026/02/26 15:01:14 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

void    ParseSide::parse_PRIVMSG(std::string &cmdarg, std::vector<Channel> &channels)
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
    std::vector<std::string>  chan;
    std::vector<std::string> receivers = ft_split(line[1], ',');
    for (size_t i = 0; i < receivers.size(); i++) {
        bool found = false;
        for (size_t j = 0; j < user.size(); j++) {
            if (user[j] == receivers[i]) {
                found = true;
                break;
            }
            if (receivers[i][0] == '#' || '&')
                chan.push_back(receivers[i]);
        }
        if (!found) {
            ERR_USERNOTFOUND(receivers[i]);
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
}