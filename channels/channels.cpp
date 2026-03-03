/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 21:45:42 by slimane           #+#    #+#             */
/*   Updated: 2026/03/03 03:47:50 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

Channel::Channel(Client &cls, std::string &channel_name) : name(channel_name) , topic(""), tp_rest(true), password(""), lim_membrs(-1), def_lim_members(200), nd_pss(false)
{
    members.push_back(&cls);
    ops.push_back(&cls);
    ft_send(cls, "WELCOME YOU are now a  member in this channel don't forget to  set the setting for this channel using the command help to see all command\r\r\n");
};


std::string &Channel::get_name()
{
	return (name);
}

void Channel::set_password(std::string &key)
{
    nd_pss = true;
    password = key;
}

std::string &Channel::get_pass()
{
    return (password);
}

bool Channel::get_permession ()
{
    return (nd_pss);
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
    std::string str;
    int check = 0;

    if (invite_only == true)
    {
        check = check_is_in(cls, invited);
        if (check == 0)
        {
            str = "473 " + cls.get_name() + "  " + name +   " :Cannot join channel (+i)";
            ft_send(cls,  str.c_str());
            return ;
        }
    }
    
    for (i = 0; i < members.size(); i++)
    {
        if (cls.get_name() == members[i]->get_name())
        {
            // ft_send(cls, "you already member in this channel \r\n");
            return;
        }
    }
    if (members.size() >= lim_membrs || def_lim_members < members.size())
    {
        send(cls.get_Clientsocket(), "the channel is full there's no place for you go search another channel\r\r\n", 73, 0);
        return;
    }
    if (topic != "") 
        str = "332 " + cls.get_name() + " " + name + " " + topic;
    members.push_back(&cls);
    str = "Welcome " + cls.get_name() + " to the channel " + name + "\r\r\n";
    ft_send(cls, str.c_str());
    str = ":" + cls.get_name() + "!~Server_irc JOIN " + name + "\r\r\n";
    ft_broadcast(cls, str);
}


int Channel::ft_atoi(std::string str)
{
    int res  = 0;
    int i = 0;
    while (str[i])
    {
        res = (res * 10) + (str[i] - '0');
        if (res > def_lim_members)
            return (-1);
        i++;
    }
    return res;
}

void Channel::ft_mode(Client &cls, std::string md , std::string args, std::vector<Client> &clients)
{
    if (args.empty() || md.empty()  || (md[0] != '+' && md[0] != '-'))
    {
        std::cout << "error in the commands check it properly " << std::endl;
        return ;
    }
    std::string  str ;
    int check = check_is_in(cls, ops);
    if (check == 0)
    {
        str = "482 " + cls.get_name() + "  " + name + " :You're not a channel operator\n\t";
        ft_send(cls, str.c_str());
        return ;
    }
    check = 0;
    if (md == "+i")
        invite_only =  true ;
    else if (md == "-i")
        invite_only =  false;
    else if (md == "+t")
        tp_rest = true;
    else if (md == "-t")
        tp_rest = false;
    else if (md == "+k")
    {
        this->set_password(args);
        nd_pss = true;
    }
    else if (md == "-k")
    {
        str = "";
        this->set_password(str);
        nd_pss = false;   
    }
    else if (md == "+l")
    {
        if (args.empty())
            return ;
        for (size_t i = 0; i < args.size(); i++)
        {
            if (!std::isdigit(args[i]))
                return ;
        }
        int tmp = ft_atoi(args);
        if (tmp <= 0)
            return ; // msg error 
        lim_membrs = tmp;
        str = ":"+ cls.get_name() +"!~Server_irc MODE "  + name + " +l " + args;
        ft_broadcast_all(str);
    }
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
	std::string str = ":"+cls.get_name() +  "!PART " +  name + "\r\n";
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
    std::string str;
    int check = check_is_in(rmvr, members);
    if (check == 0)
    {
        // 482 imgoun #aday :You don't have enough channel privileges;
        str = "482 " + rmvr.get_name()+ "  " +name  + " :You don't have enough channel privileges\r\n";
        ft_send(rmvr, str.c_str());
        return;
    }
    check = check_is_in(rmvr, ops);
    if (check == 0)
    {
        str = "482 " + rmvr.get_name()+ name  + " :You don't have enough channel privileges\r\n";
        ft_send(rmvr, str.c_str());
        return;
    }
    
    // check = check_is_in(cls, members);
    // if (check == 0)
    // {
    //     std::string str = cls.get_name() + " is not a member  in this channel \r\n";
    //     ft_send(rmvr, str.c_str());
    //     return;
    // }
    int founded = 0;
    for (i = 0; i < members.size(); i++)
    {
        if (cls.get_name() == members[i]->get_name())
        {
            founded = 1;
            break;
        }
    }
    if (founded == 1)
        members.erase(members.begin() + i);
    else
    {
        ft_send(rmvr, "NOT found in this channel\r\n");
        return ;
    }
    check = check_is_in(cls, ops);
    if (check == 1)
    {
        remove_operator(cls, rmvr);
    }
    str = "Hey " + cls.get_name() + " you were removed form this channel " + name + "\r\n";
    ft_send(cls, str.c_str());
}

void Channel::remove_operator(Client &cls, Client &rmvr)
{
    size_t i;
    // int check = check_is_in(rmvr , ops);
    
    // if (check == 0)
    // {
    //     std::string str = rmvr.get_name() + " you are not an operator  to choose who will be an operator or not \r\n";
    //     ft_send(rmvr, str.c_str());
    //     return;
    // }

    // check = check_is_in(cls, ops);
    // if (check == 0)
    // {
    //     std::string str = cls.get_name() + " is not an operator \r\n";
    //     ft_send(rmvr, str.c_str());
    //     return;
    // }
    for (i = 0; i < ops.size(); i++)
    {
        if (cls.get_name() == ops[i]->get_name())
            break;
    }
    ops.erase(ops.begin() + i);
    // std::string str = "Hey " + cls.get_name() + " you are not longger an operator  for this channel " + name;
    // ft_send(cls, str.c_str());
}

void Channel::ft_topic(Client &cls, std::string &topic)
{
    int check = check_is_in(cls, ops);
    if (check == 0)
    {
        std::string str = "482" + cls.get_name()+ " " + name  + " :You're not a channel operator\r\n";
        ft_send(cls, str.c_str());
        return;
    }
    // if (tp_rest == true)
    // {
    // }
    this->topic = topic;

    //:imgoun!~u@qk3i8byd6tfyg.irc TOPIC #42 :wonderful life
    std::string str = ":" + cls.get_name() + "!~Sever_irc TOPIC " + name + " :" + this->topic;
    ft_broadcast_all(str);
}


void Channel::ft_topic(Client &cls)
{
    int check = check_is_in(cls , members);
    std::string str ;
    if (check == 0)
    {
        str = "422 " +cls.get_name() + " " + name + ":You're not on that channel\r\n";
        ft_send(cls, str.c_str());
        return ; 
    }
    check = check_is_in(cls, ops);
    if (check == 0 && tp_rest == true)
    {
        str = "482 " + cls.get_name() + " " + name + ":You're not a channel operator\r\n";
        ft_send(cls, str.c_str());
        return ;   
    }
    str = "332 " +  cls.get_name() + " " + name +  topic + "\r\n";
    ft_send(cls, topic.c_str());
}

void Channel::ft_broadcast(Client &sender, std::string &msg)
{
    size_t i;
    int check = check_is_in(sender, members);
    if (check == 0)
    {
        std::string str = ":Server_irc 404 " + sender.get_name() + " " + name + " :Cannot send to channel\r\n";
        ft_send(sender, str.c_str());
        return ;
    }
    for (i = 0; i < members.size(); i++)
    {
        if (members[i]->get_name() != sender.get_name())
        {
            if (ft_send(*members[i], msg.c_str()) == -1)
            {
                std::cerr << "the send function failed for some reason we cannot send the message to " << members[i]->get_name() << std::endl;
                write(sender.get_Clientsocket(), "the message didn't send well to some of members\r\n", 50);
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
    // int check = check_is_in(guest, members);
    std::string str;
    // if (check == 1)
    // {
    //     str = "443 "+ host.get_name() + guest.get_name() + name  + " :User is already on that channel";
    //     ft_send(host, str.c_str());
    //     return ;
    // }
    str = ":" + host.get_name() +":!~Server_irc INVITE " + guest.get_name() + name + "\r\n";
    ft_send(guest, str.c_str());
    std::cout << ":!~Server_irc 341 " << host.get_name() << name << std::endl;
    invited.push_back(&guest);
}

void Channel::add_member_to_operator(Client &cls, Client &oprtr)
{
    int  check = check_is_in(cls, ops);
    if (check == 1)
    {
        std::string str = cls.get_name() + " is already an operator \r\n";
        ft_send(cls, str.c_str());
        return;
    }
    check = check_is_in(oprtr, ops);
    if (check == 1)
    {
        ops.push_back(&cls);
        std::string str = oprtr.get_name() + " sets " + cls.get_name() + " as an operator in this  channel " + name + "\r\n";
        ft_broadcast_all(str);
    }
    else
        ft_send(oprtr, "you are not an operator to set people you want as operators too\r\n");
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
