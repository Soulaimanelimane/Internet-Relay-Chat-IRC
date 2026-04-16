/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorside.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:22:10 by omaezzem          #+#    #+#             */
/*   Updated: 2026/04/16 11:24:23 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

void ERR_NEEDMOREPARAMS_PASS(Client &cls) {
    std::string str = "!~Server_IRC 461 PASS :Not enough parameters\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_ALREADYREGISTERED_PASS(Client &cls) {
    std::string str = "!~Server_IRC 462 PASS :You may not reregister\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_PASSWDMISMATCH(Client &cls) {
    std::string str = "!~Server_IRC 464 :Password incorrect\r\n";
    ft_send(cls, str.c_str());
    std::cout <<  str << std::endl;
}

void ERR_EXCEEDLIMIT(Client &cls) {
    std::string str = "!~Server_IRC exceed limit\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_CMDDISMATCH(const std::string &cmd, Client &cls) {
    ft_send(cls, cmd.c_str());
    std::cout << "cmd must be "<< cmd << "\r\n" << std::endl;
}

void ERR_NONICKNAMEGIVEN(Client &cls) {
    std::string str = "!~Server_IRC 431 :No nickname given\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_ERRONEUSNICKNAME(const std::string& nick, Client &cls) {
    std::string str = "!~Server_IRC 432 : " + nick + " :Erroneous nickname\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_NICKNAMEINUSE(const std::string& nick, Client &cls) {
    std::string str = "!~Server_IRC 433 : " + nick + " :Nickname is already in use\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_NICKCOLLISION(const std::string& nick, Client &cls) {
    std::string str = "!~Server_IRC 436 : " + nick + " :Nickname collision\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_NEEDMOREPARAMS_USER(Client &cls) {
    std::string str = "!~Server_IRC 461 USER :Not enough parameters\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_CONTAINSPACE(Client &cls) {
    std::string str = "!~Server_IRC must be without white spaces\r\n" ;
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}


void ERR_INVALIDUSERNAME(const std::string& username, Client &cls) {
    std::string str = "!~Server_IRC 468 " + username + " :Invalid username" + "\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_CMDMISMATCH(const std::string &expected, Client &cls)
{
    std::string str = "!~Server_IRC Error: Expected command " + expected + "\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_NEEDMOREPARAMS(const std::string &cmd, Client &cls)
{
    std::string str = "!~Server_IRC Error: Not enough parameters for " + cmd + "\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_BADCHANMASK(const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC Error: Invalid channel name: " + channel + "\r\n";
    ft_send(cls, str.c_str());
    std::cout  << str << std::endl;
}
void ERR_TOOMANYPARAMS(const std::string &cmd, Client &cls)
{
    std::string str = "!~Server_IRC Error: too many parameters for " + cmd + "\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_USERNOTFOUND(std::string &var, Client &cls)
{
    std::string str = "!~Server_IRC Error: " + var + " is not a valid user.\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_NICKNOTFOUND(std::string &var, Client &cls)
{
    std::string str = "!~Server_IRC Error: " + var + " is not a valid nickname.\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_NOSUCHCHANNEL(const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 403 " + channel + " :No such channel\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_NOTONCHANNEL(const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 442 " + channel + " :You're not on that channel\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_USERNOTINCHANNEL(const std::string &target, const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 441 " + target + " " + channel + " :They aren't on that channel\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_CHANOPRIVSNEEDED(const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 482 " + channel + " :You're not channel operator\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_ISEMPTY(const std::string &cmd, Client &cls)
{
    std::string str = "!~Server_IRC Error: " + cmd + " parameter is empty\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_NEEDMOREPARAMS_INVITE(const std::string &cmd, Client &cls)
{
    std::string str = "!~Server_IRC 461 " + cmd + " :Not enough parameters\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_NOSUCHNICK_INVITE(const std::string &nick, Client &cls)
{
    std::string str = "!~Server_IRC 401 " + nick + " :No such nick\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_NOSUCHCHANNEL_INVITE(const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 403 " + channel + " :No such channel\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_NOTONCHANNEL_INVITE(const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 442 " + channel + " :You're not on that channel\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_CHANOPRIVSNEEDED_INVITE(const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 482 " + channel + " :You're not channel operator\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_USERONCHANNEL_INVITE(const std::string &nick, const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 443 " + nick + " " + channel + " :is already on channel\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_CANNOTSENDTOCHAN_INVITE(const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 404 " + channel + " :Cannot send to channel\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void RPL_INVITING(const std::string &inviter, const std::string &nickname, const std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 341 " + inviter + " " + nickname + " " + channel + "\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void RPL_KICK(const std::string &targetUser, const std::string &channel, const std::string &reason, Client &cls)
{
    std::string str = ": KICK " + channel + " " + targetUser;
    if (!reason.empty())
        str += " :" + reason;
    str += "\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}

void ERR_CHANOPRIVSNEEDED(std::string &nickname, std::string &channel, Client &cls)
{
    std::string str = "!~Server_IRC 482 " + nickname + " " + channel + " :You're not channel operator\r\n";
    ft_send(cls, str.c_str());
    std::cout << str << std::endl;
}