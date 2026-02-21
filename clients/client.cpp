/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 03:33:50 by slimane           #+#    #+#             */
/*   Updated: 2026/02/21 04:38:56 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

int ft_send(Client &cls , const char *str)
{
    return (send(cls.get_Clientsocket(), str, strlen(str), 0));
}