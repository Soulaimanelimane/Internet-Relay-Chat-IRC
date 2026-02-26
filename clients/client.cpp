/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:37:28 by omaezzem          #+#    #+#             */
/*   Updated: 2026/02/26 17:04:23 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

int ft_send(Client &cls , const char *str)
{
    return (send(cls.get_Clientsocket(), str, strlen(str), 0));
}
Client::Client(int fd)
{
    sk_fd = fd;
    flag = false;
}

void Client::set_name(std::string nick , std::string usr)
{
    nickname = nick;
    username = usr;
}
Client::Client()
{
    pass = false;
    nick = false;
    user = false;
    flag = false;
    
}


Client::~Client()
{

}


std::string    &Client::getnickname()
{
    return nickname;
}