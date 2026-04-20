/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 13:56:14 by bbenaali          #+#    #+#             */
/*   Updated: 2026/04/20 17:10:19 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>

#include <iostream>
#include <vector>
#include <fcntl.h>
#include <unistd.h>

#include <sstream>

class ParseSide;

#include "../ParseSide/ParseSide.hpp"
#include "../clients/client.hpp"

std::string ft_toupper(std::string &var);
void        ft_handel_bot(Client &client, std::string &line, std::vector<Client *> &array, std::vector<Channel> &channels);

#endif
