/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 01:35:51 by omaezzem          #+#    #+#             */
/*   Updated: 2026/02/22 22:09:14 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ParseSide/ParseSide.hpp"
int main()
{
    std::vector<std::string> users = ft_split("omar,,soulaimane,brahim", ',');
    for (size_t i = 0; i < users.size(); i++)
    {
        std::cout << "-"+users[i]+"-" << std::endl;
    }
    
    // std::vector<Client*> clients;
    // clients[0].nickname = " df";
    // clients[0].username = "dffdf";

    // clients[1].nickname = " df";
    // clients[1].username = "dffdf";
}
