/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingfile.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:21:48 by omaezzem          #+#    #+#             */
/*   Updated: 2026/03/08 02:38:12 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

void ParseSide::addusernicktoclient(std::vector<Client *> &clients)
{
    size_t i = 0;

    while (i < nick.size() && i < clients.size()){
        clients[i]->set_name(nick[i], user[i]);
        i++;
    }
}

