/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 21:10:45 by bbenaali          #+#    #+#             */
/*   Updated: 2026/02/22 17:08:58 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

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
    std::vector<pollfd> data_vec;

    pollfd data_poll;

    data_poll.events = POLL_IN;
    data_poll.fd = fd_server;
    data_poll.revents = 0;
    data_vec.push_back(data_poll);
    while (true)
    {
        poll(&data_vec[0], data_vec.size(), -1);
        for(int i = 0; i < data_vec.size(); i++)
        {
            if(data_vec[i].revents & POLL_IN)
            {
                
            }
            if(data_vec[i].fd == fd_server)
            {
                sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);

                int client_fd = accept(fd_server, (sockaddr*)&client_addr, &client_len);

                if (client_fd != -1)
                {
                    fcntl(client_fd, F_SETFL, O_NONBLOCK);

                    pollfd client_poll;
                    client_poll.fd = client_fd;
                    client_poll.events = POLLIN;

                    data_vec.push_back(client_poll);

                    std::cout << "New client connected\n";
                }
            }
        }
    }
}


