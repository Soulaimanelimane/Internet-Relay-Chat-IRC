/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:37:28 by omaezzem          #+#    #+#             */
/*   Updated: 2026/03/07 04:08:51 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

int ft_send(Client &cls , const char *str)
{
    return (send(cls.get_Clientsocket(), str, strlen(str), 0));
}
Client::Client(int fd) :  pass(false) , nick(false), user(false), flag(false), join(false), auth_us(false)
{
    sk_fd = fd;
}

void Client::set_name(std::string nick , std::string usr)
{
    nickname = nick;
    username = usr;
}
Client::Client() 
{}


Client::~Client()
{

}


std::string& Client::getnickname()
{
    return nickname;
}