/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:58:21 by bbenaali          #+#    #+#             */
/*   Updated: 2026/02/24 17:39:44 by bbenaali         ###   ########.fr       */
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
        // pollfd data_poll;
        std::string nickname;
        std::string username;

        bool auth_us;

        bool pass;
        bool nick;
        bool user;
    public:
        Client();
        Client(int fd);
        int get_fd(){return (sk_fd);};
        void set_Clientsocket(int fd){sk_fd = fd;};
        int get_Clientsocket(){return (sk_fd);};
        // pollfd &get_pollfd(){return (data_poll);};
        void set_name(std::string nick , std::string usr);
        std::string get_name() {return (username);};
        bool &set_pass() {return pass;};
        bool &set_nick() {return nick;};
        bool &set_user() {return user;};
        bool &set_auth() {return auth_us;};
        
        ~Client();
};


int ft_send(Client & cls, const char *str);



#endif