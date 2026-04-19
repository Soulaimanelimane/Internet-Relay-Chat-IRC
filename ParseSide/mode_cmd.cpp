/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 23:19:25 by omaezzem          #+#    #+#             */
/*   Updated: 2026/04/17 17:57:11 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"


void    ParseSide::Parse_mode(std::string &cmdarg, std::vector<Channel> &channels, Client &cls, std::vector<Client *> &clients)
{
    std::vector<std::string> line = ft_split(cmdarg, 0);
    if (line.size() < 3)
    {
        ERR_NEEDMOREPARAMS("MODE", cls);
        return ;
    }
    std::string cmd = line[0];
    if (cmd != "MODE")
    {
        ERR_CMDDISMATCH("MODE\r\n", cls);
        return ;
    }
    std::string ch = line[1];
    if (ch[0] != '#' && ch[0] != '&'){
        ERR_BADCHANMASK(ch, cls);
        return ;
    }
    Channel *target = NULL;
    bool    is_in = false;
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (channels[i].getname() == ch)
        {
            target = &channels[i];
            is_in = true;
            break;
        }
    }
    if (!is_in)
    {
        ERR_NOSUCHCHANNEL(ch, cls);
        return;
    }

    std::string mode = line[2];
    char        current_sign = '\0';
    std::string smode = "";
    std::string mode_param = "";

    if (line.size() >= 4)
    {
        mode_param = line[3];
        for (size_t i = 4; i < line.size(); i++){
            mode_param += " ";
            mode_param += line[i];
        }
    }
    std::multimap <std::string , std::string> modes;
    std::vector<std::string> split_params = ft_split(mode_param, 0);
    size_t j = 0;
    for (size_t i = 0; i < mode.length(); i++)
    {
        smode = "";
        if (mode[i] == '+' || mode[i] == '-'){
            current_sign = mode[i];
            i++;
        }
        if (current_sign == '\0')
            continue;
        if (current_sign == '+' || current_sign == '-')
        {
            if (mode[i] == 'i' || mode[i] == 't' || (mode[i] == 'k' && current_sign == '-')
                || (mode[i] == 'l' && current_sign == '-')){
                smode += current_sign;
                smode += mode[i];
                modes.insert(std::make_pair(smode , ""));
            }
            
            while(j < split_params.size())
            {
                if (mode[i] == 'k'){
                    if (current_sign == '+'){
                        if (line.size() < 3){
                            ERR_NEEDMOREPARAMS("MODE", cls);
                            break;
                        }
                        else {
                            smode += current_sign;
                            smode += mode[i];
                            modes.insert(std::make_pair(smode , split_params[j]));
                            j++;
                            break;
                        }
                    }
                }
                else if (mode[i] == 'o'){
                    if (current_sign == '+' || current_sign == '-'){
                        if (line.size() < 3){
                            ERR_NEEDMOREPARAMS("MODE", cls);
                            break;
                        }
                        else {
                            smode += current_sign;
                            smode += mode[i];
                            modes.insert(std::make_pair(smode , split_params[j]));
                            j++;
                            break;
                        }
                    }
                }
                else if (mode[i] == 'l'){
                    if (current_sign == '+'){
                        if (line.size() < 3){
                            ERR_NEEDMOREPARAMS("MODE", cls);
                            break;
                        }
                        else {
                            smode += current_sign;
                            smode += mode[i];
                            modes.insert(std::make_pair(smode , split_params[j]));
                            j++;
                            break;
                        }
                    }
                }
                else 
                    break;
            }
            
        }
        else
            break; 
    }
    if (modes.empty())
    {
        std::string str = " ERROR :!~Server_IRC 324 " + cls.get_name() + " " + target->get_name() + " +nt\n";
        str += "ERROR :!~Server_IRC 329" + cls.get_name() +" "+ target->get_name() + "\r\n";
        ft_send(cls, str.c_str());
        return ; 
    }
    std::map<std::string , std::string>::iterator mp;
    for (mp = modes.begin(); mp != modes.end(); mp++)
    {
        target->ft_mode(cls, mp->first, mp->second , clients);
    }

}
