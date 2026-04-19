/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:08:09 by slimane           #+#    #+#             */
/*   Updated: 2026/03/31 16:08:10 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

void    ParseSide::parse_PASS(Client &client, std::string &cmdarg, std::string &correct_pass)
{
    std::vector<std::string> line = ft_split(cmdarg, 0);
    std::string cmd = line[0];
    if (cmd != "PASS"){
        ERR_CMDDISMATCH(cmd, client);
        return ;
    }
    if (line.size() < 2){
        ERR_NEEDMOREPARAMS(cmd, client);
        return;
    }
    if (line.size() > 2){
        ERR_TOOMANYPARAMS(cmd, client);
        return;
    }
    std::string client_password = line[1];
    if (client_password.length() > 255){
        ERR_EXCEEDLIMIT(client);
        return;
    }
    if(client_password == correct_pass)
    {
        client.set_pass() = true;
        std::cout << "CLIENT[" << client.get_fd() << "] : " <<  "PASSWORD CORRECT :) \n";
        send(client.get_fd(), "--> Password accepted :)\r\n", 27, 0);
    }
    else
    {
        std::cout << "CLIENT[" << client.get_fd() << "] : " << "PASSWORD INCORRECT :( \n";
        send(client.get_fd(), "ERROR: Incorrect password :(\r\n", 31, 0);
    }
}