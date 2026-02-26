/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 21:10:45 by bbenaali          #+#    #+#             */
/*   Updated: 2026/02/26 01:15:18 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "../ParseSide/ParseSide.hpp"

void parseCommand(Client &client, std::string &line, std::string &pass_word)
{
    // std::istringstream iss(line);
    // std::string command;
    // iss >> command;
    // (void)line;
        // std::cout << "pass correct \n";
        ParseSide parse;
        std::cout << line << std::endl;
    
    if (!client.set_pass())
    {
        // client.set_pass() = true;
        // std::cout << "i'm chicking the password\n";
        parse.parse_PASS(client, line, pass_word);
        // std::string password;
        // iss >> password;
        // if (password == "brahim")
        // {
        //     client.set_pass() = true;
        //     std::cout << "New client connected\n";
        // }
        // else
        //     send(client.get_fd(), "ERROR: WRONG PASSWORD\n", 22, 0);
        // std::cout << "her\n";
    }
    else if (client.set_pass() && (!client.set_nick() || !client.set_user()))
    {
        if(!client.set_nick())
        {
            // client.set_nick() = true;cle
            // std::cout << "i'm chiking the nickname\n";   
            parse.parse_NICK(client, line);
        }
        else if(!client.set_user())
        {
            // client.set_user() = true;
            // std::cout << "i'm chiking the user\n";   
            parse.parse_USER(client, line);
        }
        // std::string nick;
        // iss >> nick;

        // if (!nick.empty())
        // {
        //     client.set_nick() = true;
        // }
    }
    // else if (command == "USER")
    // {
    //     std::string username;
    //     iss >> username;

    //     if (!username.empty())
    //         client.set_user() = true;
    // }

    if (client.set_pass() && client.set_nick() && client.set_user())
    {
        client.set_auth() = true;
        std::cout << "Client fd["<< client.get_fd() << "] registered successfully\n";
    }
}

int main(int ac, char *av[])
{
    (void)ac;
    int fd_server = socket(AF_INET, SOCK_STREAM, 0);
    if(fd_server < 0)
    {
        std::cout << "ERROR: OPEN SOCKET" << fd_server << std::endl;
        return (1);
    }
    int opt = 1;
    setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in data_ser;
    data_ser.sin_family = AF_INET;
    data_ser.sin_addr.s_addr = INADDR_ANY;
    int num = atoi(av[1]);
    data_ser.sin_port = htons(num);

    if (bind(fd_server, (sockaddr*)&data_ser, sizeof(data_ser)) == -1)
    {
        std::cerr << "Bind failed\n";
        return 1;
    }

    if (listen(fd_server, 10) == -1)
    {
        std::cerr << "Listen failed\n";
        return 1;
    }

    std::cout << "Server running on port " << num <<" ...\n";
    fcntl(fd_server, F_SETFL, O_NONBLOCK);
    std::vector<Client> client;

    // Client *data_pol = new Client;

    // data_pol->get_pollfd().events = POLL_IN;
    // data_pol->get_pollfd().fd = fd_server;
    // data_pol->get_pollfd().revents = 0;
    // data_vec.push_back(data_pol);
    std::vector<pollfd> vec_data_fds;
    pollfd data_fds;

    data_fds.fd = fd_server;
    data_fds.events = POLL_IN;
    data_fds.revents = 0;
    vec_data_fds.push_back(data_fds);

    while (true)
    {
        // std::vector<pollfd> poll_array;
        // std::cout << "lsfladsjflajsflajsdfj\n";
        // for (size_t i = 0; i < clients.size(); i++)
        //     poll_array.push_back(clients[i].get_pollfd());
        poll(&vec_data_fds[0], vec_data_fds.size(), -1);
        for(int i = 0; i < (int)vec_data_fds.size(); i++)
        {
            if(vec_data_fds[i].revents & POLL_IN)
            {
                if(vec_data_fds[i].fd == fd_server)
                {
                    sockaddr_in client_addr;
                    socklen_t client_len = sizeof(client_addr);

                    int client_fd = accept(fd_server, (sockaddr*)&client_addr, &client_len);
                    if (client_fd != -1)
                    {
                        fcntl(client_fd, F_SETFL, O_NONBLOCK);
                        // Client *data_pol = new Client;

                        // data_pol->get_pollfd().events = POLL_IN;
                        // data_pol->get_pollfd().fd = client_fd;
                        // data_pol->get_pollfd().revents = 0;
                        // data_vec.push_back(data_pol);

                            pollfd data_fds;

                            data_fds.fd = client_fd;
                            data_fds.events = POLL_IN;
                            data_fds.revents = 0;
                            vec_data_fds.push_back(data_fds);

                            client.push_back(Client(client_fd));
                            if((i - 1) > -1)
                                std::cout << client[i - 1].get_fd() << std::endl;
                    }
                }
                else
                {
                    char buffer[1024];
                    int bytes = recv(vec_data_fds[i].fd, buffer, 1024, 0);
                        std::string tmp = av[2];
                    if (bytes > 0)
                    {
                        // std::cout << "-->" << buffer << std::endl;
                        std::string str(buffer, bytes);

                        
                        // std::cout << str << std::endl;
                        // if()
                        // {
                            // std::cout << "New client connected\n";
                        // }
                        // if((i - 1) > -1)
                        //     parseCommand(client[i - 1], str, tmp);

                        // Client
                        if((i - 1) > -1)
                        {
                            client[i - 1].get_buffer() += str;
                            // std::cout << "her" << client[i - 1].get_buffer() << std::endl;
                            size_t pos;
                            while ((pos = client[i - 1].get_buffer().find("\r\n")) != std::string::npos)
                            {
                                std::string command = client[i - 1].get_buffer().substr(0, pos);
                                // std::cout << command << std::endl;
                                client[i - 1].get_buffer().erase(0, pos + 2);

                                parseCommand(client[i - 1], command, tmp);
                            }
                        }
                    }
                }
            }
        }
    }
}


