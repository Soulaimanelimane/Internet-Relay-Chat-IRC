/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 21:10:45 by bbenaali          #+#    #+#             */
/*   Updated: 2026/02/26 14:34:32 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "../ParseSide/ParseSide.hpp"

void parseCommand(Client &client, std::string &line, std::string &pass_word, std::vector<Client> &array)
{
    ParseSide parse;
    std::vector<Channel> channels;
    std::vector<std::string> command = ft_split(line, ' ');
    if(command.empty())
        return;
    if (command[0] == "PASS")
    {
        if(command[0] == "PASS" && !client.set_pass())
            parse.parse_PASS(client, line, pass_word);
        else if(client.set_pass())
            std::cout << "CLIENT[" << client.get_fd() << "] : " << "THE PASSWORD HAS BEEN ENTERED\n";
    }
    else if (command[0] == "NICK")
    {
        if (!client.set_pass())
            std::cout << "CLIENT[" << client.get_fd() << "] : " << "YOU NEED TO ENTER THE PASSWORD FIRST\n";
        else
            parse.parse_NICK(client, line);
    }
    else if (command[0] == "USER")
    {
        if (!client.set_pass() || !client.set_nick())
            std::cout << "CLIENT[" << client.get_fd() << "] : " << "YOU NEED TO ENTER THE PASSWORD AND THE NICKNAME FIRST\n";
        else
            parse.parse_USER(client, line);
    }
    else
    {
        if (!client.set_auth())
        {
            std::cout << "CLIENT[" << client.get_fd() << "] : " << "YOU NEED TO AUTHENTICATE THE CLIENT FIRST\n";
        }
        else if (command[0] == "JOIN")
        {
            parse.parse_Join(line, channels, client);
        }
        else if (command[0] == "PRIVMSG")
        {
            // parse.parse_PRIVMSG(line);
        }
        else if (command[0] == "KICK")
        {
            //kick function
            // parse.parse_KICK(line, &channels, array, client);
        }
        else if (command[0] == "MODE")
        {
            //MODE
        }
        else if (command[0] == "TOPIC")
        {
            //TOPIC
        }
        else if (command[0] == "INVITE")
        {
            //invite
        }
        else if (command[0] == "QUIT")
        {
            //QUIT
        }
        else
        {
            std::cout << "CLIENT[" << client.get_fd() << "] : " << "THIS COMMAND NOT VALID\n";
        }
    }

    if (client.set_pass() && client.set_nick() && client.set_user() && !client.get_flag())
    {
        client.set_flag();
        client.set_auth() = true;
        std::cout << "CLIENT["<< client.get_fd() << "] REGISTERED SUCCESSFULLY\n";
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
                        std::string str(buffer, bytes);

                        if((i - 1) > -1)
                        {
                            client[i - 1].get_buffer() += str;
                            size_t pos;
                            while ((pos = client[i - 1].get_buffer().find("\r\n")) != std::string::npos)
                            {
                                std::string command = client[i - 1].get_buffer().substr(0, pos);
                                client[i - 1].get_buffer().erase(0, pos + 2);

                                parseCommand(client[i - 1], command, tmp, client);
                            }
                        }
                    }
                }
            }
        }
    }
}


