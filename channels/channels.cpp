/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 21:45:42 by slimane           #+#    #+#             */
/*   Updated: 2026/02/22 03:55:34 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

Channel::Channel(Client &cls, std::string & channel_name) : curr_member(1) , lim_membrs(-1), password(""), topic(""), invite_only(false), def_lim_members(200)
{
    name = channel_name;
    members.push_back(&cls);
    ops.push_back(&cls);
    ft_send(cls, "WELCOME YOU are now a  member in this channel don't forget to  set the setting for this channel using the command help to see all command\n");
};

void Channel::add_member(Client &cls)
{
    size_t i = 0;
    int check = 0;
    for (i = 0; i < members.size(); i++)
    {
        if (cls.get_name() == members[i]->get_name())
        {
            ft_send(cls , "you already member in this channel \n");
            return ; 
        }
    }
    
    curr_member++;
    if (curr_member > lim_membrs || def_lim_members < curr_member)
    {
        send(cls.get_Clientsocket(), "the channel is full there's no place for you go search another channel\n", 73, 0);
        return ; 
    }
    members.push_back(&cls);
    std::string str =  "Welcome " + cls.get_name() + " to the channel " + name ;
    ft_send(cls, str.c_str()); 
}

void Channel::ft_mode(Client &cls , std::string &md)
{
    
}

void Channel::remove_member(Client &cls, Client &rmvr)
{
    size_t i;
    int check = 0;
    for (i = 0;  i < ops.size(); i++)
    {
        if (rmvr.get_name() == ops[i]->get_name())
        {
            check = 1;
            break;
        }
    }
    if (check == 0)
    {
        std::string str = rmvr.get_name() + " you are not an operator  to KICK users From their channels\n";
        ft_send(rmvr, str.c_str());
        return ;
    }
    for (i = 0; i < members.size(); i++)
    {
        if (cls.get_name() == members[i]->get_name())
            break;
    }
    members.erase(members.begin() + i);
    std::string str = "Hey " + cls.get_name() +  " you were removed form this channel " + name;
    ft_send(cls, str.c_str());
}

void Channel::remove_operator(Client &cls, Client &rmvr)
{
    size_t i;
    int check = 0;
    for (i = 0;  i < ops.size(); i++)
    {
        if (rmvr.get_name() == ops[i]->get_name())
        {
            check = 1;
            break;
        }
    }
    if (check == 0)
    {
        std::string str = rmvr.get_name() + " you are not an operator  to choose who will be an operator or not \n";
        ft_send(rmvr, str.c_str());
        return ;
    }
    for (i = 0; i < ops.size(); i++)
    {
        if (cls.get_name() == ops[i]->get_name())
            break;
    }
    ops.erase(ops.begin() + i);
    std::string str = "Hey " + cls.get_name() +  " you are not longger an operator  for this channel " + name;
    ft_send(cls, str.c_str());
}

void Channel::ft_topic(Client &cls, std::string &topic)
{
    this->topic = topic;
    std::string str = "the Client " + cls.get_name() + " set a topic for this channel " + name ;
    ft_broadcast_all(str);
}
void Channel::ft_topic(Client &cls)
{
    ft_send(cls, topic.c_str());
}

void Channel::ft_broadcast(Client &sender, std::string &msg)
{
    size_t i = 0;
    for (i = 0; i < count; i++)
    {
        /* code */
    }
    
}


void Channel::add_member_to_operator(Client &cls, Client &oprtr)
{
    int check = 0;
    for (size_t i = 0; i < ops.size(); i++)
    {
        if (oprtr.get_name() == ops[i]->get_name())
        {
            check = 1;
            break;
        }
    }
    if (check == 1)
    {
        ops.push_back(&cls);
        std::string str = oprtr.get_name() + " sets " + cls.get_name() + " as an operator in this  channel " + name;
        ft_broadcast_all(str);
    }
    else
        ft_send(oprtr, "you are not an operator to set people you want as operators too\n");
}

Channel::~Channel()
{};