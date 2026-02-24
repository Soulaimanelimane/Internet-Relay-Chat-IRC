/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 21:10:45 by bbenaali          #+#    #+#             */
/*   Updated: 2026/02/24 03:13:10 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"



void parseCommand(Client *client, std::string line)
{
    std::istringstream iss(line);
    std::string command;
    iss >> command;

    if (command == "PASS")
    {
        std::string password;
        iss >> password;

        if (password == "brahim")
            client->set_pass() = true;
        else
            send(client->get_pollfd().fd, "ERROR: WRONG PASSWORD\n", 22, 0);
    }
    else if (command == "NICK")
    {
        std::string nick;
        iss >> nick;

        if (!nick.empty())
        {
            client->set_nick() = true;
        }
    }
    else if (command == "USER")
    {
        std::string username;
        iss >> username;

        if (!username.empty())
            client->set_user() = true;
    }

    if (client->set_pass() && client->set_nick() && client->set_user())
    {
        std::cout << "Client registered successfully\n";
    }
}


int main(int ac, char *av[])
{
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
    std::vector<Client *> data_vec;

    Client *data_pol = new Client;

    data_pol->get_pollfd().events = POLL_IN;
    data_pol->get_pollfd().fd = fd_server;
    data_pol->get_pollfd().revents = 0;
    data_vec.push_back(data_pol);
    while (true)
    {
        poll(&data_vec[0]->get_pollfd(), data_vec.size(), -1);
        for(int i = 0; i < data_vec.size(); i++)
        {
            if(data_vec[i]->get_pollfd().revents & POLL_IN)
            {
                if(data_vec[i]->get_pollfd().fd == fd_server)
                {
                    sockaddr_in client_addr;
                    socklen_t client_len = sizeof(client_addr);

                    int client_fd = accept(fd_server, (sockaddr*)&client_addr, &client_len);
                    if (client_fd != -1)
                    {
                        std::cout << "her\n";
                        fcntl(client_fd, F_SETFL, O_NONBLOCK);
                        Client *data_pol = new Client;
                        
                        data_pol->get_pollfd().events = POLL_IN;
                        data_pol->get_pollfd().fd = fd_server;
                        data_pol->get_pollfd().revents = 0;
                        data_vec.push_back(data_pol);
                    }
                }
                else
                {
                    char buffer[1024];
                    int bytes = recv(data_vec[i]->get_pollfd().fd, buffer, 1024, 0);
                    if (bytes > 0)
                    {
                        std::string str(buffer, bytes);
                        
                        // if()
                        // {
                            std::cout << "New client connected\n";
                        // }
                        parseCommand(data_vec[i], str);
                    }
                }
            }
        }
    }
}


