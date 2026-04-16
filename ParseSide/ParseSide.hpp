/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseSide.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:01:02 by omaezzem          #+#    #+#             */
/*   Updated: 2026/04/16 11:29:11 by slimane          ###   ########.fr       */
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
    void    parse_NICK(std::vector<Client *> &array, Client &client, std::string &cmdarg);
    void    parse_USER(Client &client, std::string &cmdarg);
    void    addusernicktoclient(std::vector<Client *> &clients);
    void    parse_PRIVMSG(std::string &cmdarg, std::vector<Channel > &channels, Client &cls, std::vector<Client *> &Clients);
    void    parse_KICK(std::string &cmdarg, std::vector<Channel > &channels, std::vector<Client *> &Clients,  Client &cls);
    void    Parse_invite(Client &sender, std::string &cmdarg, std::vector<Channel > &channels, std::vector<Client *> & Clients);
    void    Parse_mode(std::string &cmdarg, std::vector<Channel> &channels, Client &cls, std::vector<Client *> &clients);
    void    Parse_topic(std::string &user, std::string &cmdarg, std::vector<Channel > &channels, std::vector<Client *> &Clients, Client &cls);
    Client &get_client(std::vector<Client *> & Clients, std::string &nickname);
    
    std::vector<std::string> nick;
    std::vector<std::string> user;
    std::vector<std::string> rname;

    // void get_nickname();
};



// void add_nickname(std::string &name);
// void add_username(std::string &name);
// void add_rname(std::string &name);


std::vector<std::string> ft_split(const std::string& str, char delim);
bool    check_is_contain_space(std::string var);

void ERR_NEEDMOREPARAMS_PASS(Client &cls);
void ERR_ALREADYREGISTERED_PASS(Client &cls);
void ERR_PASSWDMISMATCH(Client &cls);
void ERR_EXCEEDLIMIT(Client &cls);
void ERR_CMDDISMATCH(const std::string &cmd, Client &cls);
void ERR_NONICKNAMEGIVEN(Client &cls);
void ERR_ERRONEUSNICKNAME(const std::string &nick, Client &cls);
void ERR_NICKNAMEINUSE(const std::string &nick, Client &cls);
void ERR_NICKCOLLISION(const std::string &nick, Client &cls);
void ERR_NEEDMOREPARAMS_USER(Client &cls);
void ERR_CONTAINSPACE(Client &cls);
void ERR_INVALIDUSERNAME(const std::string &username, Client &cls);
void ERR_CMDMISMATCH(const std::string &expected, Client &cls);
void ERR_NEEDMOREPARAMS(const std::string &cmd, Client &cls);
void ERR_BADCHANMASK(const std::string &channel, Client &cls);
void ERR_TOOMANYPARAMS(const std::string &cmd, Client &cls);
void ERR_USERNOTFOUND(std::string &var, Client &cls);
void ERR_NICKNOTFOUND(std::string &var, Client &cls);
void ERR_NOSUCHCHANNEL(const std::string &channel, Client &cls);
void ERR_NOTONCHANNEL(const std::string &channel, Client &cls);
void ERR_USERNOTINCHANNEL(const std::string &target, const std::string &channel, Client &cls);
void ERR_CHANOPRIVSNEEDED(const std::string &channel, Client &cls);
void ERR_ISEMPTY(const std::string &cmd, Client &cls);
void ERR_NEEDMOREPARAMS_INVITE(const std::string &cmd, Client &cls);
void ERR_NOSUCHNICK_INVITE(const std::string &nick, Client &cls);
void ERR_NOSUCHCHANNEL_INVITE(const std::string &channel, Client &cls);
void ERR_NOTONCHANNEL_INVITE(const std::string &channel, Client &cls);
void ERR_CHANOPRIVSNEEDED_INVITE(const std::string &channel, Client &cls);
void ERR_USERONCHANNEL_INVITE(const std::string &nick, const std::string &channel, Client &cls);
void ERR_ERRONEUSNICKNAME(const std::string &nick, Client &cls);
void ERR_CANNOTSENDTOCHAN_INVITE(const std::string &channel, Client &cls);
void RPL_INVITING(const std::string &inviter, const std::string &nickname, const std::string &channel, Client &cls);
void RPL_KICK(const std::string &targetUser, const std::string &channel, const std::string &reason, Client &cls);
void ERR_CHANOPRIVSNEEDED(std::string &nickname, std::string &channel, Client &cls);
// bool    check_multiple_twopoint(std::string &var);
#endif 

