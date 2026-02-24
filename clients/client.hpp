/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:26:44 by slimane           #+#    #+#             */
/*   Updated: 2026/02/24 03:31:50 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLIENT_HPP 
#define CLIENT_HPP

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>




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
        void set_name(std::string nick , std::string usr);
        std::string get_name() {return (nickname);};
        ~Client();
};


int ft_send(Client & cls, const char *str);



#endif