/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 13:56:14 by bbenaali          #+#    #+#             */
/*   Updated: 2026/02/27 00:25:07 by omaezzem         ###   ########.fr       */
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

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>

#include <sstream>

class ParseSide;

#include "../ParseSide/ParseSide.hpp"
#include "../clients/client.hpp"

std::string ft_toupper(std::string &var);

#endif
