/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 03:33:50 by slimane           #+#    #+#             */
/*   Updated: 2026/02/23 21:45:53 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

int ft_send(Client &cls , const char *str)
{
    return (send(cls.get_Clientsocket(), str, strlen(str), 0));
}

Client::Client()
{
}

void Client::set_name(std::string nick , std::string usr)
{
    nickname = nick;
    username = usr;
}


Client::~Client()
{

}


std::string    Client::getnickname()
{
    return nickname;
}