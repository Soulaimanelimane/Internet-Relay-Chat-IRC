/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseSide.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:01:02 by omaezzem          #+#    #+#             */
/*   Updated: 2026/02/26 17:03:40 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSESIDE_HPP
#define PARSESIDE_HPP

// #include "../clients/client.hpp"
#include "../channels/channel.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>


class Client;

class ParseSide {
// private:
public:
    void    parse_Join(const std::string &cmdarg, std::vector<Channel> &all_channels, Client &cls);
    void    parse_PASS(Client &client, std::string &cmdarg, std::string &correct_pass);
    void    parse_NICK(std::vector<Client> &array, Client &client, std::string &cmdarg);
    void    parse_USER(Client &client, std::string &cmdarg);
    void    addusernicktoclient(std::vector<Client> &clients);
    void    parse_PRIVMSG(std::string &cmdarg, std::vector<Channel > &channels, Client &cls, std::vector<Client> &Clients);
    void    parse_KICK(std::string &cmdarg, std::vector<Channel > &channels, std::vector<Client> &Clients,  Client &cls);
    void    Parse_invite(Client &sender, std::string &cmdarg, std::vector<Channel > &channels, std::vector<Client> & Clients);
    void    Parse_mode(std::string &cmdarg, std::vector<Channel > &channels);
    void    Parse_topic(std::string &user, std::string &cmdarg, std::vector<Channel > &channels, std::vector<Client> &Clients);
    Client &get_client(std::vector<Client> & Clients, std::string &nickname);
    
    std::vector<std::string> nick;
    std::vector<std::string> user;
    std::vector<std::string> rname;

    // void get_nickname();
};




std::vector<std::string> ft_split(const std::string& str, char delim);
bool    check_is_contain_space(std::string var);

void ERR_NEEDMOREPARAMS_PASS();
void ERR_ALREADYREGISTERED_PASS();
void ERR_PASSWDMISMATCH();
void ERR_EXCEEDLIMIT();
void ERR_NONICKNAMEGIVEN();
void ERR_ERRONEUSNICKNAME(const std::string &nick);
void ERR_NICKNAMEINUSE(const std::string &nick);
void ERR_NICKCOLLISION(const std::string &nick);
void ERR_NEEDMOREPARAMS_USER();
void ERR_INVALIDUSERNAME(const std::string &username);
void ERR_CMDDISMATCH(const std::string &cmd);
void ERR_CONTAINSPACE();
void ERR_BADCHANMASK(const std::string &channel);
void ERR_NEEDMOREPARAMS();
void ERR_TOOMANYPARAMS();
void ERR_USERNOTFOUND(std::string &var);
void ERR_NOSUCHCHANNEL(const std::string &channel);
void ERR_NOTONCHANNEL(const std::string &channel);
void ERR_USERNOTINCHANNEL(const std::string &target, const std::string &channel);
void ERR_CHANOPRIVSNEEDED(const std::string &channel);
void ERR_ISEMPTY();
void ERR_NICKNOTFOUND(std::string &var);
void ERR_NEEDMOREPARAMS_INVITE();
void ERR_NOSUCHNICK_INVITE(const std::string &nick);
void ERR_NOSUCHCHANNEL_INVITE(const std::string &channel);
void ERR_NOTONCHANNEL_INVITE(const std::string &channel);
void ERR_CHANOPRIVSNEEDED_INVITE(const std::string &channel);
void ERR_USERONCHANNEL_INVITE(const std::string &nick, const std::string &channel);
void ERR_ERRONEUSNICKNAME_INVITE(const std::string &nick);
void ERR_CANNOTSENDTOCHAN_INVITE(const std::string &channel);
void RPL_INVITING(const std::string &inviter, const std::string &nickname, const std::string &channel);
void RPL_KICK(const std::string &targetUser, const std::string &channel, const std::string &reason);
void    ERR_CHANOPRIVSNEEDED(std::string &nickname, std::string &channel);
// bool    check_multiple_twopoint(std::string &var);
#endif 

