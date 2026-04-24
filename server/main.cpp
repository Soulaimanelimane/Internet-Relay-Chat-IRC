/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:10:06 by bbenaali          #+#    #+#             */
/*   Updated: 2026/04/24 14:49:10 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "../ParseSide/ParseSide.hpp"

bool g_running = true;

void handleSignal(int signal)
{
    (void)signal;
    std::cout << "Server shutting down safely..." << std::endl;
    g_running = false;
}

std::string ft_toupper(std::string &var)
{
    for (size_t i = 0; i < var.size(); i++)
    {
        var[i] = std::toupper(var[i]);
    }
    return var;
}

bool check_some_things(std::string &line)
{
    if(line == "JOIN" || line == "PRIVMSG" || line == "KICK" 
        || line == "MODE" || line == "TOPIC" || line == "INVITE" 
            || line == "QUIT" || line == "BOT")
        return true;
    return false;
}

void parseCommand(Client &client, std::string &line, std::string &pass_word,
                    std::vector<Client *> &array, std::vector<Channel> &channels, ParseSide &parse)
{
    std::vector<std::string> command = ft_split(line, 0);
    if (command.empty())
        return;

    std::string cmd = ft_toupper(command[0]);
    for (size_t i = 0; i < cmd.size(); i++)
    {
        line[i] = cmd[i];
    }
    if (cmd == "PASS")
    {
        if (cmd == "PASS" && !client.set_pass())
            parse.parse_PASS(client, line, pass_word);
        else if (client.set_pass())
        {
            std::cout << "CLIENT[" << client.get_fd() << "] : " << "THE PASSWORD HAS BEEN ENTERED\n";
            send(client.get_fd(), "ERROR: The password has been entered\r\n", 38, 0);   
        }
    }
    else if (cmd == "NICK")
    {
        if (!client.set_pass())
        {
            std::cout << "CLIENT[" << client.get_fd() << "] : " << "YOU NEED TO ENTER THE PASSWORD FIRST\n";
            send(client.get_fd(), "ERROR: You need to enter the password first\r\n", 45, 0);
        }
        else
            parse.parse_NICK(array, client, line);
    }
    else if (cmd == "USER")
    {
        if (!client.set_pass() || !client.set_nick())
        {
            std::cout << "CLIENT[" << client.get_fd() << "] : " << "YOU NEED TO ENTER THE PASSWORD AND THE NICKNAME FIRST\n";
            send(client.get_fd(), "ERROR: You need to enter the password and the nickname first\r\n", 62, 0);
        }
        else
            parse.parse_USER(client, line);
    }
    else
    {
        if (!client.set_auth() && check_some_things(line))
        {
            std::cout << "CLIENT[" << client.get_fd() << "] : " << "YOU NEED TO AUTHENTICATE THE CLIENT FIRST\n";
        }
        else if (cmd == "JOIN")
        {
            parse.parse_Join(line, channels, client);
        }
        else if (cmd == "PRIVMSG")
        {
            parse.parse_PRIVMSG(line, channels, client, array);
        }
        else if (cmd == "KICK")
        {
            parse.parse_KICK(line, channels, array, client);
        }
        else if (cmd == "MODE")
        {
            parse.Parse_mode(line, channels, client, array);
        }
        else if (cmd == "TOPIC")
        {
            parse.Parse_topic(client.getnickname(), line, channels, array, client);
        }
        else if (cmd == "INVITE")
        {
            parse.Parse_invite(client, line, channels, array);
        }
        else if (cmd  == "BOT")
        {
            ft_handel_bot(client, line, array, channels);
        }
        else
        {
            std::cout << "CLIENT[" << client.get_fd() << "] : " << "THIS COMMAND NOT VALID\n";
            send(client.get_fd(), "ERROR: This command is not valid\r\n", 35, 0);
        }
    }

    if (client.set_pass() && client.set_nick() && client.set_user() && !client.get_flag())
    {
        client.set_flag();
        client.set_auth() = true;
        std::cout << "CLIENT[#" << client.get_fd() << " from " 
                    << client.get_ip() <<":" << client.get_port() 
                    << "] : REGISTERED SUCCESSFULLY\n";
        send(client.get_fd(), "Welcome to the IRC server!\r\n", 29, 0);
    }
}




bool isValidPort(std::string str) 
{
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (!isdigit(str[i])) 
            return false;
    }
    
    int i = 0;
    while (str[i] == '0') 
        ++i;
    std::string trimmed = str.substr(i);
    if (trimmed.empty()) 
        trimmed = "0";
    if (trimmed.size() == 0 || trimmed.size() > 5) 
        return false;
    int num = atoi(trimmed.c_str());
    return (num > 0 && num <= 65535);
}


void    close_the_client(std::vector<pollfd> &vec_data_fds, std::vector<Channel> &channels, std::vector<Client *> &client, ParseSide &parse, int i)
{
    std::string nickname = client[i - 1]->get_name();
    parse.parse_Join("JOIN 0", channels, *client[i - 1]);
    close(vec_data_fds[i].fd);
    if (vec_data_fds.size() >= 1)
    {
        delete client[i - 1];
        vec_data_fds.erase(vec_data_fds.begin() + i);
    }
    if (client.size() >= 1)
    {
        client.erase(client.begin() + (i - 1));
    }
    if (parse.nick.size() > 0)
    {
        size_t k = i - 1;
        for (k = 0; k < parse.nick.size(); k++)
        {
            if (parse.nick[k] == nickname)
                break;
        }
        if (k != 0 && parse.nick.size() != k)
            parse.nick.erase(parse.nick.begin() + k);
    }
}

int main(int ac, char *av[])
{
    if (ac != 3)
    {
        std::cout << "Usage: " << av[0] << " <port> <password>" << std::endl;
        return (1);
    }
    if (!isValidPort(av[1]))
    {
        std::cerr << "ERROR: Invalid port. Must be an integer between 1 and 65535.\n";
        return 1;
    }
    int num = atoi(av[1]);
    int fd_server = socket(AF_INET, SOCK_STREAM, 0);

    if (fd_server < 0)
    {
        std::cout << "ERROR: OPEN SOCKET" << fd_server << std::endl;
        return (1);
    }

    int opt = 1;
    if (setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        std::cerr << "ERROR: setsockopt failed\n";
        close(fd_server);
        return 1;
    }

    sockaddr_in data_ser;
    data_ser.sin_family = AF_INET;
    data_ser.sin_addr.s_addr =  INADDR_ANY;
    data_ser.sin_port = htons(num);

    if (bind(fd_server, (sockaddr *)&data_ser, sizeof(data_ser)) == -1)
    {
        close(fd_server);
        std::cerr << "Bind failed" << std::endl;
        return 1;
    }
    if (listen(fd_server, 10) == -1)
    {
        std::cerr << "Listen failed" << std::endl;;
        close(fd_server);
        return 1;
    }
    fcntl(fd_server, F_SETFL, O_NONBLOCK);
    std::cout << "Server running on port " << num << " ..." << std::endl;

    std::vector<Client *> client;
    ParseSide parse;
    std::vector<pollfd> vec_data_fds;
    pollfd data_fds;

    data_fds.fd = fd_server;
    data_fds.events = POLLIN;
    data_fds.revents = 0;
    vec_data_fds.push_back(data_fds);
    std::vector<Channel> channels;
    int for_poll = 0;

    signal(SIGINT, handleSignal);
    while (true)
    {
        if(for_poll != -1)
            for_poll = poll(&vec_data_fds[0], vec_data_fds.size(), -1);
        if (!g_running || for_poll < 0)
        {
            if((for_poll == -1 || for_poll == -2) && g_running)
                std::cerr << "ERROR: POLL failed" << std::endl;
            else
                std::cout << "Closing server..." << std::endl;
            for (size_t i = 0; i < vec_data_fds.size(); i++)
            {
                close(vec_data_fds[i].fd);
            }
            for (size_t i = 0; i < client.size(); i++){
                delete client[i];
            }
            return 1;
        }
        int size_vd = vec_data_fds.size();
        for (int i = 0; i < size_vd; i++)
        {
            if (vec_data_fds[i].revents & (POLLERR | POLLNVAL))
            {
                if(vec_data_fds[i].fd == fd_server)
                {
                    std::cerr << "ERROR: Server socket error\n";
                    for_poll = -2;
                    break ;
                }
                if (client[i - 1]->set_auth())
                    std::cout << "CLIENT[#" << vec_data_fds[i].fd << " from " 
                            << client[i - 1]->get_ip()
                            <<":" << client[i - 1]->get_port()
                            << "] : DISCONNECTED\n";
                close_the_client(vec_data_fds, channels, client, parse, i);
                --i;
                continue;
            }
            if (vec_data_fds[i].revents & POLLIN)
            {
                if (vec_data_fds[i].fd == fd_server)
                {
                    sockaddr_in client_addr;
                    socklen_t client_len = sizeof(client_addr);

                    int client_fd = accept(fd_server, (sockaddr *)&client_addr, &client_len);
                    if (client_fd != -1)
                    {
                        fcntl(client_fd, F_SETFL, O_NONBLOCK);

                        
                        pollfd data_fds;
                        data_fds.fd = client_fd;
                        data_fds.events = POLLIN;
                        data_fds.revents = 0;
                        vec_data_fds.push_back(data_fds);
                        try
                        {
                            Client *cls = new Client(client_fd);
                            cls->set_ip(inet_ntoa(client_addr.sin_addr));
                            cls->set_port(ntohs(client_addr.sin_port));
                            client.push_back(cls);
                        }
                        catch(const std::exception& e)
                        {
                            std::string str_err = "failed allocation of the new client :( \r\nthe server closing now ...\r\n";
                            std::cout << str_err;

                            for (size_t i = 0; i < client.size(); i++)
                            {
                                ft_send(*client[i], str_err.c_str());
                                delete client[i];
                            }
                            for (size_t i = 0; i < vec_data_fds.size(); i++)
                                close(vec_data_fds[i].fd);
                            std::cerr << e.what() << std::endl;;
                            return 1;
                        }
                    }
                    else
                    {
                        std::cerr << "Accept failed" << std::endl;
                    }
                }
                else
                {
                    char buffer[1024];
                    int bytes = recv(vec_data_fds[i].fd, buffer, 1000, 0);
                    std::string tmp = av[2];
                    if (bytes > 0)
                    {
                        std::string str(buffer, bytes);
                        std::cout <<  "here i:" << i << std::endl;
                        if ((i - 1) > -1)
                        {
                            std::cout << "here" << std::endl;
                            if(str.size() > 512)
                            {
                                std::cout << "CLIENT[" << client[i - 1]->get_fd() << "] : " << "DATA TOO BIG\n";
                                send(client[i - 1]->get_fd(), "ERROR: Data too big\r\n", 22, 0);
                                continue;
                            }
                            size_t pos;
                            client[i - 1]->get_buffer() += str;
                            while ((pos = client[i - 1]->get_buffer().find("\r\n")) != std::string::npos)
                            {
                                std::string command = client[i - 1]->get_buffer().substr(0, pos);
                                client[i - 1]->get_buffer().erase(0, pos + 2);
                                parseCommand(*client[i - 1], command, tmp, client, channels, parse);
                            }
                        }
                    }
                    if (bytes <= 0)
                    {
                        if (client[i - 1]->set_auth())
                            std::cout << "CLIENT[#" << vec_data_fds[i].fd << " from " 
                                    << client[i - 1]->get_ip() 
                                    <<":" << client[i - 1]->get_port() 
                                    << "] : DISCONNECTED" << std::endl;
                        close_the_client(vec_data_fds, channels, client, parse, i);
                        i--;
                    }
                }
            }
        }
    }

}