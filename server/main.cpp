/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 00:43:39 by omaezzem          #+#    #+#             */
/*   Updated: 2026/03/10 22:28:36 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "../ParseSide/ParseSide.hpp"

bool g_running = true;

void handleSignal(int signal)
{
    std::cout << "\nSignal received: " << signal << std::endl;
    std::cout << "Server shutting down safely...\n";
    g_running = false;
    // exit(0);
}

std::string ft_toupper(std::string &var)
{
    for (size_t i = 0; i < var.size(); i++)
    {
        var[i] = std::toupper(var[i]);
    }
    return var;
}

void parseCommand(Client &client, std::string &line, std::string &pass_word, std::vector<Client *> &array, std::vector<Channel> &channels, ParseSide &parse)
{
    
    
    std::vector<std::string> command = ft_split(line, 0);
    if(command.empty())
        return;
    
    std::string cmd = ft_toupper(command[0]);
    for (size_t i = 0;  i < cmd.size(); i++)
    {
        line[i] = cmd[i];
    }
    if (cmd == "PASS")
    {
        if(cmd == "PASS" && !client.set_pass())
            parse.parse_PASS(client, line, pass_word);
        else if(client.set_pass())
            std::cout << "CLIENT[" << client.get_fd() << "] : " << "THE PASSWORD HAS BEEN ENTERED\n";
    }
    else if (cmd == "NICK")
    {
        if (!client.set_pass())
            std::cout << "CLIENT[" << client.get_fd() << "] : " << "YOU NEED TO ENTER THE PASSWORD FIRST\n";
        else
            parse.parse_NICK(array, client, line);
    }
    else if (cmd == "USER")
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
        else if (cmd == "JOIN")
        {
            parse.parse_Join(line, channels, client);
        }
        else if (cmd == "PRIVMSG")
        {
            parse.parse_PRIVMSG(line,channels, client, array);
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
            parse.Parse_topic(client.getnickname(),line, channels, array);
        }
        else if (cmd == "INVITE")
        {
            parse.Parse_invite(client , line, channels, array);
        }
        else if (cmd == "QUIT")
        {
            //QUIT
            std::cout << "ba9i makayn walo\n";
            // QUIT
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
        // parse.user.push_back(client.get_username());
        // parse.nick.push_back(client.get_name());
        std::cout << "CLIENT["<< client.get_fd() << "] : REGISTERED SUCCESSFULLY\n";
    }
}

void f()
{
    system("leaks ircserv");
    system("lsof -c ircserv");
}

int main(int ac, char *av[])
{
    if(ac != 3)
    {
        std::cout << "Usage: " << av[0] << " <port> <password>" << std::endl;
        return (1);
    }
    atexit(f);
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
    std::vector<Client *> client;
    ParseSide parse;
    std::vector<pollfd> vec_data_fds;
    pollfd data_fds;

    data_fds.fd = fd_server;
    data_fds.events = POLL_IN;
    data_fds.revents = 0;
    vec_data_fds.push_back(data_fds);
    std::vector<Channel> channels;
    while (true)
    {
        signal(SIGINT, handleSignal);
        if(!g_running)
        {
            std::cout << "Closing server...\n";
            for(int i = 0; i < (int)vec_data_fds.size(); i++)
            {
                close(vec_data_fds[i].fd);
            }
            for (size_t i = 0; i < client.size() ; i++)
            {
                delete client[i];
            }
            // close(fd_server);
            return 0;
        }
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
                            Client *cls = new Client(client_fd);
                            client.push_back(cls);
                            if((i - 1) > -1)
                                std::cout << client[i - 1]->get_fd() << std::endl;
                    }
                }
                else
                {
                    char buffer[1024];
                    int bytes = recv(vec_data_fds[i].fd, buffer, 25, 0);
                    std::string tmp = av[2];
                    if (bytes > 0)
                    {
                        std::string str(buffer, bytes);

                        if((i - 1) > -1)
                        {
                            client[i - 1]->get_buffer() += str;
                            size_t pos;
                            while ((pos = client[i - 1]->get_buffer().find("\r\n")) != std::string::npos)
                            {
                                std::string command = client[i - 1]->get_buffer().substr(0, pos);
                                client[i - 1]->get_buffer().erase(0, pos + 2);

                                parseCommand(*client[i - 1], command, tmp, client, channels, parse);
                            }
                        }
                    }
                    if(bytes <= 0)
                    {
                        if(client[i - 1]->set_auth())
                            std::cout << "CLIENT[" <<  vec_data_fds[i].fd << "] : DISCONNECTED\n" ;
                        // std::cout << "CLIENT[" << client[i - 1].get_name() << "] : OUT\n";

                        parse.parse_Join("JOIN 0", channels, *client[i-1]);
                        close(vec_data_fds[i].fd);
                        // vec_data_fds.erase(vec_data_fds.begin() + i);
                        // client.erase(client.begin() + (i - 1));
                        // parse.nick.erase(parse.nick.begin() + (i - 1));
                        // parse.user.erase(parse.user.begin() + (i - 1));
                        // parse.rname.erase(parse.rname.begin() + (i - 1));
                        if(vec_data_fds.size() >= 1)
                        {
                            delete client[i-1];
                            vec_data_fds.erase(vec_data_fds.begin() + i);
                        }
                        if(client.size() >= 1)
                        {
                            client.erase(client.begin() + (i - 1));
                        }
                        if(parse.nick.size() >= 1)
                        {
                            parse.nick.erase(parse.nick.begin() + (i - 1));
                            parse.user.erase(parse.user.begin() + (i - 1));
                            parse.rname.erase(parse.rname.begin() + (i - 1));
                        }
                        i--;
                    }
                }
            }
        }
    }
}


