/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:37:28 by omaezzem          #+#    #+#             */
/*   Updated: 2026/04/24 16:50:27 by bbenaali         ###   ########.fr       */
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

int Client::get_fd()
{
    return (sk_fd);
}

void Client::set_Clientsocket(int fd)
{
    sk_fd = fd;
}

int Client::get_Clientsocket()
{
    return (sk_fd);
}

std::string Client::get_name() {return (nickname);};
std::string Client::get_username() {return (username);};
bool &Client::set_pass() {return pass;};
bool &Client::set_nick() {return nick;};
bool &Client::set_user() {return user;};
bool &Client::set_auth() {return auth_us;};

std::string &Client::get_buffer(){return (buffer);};
void Client::set_buffer(std::string buf) {buffer = buf;};


bool &Client::get_flag() {return flag;};
void Client::set_flag() {flag = true;};

std::string Client::get_ip() {return ip_addr;};
int Client::get_port() {return port;};
void Client::set_ip(std::string ip) {ip_addr = ip;};
void Client::set_port(int p) {port = p;};

std::string& Client::getnickname()
{
    return nickname;
}