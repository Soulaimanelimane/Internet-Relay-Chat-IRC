/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 21:10:45 by bbenaali          #+#    #+#             */
/*   Updated: 2026/02/21 12:12:12 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>

int main()
{
    int int_error = socket(AF_INET, SOCK_STREAM, 0);
    if(int_error < 0)
    {
        std::cout << "ERROR: OPEN SOCKET" << int_error << std::endl;
        return (1);
    }
}