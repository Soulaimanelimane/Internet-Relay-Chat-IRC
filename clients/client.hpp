/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 21:39:51 by slimane           #+#    #+#             */
/*   Updated: 2026/02/22 16:29:21 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP 
#define CLIENT_HPP

#include <iostream>
#include <vector>
#include <sys/socket.h>


class Client
{
    private:
        int sk_fd;
        std::string nickname;
        std::string username;
        int auth_us;

        bool pass;
        bool nick;
        bool user;
    public:
        void set_Clientsocket(int fd){sk_fd = fd;};
        int get_Clientsocket(){return (sk_fd);};
        void set_name(std::string nick , std::string usr){};
        std::string get_name() {return (username);};
        ~Client();
};


int ft_send(Client & cls, const char *str);
Client::Client(/* args */)
{
}

Client::~Client()
{
}


#endif