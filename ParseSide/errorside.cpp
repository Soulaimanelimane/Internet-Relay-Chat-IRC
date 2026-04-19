/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorside.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:22:10 by omaezzem          #+#    #+#             */
/*   Updated: 2026/04/18 16:08:07 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"



void ERR_EXCEEDLIMIT(Client &cls) {
    std::string str = "!~Server_IRC exceed limit\r\n";
    ft_send(cls, str.c_str());
    std::cout << str;
}

void ERR_CMDDISMATCH(const std::string &cmd, Client &cls) {
    ft_send(cls, cmd.c_str());
    std::cout << "cmd must be "<< cmd ;
}

void ERR_NONICKNAMEGIVEN(Client &cls) {
    std::string str = "!~Server_IRC 431 :No nickname given\r\n";
    ft_send(cls, str.c_str());
    std::cout << str;
}

void ERR_ERRONEUSNICKNAME(const std::string& nick, Client &cls) {
    std::string str = "!~Server_IRC 432 : " + nick + " :Erroneous nickname\r\n";
    ft_send(cls, str.c_str());
    std::cout << str;
}

void ERR_NICKNAMEINUSE(const std::string& nick, Client &cls) {
    std::string str = "!~Server_IRC 433 : " + nick + " :Nickname is already in use\r\n";
    ft_send(cls, str.c_str());
    std::cout << str;
}


void ERR_NEEDMOREPARAMS_USER(Client &cls) {
    std::string str = "!~Server_IRC 461 USER :Not enough parameters\r\n";
    ft_send(cls, str.c_str());
    std::cout << str;
}

void ERR_CONTAINSPACE(Client &cls) {
    std::string str = "!~Server_IRC must be without white spaces\r\n" ;
    ft_send(cls, str.c_str());
    std::cout << str;
}


void ERR_NEEDMOREPARAMS(const std::string &cmd, Client &cls)
{
    std::string str = "!~Server_IRC Error: Not enough parameters for " + cmd + "\r\n";
    ft_send(cls, str.c_str());
    std::cout << str;
}

void ERR_BADCHANMASK(const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC Error: Invalid channel name: " + channel + "\r\n";
    ft_send(cls, str.c_str());
    std::cout  << str;
}
void ERR_TOOMANYPARAMS(const std::string &cmd, Client &cls)
{
    std::string str = "!~Server_IRC Error: too many parameters for " + cmd + "\r\n";
    ft_send(cls, str.c_str());
    std::cout << str;
}

void ERR_USERNOTFOUND(std::string &var, Client &cls)
{
    std::string str = "!~Server_IRC Error: " + var + " is not a valid user.\r\n";
    ft_send(cls, str.c_str());
    std::cout << str;
}


void ERR_NOSUCHCHANNEL(const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 403 " + channel + " :No such channel\r\n";
    ft_send(cls, str.c_str());
    std::cout << str;
}

void ERR_NOTONCHANNEL(const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 442 " + channel + " :You're not on that channel\r\n";
    ft_send(cls, str.c_str());
    std::cout << str;
}

void ERR_USERNOTINCHANNEL(const std::string &target, const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 441 " + target + " " + channel + " :They aren't on that channel\r\n";
    ft_send(cls, str.c_str());
    std::cout << str;
}

void ERR_NEEDMOREPARAMS_INVITE(const std::string &cmd, Client &cls)
{
    std::string str = "!~Server_IRC 461 " + cmd + " :Not enough parameters\r\n";
    ft_send(cls, str.c_str());
    std::cout << str;
}

void ERR_NOSUCHNICK_INVITE(const std::string &nick, Client &cls)
{
    std::string str = "!~Server_IRC 401 " + nick + " :No such nick\r\n";
    ft_send(cls, str.c_str());
    std::cout << str;
}

void ERR_USERONCHANNEL_INVITE(const std::string &nick, const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 443 " + nick + " " + channel + " :is already on channel\r\n";
    ft_send(cls, str.c_str());
    std::cout << str;
}

void RPL_INVITING(const std::string &inviter, const std::string &nickname, const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 341 " + inviter + " " + nickname + " " + channel + "\r\n";
    ft_send(cls, str.c_str());
    std::cout << str;
}

void RPL_KICK(const std::string &targetUser, const std::string &channel, const std::string &reason)
{
    std::string str = ": KICK " + channel + " " + targetUser;
    if (!reason.empty())
        str += " :" + reason;
    str += "\r\n";
    std::cout << str;
}
