/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorside.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:22:10 by omaezzem          #+#    #+#             */
/*   Updated: 2026/03/06 00:01:22 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

void ERR_NEEDMOREPARAMS_PASS() {
    std::cout << "461 PASS :Not enough parameters" << std::endl;
}

void ERR_ALREADYREGISTERED_PASS() {
    std::cout << "462 PASS :You may not reregister" << std::endl;
}

void ERR_PASSWDMISMATCH() {
    std::cout << "464 :Password incorrect" << std::endl;
}

void ERR_EXCEEDLIMIT() {
    std::cout << "exceed limit" << std::endl;
}

void ERR_CMDDISMATCH(const std::string &cmd) {
    std::cout << "cmd must be "<< cmd << std::endl;
}

void ERR_NONICKNAMEGIVEN() {
    std::cout << "431 :No nickname given" << std::endl;
}

void ERR_ERRONEUSNICKNAME(const std::string& nick) {
    std::cout << "432 " << nick << " :Erroneous nickname" << std::endl;
}

void ERR_NICKNAMEINUSE(const std::string& nick) {
    std::cout << "433 " << nick << " :Nickname is already in use" << std::endl;
}


void ERR_NICKCOLLISION(const std::string& nick) {
    std::cout << "436 " << nick << " :Nickname collision" << std::endl;
}

void ERR_NEEDMOREPARAMS_USER() {
    std::cout << "461 USER :Not enough parameters" << std::endl;
}

void ERR_CONTAINSPACE() {
    std::cout << "must be without white spaces" << std::endl;
}


void ERR_INVALIDUSERNAME(const std::string& username) {
    std::cout << "464 " << username << " :Invalid username" << std::endl;
}

void ERR_CMDMISMATCH(const std::string &expected)
{
    std::cout << "Error: Expected command " << expected << std::endl;
}

void ERR_NEEDMOREPARAMS()
{
    std::cout << "Error: Not enough parameters for " << std::endl;
}

void ERR_BADCHANMASK(const std::string &channel)
{
    std::cout << "Error: Invalid channel name: " << channel << std::endl;
}
void ERR_TOOMANYPARAMS()
{
    std::cout << "Error: too many parameteres : " << std::endl;
}
void ERR_USERNOTFOUND(std::string &var)
{
    std::cout << "Error: " << var << " is not a valid user.\n";
}
void ERR_NICKNOTFOUND(std::string &var)
{
    std::cout << "Error: " << var << " is not a valid nickname.\n";
}

void ERR_NOSUCHCHANNEL(const std::string &channel)
{
    std::cout <<  "Error: No such channel -> " << channel << std::endl;
}

void ERR_NOTONCHANNEL(const std::string &channel)
{
    std::cout << "422 Error: You're not on channel -> " << channel << std::endl;
}

void ERR_USERNOTINCHANNEL(const std::string &target, const std::string &channel)
{
    std::cout << "Error: User " << target << " is not in channel " << channel << std::endl;
}

void ERR_CHANOPRIVSNEEDED(const std::string &channel)
{
    std::cout << "Error: Channel operator privileges needed for " << channel << std::endl;
}

void ERR_ISEMPTY()
{
    std::cout << "Error: user is empty" << std::endl;
}

void ERR_NEEDMOREPARAMS_INVITE() 
{
    std::cout << "461 :Not enough parameters" << std::endl;
}
void ERR_NOSUCHNICK_INVITE(const std::string &nick) {
    std::cout << "401 " << nick << " :No such nick" << std::endl;
}
void ERR_NOSUCHCHANNEL_INVITE(const std::string &channel) {
    std::cout << "403 " << channel << " :No such channel" << std::endl;
}

void ERR_NOTONCHANNEL_INVITE(const std::string &channel) {
    std::cout << "442 " << channel << " :You're not on that channel" << std::endl;
}

void ERR_CHANOPRIVSNEEDED_INVITE(const std::string &channel) {
    std::cout << "482 " << channel << " :You're not channel operator" << std::endl;
}

void ERR_USERONCHANNEL_INVITE(const std::string &nick, const std::string &channel) {
    std::cout << "443 " << nick << " " << channel << " :is already on channel" << std::endl;
}

void ERR_ERRONEUSNICKNAME_INVITE(const std::string &nick) {
    std::cout << "400 " << nick << " :Erroneous nickname" << std::endl;
}

void ERR_CANNOTSENDTOCHAN_INVITE(const std::string &channel) {
    std::cout << "406 " << channel << " :Cannot send to channel" << std::endl;
}

void RPL_INVITING(const std::string &inviter,
                  const std::string &nickname,
                  const std::string &channel)
{
    std::cout << "341 " << inviter << " " << nickname << " " << channel << std::endl;
}
void RPL_KICK(const std::string &targetUser, const std::string &channel, const std::string &reason)
{
    std::cout << ":" << " KICK " << channel << " " << targetUser;
    if (!reason.empty())
        std::cout << " :" << reason;
    std::cout << std::endl;
}

void    ERR_CHANOPRIVSNEEDED(std::string &nickname, std::string &channel)
{
    std::cout << "482 " << nickname << channel <<  ":You're not channel operator" << std::endl;
}