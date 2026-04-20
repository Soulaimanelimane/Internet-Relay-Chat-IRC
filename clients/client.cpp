/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:37:28 by omaezzem          #+#    #+#             */
/*   Updated: 2026/04/20 18:35:09 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

void ft_send(Client &cls , const char *str)
{
    if (send(cls.get_Clientsocket(), str, strlen(str), 0)  < 0)
        std::cout << "error in send please re-send the message later" << std::endl;
}
Client::Client(int fd) :  auth_us(false),  pass(false) , nick(false), user(false), flag(false)
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