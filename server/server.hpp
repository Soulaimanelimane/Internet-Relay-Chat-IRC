/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 13:56:14 by bbenaali          #+#    #+#             */
/*   Updated: 2026/02/22 17:03:52 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <poll.h>
#include <fcntl.h>

#include "clients/client.hpp"

struct sockaddr_in_serv
{
    int sev_trans;
    int sev_addrs;
    int sev_port;
};

// struct pollfd
// {
//     int   fd;
//     int events;
//     int revents;
// };

#endif



// #include <iostream>
// #include <cstring>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <sys/socket.h>
// #include <netinet/in.h>

// int main()
// {
//     // 1️⃣ Create socket
//     int server_fd = socket(AF_INET, SOCK_STREAM, 0);
//     if (server_fd == -1)
//     {
//         std::cerr << "Socket failed\n";
//         return 1;
//     }

//     // 2️⃣ Allow reuse
//     int opt = 1;
//     setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

//     // 3️⃣ Setup address
//     sockaddr_in address;
//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(8080);

//     // 4️⃣ Bind
//     if (bind(server_fd, (sockaddr*)&address, sizeof(address)) == -1)
//     {
//         std::cerr << "Bind failed\n";
//         return 1;
//     }

//     // 5️⃣ Listen
//     if (listen(server_fd, 10) == -1)
//     {
//         std::cerr << "Listen failed\n";
//         return 1;
//     }

//     std::cout << "Server running on port 8080...\n";

//     // 🔁 Infinite loop
//     while (true)
//     {
//         sockaddr_in client_addr;
//         socklen_t client_len = sizeof(client_addr);

//         // 6️⃣ Accept client
//         int client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);
//         if (client_fd == -1)
//         {
//             std::cerr << "Accept failed\n";
//             continue;
//         }

//         std::cout << "Client connected!\n";

//         // 🔁 Loop to communicate with this client
//         while (true)
//         {
//             char buffer[1024];
//             memset(buffer, 0, sizeof(buffer));

//             int bytes = recv(client_fd, buffer, sizeof(buffer), 0);

//             if (bytes <= 0)
//             {
//                 std::cout << "Client disconnected\n";
//                 break;
//             }

//             std::cout << "Client: " << buffer;

//             // Echo back
//             send(client_fd, buffer, bytes, 0);
//         }

//         close(client_fd);
//     }

//     close(server_fd);
//     return 0;
// }