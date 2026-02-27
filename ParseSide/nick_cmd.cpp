/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:21:54 by omaezzem          #+#    #+#             */
/*   Updated: 2026/02/27 00:47:00 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

void    ParseSide::parse_NICK(std::vector<Client> &array, Client &client, std::string &cmdarg)
{
    std::vector<std::string> line = ft_split(cmdarg, ' ');
    std::string cmd = line[0];
    if (cmd != "NICK")
    {
        ERR_CMDDISMATCH(cmd);
        return ;
    }
    if (line.size() < 2){
        ERR_NONICKNAMEGIVEN();
        return;
    }
    if (line.size() > 2){
        ERR_TOOMANYPARAMS();
        return ;
    }
    if (line.size() == 2){
        std::string nickname = line[1];
        if (nickname.length() > 20){
            ERR_ERRONEUSNICKNAME(nickname);
            return ;
        }
        if (nickname[0] == '-' ||  isdigit(nickname[0])){
            ERR_ERRONEUSNICKNAME(nickname);
            return;
        }
        for (size_t i = 0; i < nickname.length(); i++)
        {
            char c = nickname[i];
            if (!std::isalpha(c) && !std::isdigit(c)
                && c != '_' && c != '-'){
                ERR_ERRONEUSNICKNAME(nickname);
                return; 
            }
        }
        for (size_t  i = 0; i < array.size(); i++){
            if (nickname == array[i].getnickname()){
                ERR_NICKNAMEINUSE(nickname);
                return ;
            }
        }
        client.getnickname() = nickname;
        client.set_nick() = true;
        std::cout << "CLIENT[" << client.get_fd() << "] : " << "NICKNAME VALIDE :)" << std::endl;
    }
    // check if is registred before pass
}

