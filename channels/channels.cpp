/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 21:45:42 by slimane           #+#    #+#             */
/*   Updated: 2026/02/26 14:57:12 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

Channel::Channel(Client &cls, std::string &channel_name) : topic(""), tp_rest(false), password(""), curr_member(1), lim_membrs(-1), def_lim_members(200)
{
    name = channel_name;
    members.push_back(&cls);
    ops.push_back(&cls);
    ft_send(cls, "WELCOME YOU are now a  member in this channel don't forget to  set the setting for this channel using the command help to see all command\n");
};


std::string &Channel::get_name()
{
	return (name);
}

int Channel::check_is_in(Client &rmvr, std::vector<Client *> list)
{
    (void)list;
    size_t i;
    for (i = 0; i < list.size(); i++)
    {
        if (rmvr.get_name() == list[i]->get_name())
            return 1;
    }
    return 0;
}

void Channel::add_member(Client &cls)
{
    size_t i = 0;
    // int check = 0;
    for (i = 0; i < members.size(); i++)
    {
        if (cls.get_name() == members[i]->get_name())
        {
            // ft_send(cls, "you already member in this channel \n");
            return;
        }
    }

    curr_member++;
    if (curr_member > lim_membrs || def_lim_members < curr_member)
    {
        send(cls.get_Clientsocket(), "the channel is full there's no place for you go search another channel\n", 73, 0);
        return;
    }
    members.push_back(&cls);
    std::string str = "Welcome " + cls.get_name() + " to the channel " + name;
    ft_send(cls, str.c_str());
}

void Channel::ft_mode(Client &cls, std::string &md)
{
}

void Channel::remove_itself(Client &cls)
{
    int check = check_is_in(cls, members);
    if (check == 0)
        return ;
	size_t i ;
    for (i = 0; i < members.size(); i++)
    {
    	if (cls.get_name() == members[i]->get_name())
			break;
    }
	std::string str = ":"+cls.get_name() +  "!PART " +  name;
	ft_broadcast_all(str);
    members.erase(members.begin() + i);
}

void Channel::remove_member(Client &cls, Client &rmvr)
{
    if (cls.get_name() == rmvr.get_name())    
    {
        remove_itself(cls);
        return ;
    }
    size_t i;
    int check = check_is_in(rmvr, ops);
    if (check == 0)
    {
        std::string str = rmvr.get_name() + " you are not an operator  to KICK users From their channels\n";
        ft_send(rmvr, str.c_str());
        return;
    }
    
    check = check_is_in(cls, members);
    if (check == 0)
    {
        std::string str = cls.get_name() + " is not a member  in this channel \n";
        ft_send(rmvr, str.c_str());
        return;
    }

    for (i = 0; i < members.size(); i++)
    {
        if (cls.get_name() == members[i]->get_name())
            break;
    }
    members.erase(members.begin() + i);
    std::string str = "Hey " + cls.get_name() + " you were removed form this channel " + name;
    ft_send(cls, str.c_str());
}

void Channel::remove_operator(Client &cls, Client &rmvr)
{
    size_t i;
    int check = check_is_in(rmvr , ops);
    
    if (check == 0)
    {
        std::string str = rmvr.get_name() + " you are not an operator  to choose who will be an operator or not \n";
        ft_send(rmvr, str.c_str());
        return;
    }

    check = check_is_in(cls, ops);
    if (check == 0)
    {
        std::string str = cls.get_name() + " is not an operator \n";
        ft_send(rmvr, str.c_str());
        return;
    }
    
    for (i = 0; i < ops.size(); i++)
    {
        if (cls.get_name() == ops[i]->get_name())
            break;
    }
    ops.erase(ops.begin() + i);
    std::string str = "Hey " + cls.get_name() + " you are not longger an operator  for this channel " + name;
    ft_send(cls, str.c_str());
}

void Channel::ft_topic(Client &cls, std::string &topic)
{
    if (tp_rest == true)
    {
        int check = check_is_in(cls, ops);
        if (check == 0)
        {
            std::string str = cls.get_name() + " your are not an operator to set or remove the topic\n";
            ft_send(cls, str.c_str());
            return;
        }
    }
    this->topic = topic;
    std::string str = "the Client " + cls.get_name() + " set a topic for this channel " + this->topic;
    ft_broadcast_all(str);
}


void Channel::ft_topic(Client &cls)
{
    ft_send(cls, topic.c_str());
}

void Channel::ft_broadcast(Client &sender, std::string &msg)
{
    size_t i;
    for (i = 0; i < members.size(); i++)
    {
        if (members[i]->get_name() != sender.get_name())
        {
            if (ft_send(*members[i], msg.c_str()) == -1)
            {
                std::cerr << "the send function failed for some reason we cannot send the message to " << members[i]->get_name() << std::endl;
                write(sender.get_Clientsocket(), "the message didn't send well to some of members\n", 50);
                return ;
            }
        }
    }
    
}

void Channel::ft_broadcast_all(std::string &msg)
{
    size_t i;
    for (i = 0; i < members.size(); i++)
    {
        if (ft_send(*members[i], msg.c_str()) == -1)
        {
            std::cerr << "the send function failed for some reason we cannot send the message to " << members[i]->get_name() << std::endl;
        }
    }
}

void Channel::invite_member(Client &host, Client &guest)
{
    (void)host;
    (void)guest;
}

void Channel::add_member_to_operator(Client &cls, Client &oprtr)
{
    int  check = check_is_in(cls, ops);
    if (check == 1)
    {
        std::string str = cls.get_name() + " is already an operator \n";
        ft_send(cls, str.c_str());
        return;
    }
    check = check_is_in(oprtr, ops);
    if (check == 1)
    {
        ops.push_back(&cls);
        std::string str = oprtr.get_name() + " sets " + cls.get_name() + " as an operator in this  channel " + name;
        ft_broadcast_all(str);
    }
    else
        ft_send(oprtr, "you are not an operator to set people you want as operators too\n");
}

std::string Channel::getname()
{
    return name;
}

Channel::~Channel() {};
Channel::Channel() {};

bool Channel::isUserInChannel(const std::string &nickname) const
{
    for (size_t i = 0; i < members.size(); i++)
    {
        if (members[i]->getnickname() == nickname)
            return true;
    }
    return false;
}


std::vector<Client*> &Channel::get_ops()
{
    return (ops);
}

std::vector<Client*> &Channel::getmembers()
{
    return members;
}
