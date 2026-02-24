/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 03:33:50 by slimane           #+#    #+#             */
/*   Updated: 2026/02/24 14:37:22 by bbenaali         ###   ########.fr       */
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
    
}


Client::~Client()
{

}