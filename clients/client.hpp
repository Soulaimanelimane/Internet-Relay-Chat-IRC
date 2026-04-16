/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:09:36 by slimane           #+#    #+#             */
/*   Updated: 2026/04/16 11:09:40 by slimane          ###   ########.fr       */
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
        int get_fd(){return (sk_fd);};
        void set_Clientsocket(int fd){sk_fd = fd;};
        int get_Clientsocket(){return (sk_fd);};
        void set_name(std::string nick , std::string usr);
        std::string get_name() {return (nickname);};
        std::string get_username() {return (username);};
        bool &set_pass() {return pass;};
        bool &set_nick() {return nick;};
        bool &set_user() {return user;};
        bool &set_auth() {return auth_us;};

        std::string &get_buffer(){return (buffer);};
        void set_buffer(std::string buf) {buffer = buf;};

        ~Client();
        bool &get_flag() {return flag;};
        void set_flag() {flag = true;};
        std::string    &getnickname();

        std::string get_ip() {return ip_addr;};
        int get_port() {return port;};
        void set_ip(std::string ip) {ip_addr = ip;};
        void set_port(int p) {port = p;};
};

int ft_send(Client & cls, const char *str);


#endif