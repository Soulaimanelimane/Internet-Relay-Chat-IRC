/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 21:45:42 by slimane           #+#    #+#             */
/*   Updated: 2026/04/27 15:16:37 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

Channel::Channel(Client &cls, std::string &channel_name) : name(channel_name), topic(""), setter_topic(""), invite_only(false), tp_rest(true), nd_pss(false), password(""), lim_membrs(-1), def_lim_members(200)
{
    members.push_back(&cls);
    ops.push_back(&cls);
    ft_list_members(cls);
};

std::string &Channel::get_name()
{
    return (name);
}

void Channel::set_name(std::string _name){name = _name;}

void Channel::set_password(std::string &key)
{
    nd_pss = true;
    password = key;
}

std::string &Channel::get_pass()
{
    return (password);
}

bool Channel::get_permession()
{
    return (nd_pss);
}

int Channel::check_is_in(Client &rmvr, std::vector<Client *> &list)
{
    size_t i;
    for (i = 0; i < list.size(); i++)
    {
        if (rmvr.get_name() == list[i]->get_name())
            return 1;
    }
    return 0;
}
size_t Channel::size()
{
    return members.size();
}

void Channel::List_members(Client &cls)
{
    std::string str  = "";
    for (size_t i = 0; i < ops.size(); i++)
    {
        str += "@" + ops[i]->get_name() + " ";
    }
    for (size_t i = 0; i < members.size(); i++)
    {
        if (check_is_in(*members[i], ops) == 0)
            str += members[i]->get_name() + " ";
    }
    str += "\r\n";
    ft_send(cls, str.c_str());
}

void Channel::ft_list_members(Client &cls)
{
    std::string str = ":Server_irc 353 " + cls.get_name() + " = " + name + " :";
    ft_send(cls, str.c_str());
    str = "";
    for (size_t i = 0; i < ops.size(); i++)
    {
        str += "@" + ops[i]->get_name() + " ";
    }
    for (size_t i = 0; i < members.size(); i++)
    {
        if (check_is_in(*members[i], ops) == 0)
            str += members[i]->get_name() + " ";
    }
    str += "\r\n:Server_irc 366 " + cls.get_name() + " " + name + " ;End of Names list\r\n";
    ft_send(cls, str.c_str());
}

void Channel::add_member(Client &cls)
{
    std::string str;
    int check = 0;

    if (invite_only == true)
    {
        check = check_is_in(cls, invited);
        if (check == 0)
        {
            str = "473 " + cls.get_name() + "  " + name + " :Cannot join channel (+i)\r\n";
            ft_send(cls, str.c_str());
            return;
        }
        else
        {
            for (size_t i = 0; i < invited.size(); i++)
            {
                if (invited[i]->get_name() == cls.get_name())
                {
                    invited.erase(invited.begin() + i);
                    break;
                }
            }
        }
    }

    check = check_is_in(cls, members);
    if (check == 1)
        return;
    long long member_size = members.size();
    if (member_size == lim_membrs || def_lim_members < members.size() + 1)
    {
        str = ":!~Server_irc 471 " + cls.get_name() + " "+ name + " :Cannot join channel (+l)\r\n";
        ft_send(cls, str.c_str());
        return;
    }
    if (!topic.empty())
    {
        str = "332 " + cls.get_name() + " " + name + " " + topic + "\r\n";
        str += "333 " + cls.get_name() + " " + name + " " + setter_topic + "\r\n";
        ft_send(cls, str.c_str());
    }
    members.push_back(&cls);
    ft_list_members(cls);
    str = ":" + cls.get_name() + "!~Server_irc JOIN " + name + "\r\n";
    ft_broadcast(cls, str);
}

int Channel::ft_atoi(std::string str)
{
    size_t res = 0;
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

int check_is_need_args(std::string md)
{
    if ((md == "+i" || md == "-i" || md == "-l" || md == "-k" || md == "+t" || md == "-t"))
        return 1;
    else if ((md == "+o" || md == "-o" || md == "+l" || md == "+k"))
        return 2;
    return 0;
}

int Channel::ft_mode(Client &cls, std::string md, std::string args, std::vector<Client *> &clients)
{
    int check = check_is_need_args(md);
    std::string str;
    if (check == 0)
    {
        str = "472 " + cls.get_name() + " " + md + " :is an unknown mode character to me\r\n";
        ft_send(cls, str.c_str());
        return 1;
    }
    else if (check == 2 && args.empty())
    {
        str = "461 " + cls.get_name() + " " + name + " MODE Not enough parameters\r\n";
        ft_send(cls, str.c_str());
        return 1;
    }
    check = check_is_in(cls, ops);
    if (check == 0)
    {
        str = "482 " + cls.get_name() + "  " + name + " :You're not a channel operator\r\n";
        ft_send(cls, str.c_str());
        return 1;
    }
    check = 0;
    if (md == "+i")
        return (invite_only = true, 0);
    else if (md == "-i")
        return (invite_only = false, 0);
    else if (md == "+t")
        return (tp_rest = true, 0);
    else if (md == "-t")
        return (tp_rest = false, 0);
    else if (md == "+k")
    {
        this->set_password(args);
        nd_pss = true;
        return 0;
    }
    else if (md == "-k")
    {
        str = "";
        this->set_password(str);
        nd_pss = false;
        return 0;
    }
    else if (md == "+l")
    {
        size_t i = 0;
        if (args[i] != '+' && !isdigit(args[i]))
            return 1;
        if (args[i] == '+')
            i++;
        while(i < args.size())
        {
            if (!std::isdigit(args[i]))
                return 1;
            i++;
        }
        long long tmp = ft_atoi(args);
        if (tmp <= 0)
        {
            str = "696 " + cls.get_name() + " " + name + " :Invalid mode parameter\r\n";
            ft_send(cls, str.c_str());
            return 1;
        }
        lim_membrs = tmp;
        return 0;
    }
    else if (md == "-l")
    {
        lim_membrs = -1;
        return 0;
    }
    else if (md == "+o")
    {
        check = 0;
        size_t i;
        for (i = 0; i < clients.size(); i++)
        {
            if (clients[i]->get_name() == args)
            {
                check = 1;
                break;
            }
        }
        if (check == 0)
        {
            str = "401 " + cls.get_name() + " " + args + " :No such nick\r\n";
            ft_send(cls, str.c_str());
            return 1;
        }
        check = check_is_in(*clients[i], members);
        if (check == 0)
        {
            str = "441 " + cls.get_name() + " " + name + " :They aren't on that channel\r\n";
            ft_send(cls, str.c_str());
            return 1;
        }
        check = check_is_in(*clients[i], ops);
        if (check == 1)
            return 0;
        ops.push_back(clients[i]);
        return 0;
    }
    else if (md == "-o")
    {
        check = 0;
        size_t i;
        for (i = 0; i < clients.size(); i++)
        {
            if (clients[i]->get_name() == args)
            {
                check = 1;
                break;
            }
        }
        if (check == 0)
        {
            str = "401 " + cls.get_name() + " " + args + " :No such nick\r\n";
            ft_send(cls, str.c_str());
            return 1;
        }

        check = check_is_in(*clients[i], members);
        if (check == 0)
        {
            str = "441 " + cls.get_name() + " " + name + " :They aren't on that channel\r\n";
            ft_send(cls, str.c_str());
            return 1;
        }

        check = check_is_in(*clients[i], ops);
        if (check == 0)
            return 0;
        for (i = 0; i < ops.size(); i++)
        {
            if (args == ops[i]->get_name())
                break;
        }
        ops.erase(ops.begin() + i);
        return 0;
    }
    else
        return 1;
    return 1;
}

void Channel::remove_itself(Client &cls)
{
    int check = check_is_in(cls, members);
    if (check == 0)
        return;
    size_t i;
    for (i = 0; i < members.size(); i++)
    {
        if (cls.get_name() == members[i]->get_name())
            break;
    }
    std::string str = ":" + cls.get_name() + "!Server_irc PART " + name + "\r\n";
    ft_broadcast_all(str);
    members.erase(members.begin() + i);
    check = check_is_in(cls, ops);
    if (check == 1)
    {
        remove_operator(cls);
        if (ops.size() == 0)
        {
            if (members.size() > 0)
                ops.push_back(members[0]);
        }
    }
}

void Channel::remove_member(Client &cls, Client &rmvr)
{
    size_t i;
    std::string str;
    int check = check_is_in(rmvr, members);
    if (check == 0)
    {
        str = "482 " + rmvr.get_name() + " " + name + " :You don't have enough channel privileges\r\n";
        ft_send(rmvr, str.c_str());
        return;
    }
    check = check_is_in(rmvr, ops);
    if (check == 0)
    {
        str = "482 " + rmvr.get_name() + " " + name + " :You don't have enough channel privileges\r\n";
        ft_send(rmvr, str.c_str());
        return;
    }
    check = check_is_in(cls, members);
    if (check == 0)
    {
        str = "482 " + rmvr.get_name() + " " + name + " :You don't have enough channel privileges\r\n";
        ft_send(rmvr, str.c_str());
        return;
    }

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
        return;
    }
    check = check_is_in(cls, ops);
    if (check == 1)
    {
        remove_operator(cls);
        if (ops.size() == 0)
        {
            if (members.size() > 0)
                ops.push_back(members[0]);
        }
    }
    str = ":" + rmvr.get_name() + "!~Server_IRC KICK " + name + " " + cls.get_name() + " " + rmvr.get_name() + "\r\n";
    ft_send(cls, str.c_str());
    ft_send(rmvr, str.c_str());
}

void Channel::remove_operator(Client &cls)
{
    size_t i;
    for (i = 0; i < ops.size(); i++)
    {
        if (cls.get_name() == ops[i]->get_name())
            break;
    }
    ops.erase(ops.begin() + i);
}

void Channel::ft_topic(Client &cls, std::string &topic)
{
    int check = 1;
    if (tp_rest == true)
        check = check_is_in(cls, ops);
    if (tp_rest == true &&  check == 0)
    {
        std::string str = "482 " + cls.get_name() + " " + name + " :You're not a channel operator\r\n";
        ft_send(cls, str.c_str());
        return;
    }
    this->topic = topic;
    this->setter_topic = cls.get_name();
    std::string str = ":" + cls.get_name() + "!~Sever_irc TOPIC " + name + " :" + this->topic + "\r\n";
    ft_broadcast_all(str);
}

void Channel::ft_topic(Client &cls)
{
    std::string str;
    if (topic.empty())
    {
        str = ":!~Sever_irc 331 " + cls.get_name() + name  + " :No topic is set\r\n";
        ft_send(cls, str.c_str());
        return ;
    }
    str = "!~Sever_irc 332 " + cls.get_name() + " " + name + " :" + topic + "\r\n";
    ft_send(cls, str.c_str());
    str = "!~Sever_irc 333 " + cls.get_name() + " " + name + " " + setter_topic  + "\r\n";
    ft_send(cls, str.c_str());
}

void Channel::ft_broadcast(Client &sender, std::string &msg)
{
    size_t i;
    int check = check_is_in(sender, members);
    if (check == 0)
    {
        std::string str = ":Server_irc 404 " + sender.get_name() + " " + name + " :Cannot send to channel\r\n";
        ft_send(sender, str.c_str());
        return;
    }
    for (i = 0; i < members.size(); i++)
    {
        if (members[i]->get_name() != sender.get_name())
            ft_send(*members[i], msg.c_str());
    }
}

void Channel::ft_broadcast_all(std::string &msg)
{
    size_t i;
    for (i = 0; i < members.size(); i++)
        ft_send(*members[i], msg.c_str()) ;
}

void Channel::invite_member(Client &host, Client &guest)
{
    int check = 0;
    std::string str;
    check = check_is_in(host, ops);
    if (invite_only == true && check == 0)
    {
        str = "482 " + host.get_name() + "  " + name + " :You're not a channel operator\r\n";
        ft_send(host, str.c_str());
        return;
    }

    this->invited.push_back(&guest);
    str = ":" + host.get_name() + ":!~Server_irc INVITE " + guest.get_name() + " " + name + "\r\n";
    ft_send(guest, str.c_str());
}

void Channel::add_member_to_operator(Client &cls, Client &oprtr)
{

    int check = check_is_in(cls, ops);
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

std::vector<Client *> &Channel::get_ops()
{
    return (ops);
}

std::vector<Client *> &Channel::getmembers()
{
    return members;
}
