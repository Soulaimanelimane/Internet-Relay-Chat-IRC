/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:09:42 by bbenaali          #+#    #+#             */
/*   Updated: 2026/04/20 22:17:06 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP 
#define CLIENT_HPP

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
// #include "../server/server.hpp"

class Client
{
    private:
        int sk_fd;
        std::string nickname;
        std::string username;

        std::string buffer;

        bool auth_us ;

        bool pass ;
        bool nick ;
        bool user ;
        bool flag ;

        std::string ip_addr;
        int port;
    public:
        Client();
        Client(int fd);
        int get_fd();
        void set_Clientsocket(int fd);
        int get_Clientsocket();
        void set_name(std::string nick , std::string usr);
        std::string get_name();
        std::string get_username() ;
        bool &set_pass() ;
        bool &set_nick() ;
        bool &set_user() ;
        bool &set_auth() ;

        std::string &get_buffer();
        void set_buffer(std::string buf);

        ~Client();
        bool &get_flag() ;
        void set_flag() ;
        std::string    &getnickname();

        std::string get_ip() ;
        int get_port() ;
        void set_ip(std::string ip);
        void set_port(int p) ;
};

void ft_send(Client & cls, const char *str);


#endif