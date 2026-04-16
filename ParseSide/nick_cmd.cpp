/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:21:54 by omaezzem          #+#    #+#             */
/*   Updated: 2026/04/15 19:00:02 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

int is_in_client(std::string nick , std::vector<std::string> &array)
{
    for (size_t i = 0; i < array.size(); i++)
    {
        if (array[i] == nick)
            return 1;
    }
    return 0;
}
void    ParseSide::parse_NICK(std::vector<Client *> &array, Client &client, std::string &cmdarg)
{
    std::vector<std::string> line = ft_split(cmdarg, 0);
    std::string cmd = line[0];
    if (cmd != "NICK")
    {
        ERR_CMDDISMATCH(cmd, client);
        return ;
    }
    if (line.size() < 2){
        ERR_NONICKNAMEGIVEN(client);
        return;
    }
    if (line.size() > 2){
        ERR_TOOMANYPARAMS("NICK", client);
        return ;
    }
    if (line.size() == 2){
        std::string nickname = line[1];
        if (nickname.length() > 20){
            ERR_ERRONEUSNICKNAME(nickname, client);
            return ;
        }
        if (nickname[0] == '-' ||  isdigit(nickname[0])){
            ERR_ERRONEUSNICKNAME(nickname, client);
            return;
        }
        for (size_t i = 0; i < nickname.length(); i++)
        {
            char c = nickname[i];
            if (!std::isalpha(c) && !std::isdigit(c)
                && c != '_' && c != '-'){
                ERR_ERRONEUSNICKNAME(nickname, client);
                return; 
            }
        }
        for (size_t  i = 0; i < array.size(); i++){
            if (nickname == array[i]->getnickname()){
                ERR_NICKNAMEINUSE(nickname, client);
                return ;
            }
        }
        if (client.set_nick() == true)
        {
            for (size_t i = 0; i < nick.size(); i++)
            {
                if (client.get_name() == nick[i])
                {
                    nick[i] = nickname;
                    break;
                }
            }
            client.getnickname() = nickname;
        }
        else
        {
            client.getnickname() = nickname;
            client.set_nick() = true;
            nick.push_back(nickname);
        }
        
        std::cout << "CLIENT[" << client.get_fd() << "] : " << "NICKNAME VALIDE :)" << std::endl;
        send(client.get_fd(), "--> Nickname accepted :)\r\n", 27, 0);
    }
    // check if is registred before pass
}

