/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 23:19:25 by omaezzem          #+#    #+#             */
/*   Updated: 2026/03/01 21:39:35 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

void    ParseSide::Parse_mode(std::string &cmdarg, std::vector<Channel> &channels)
{
    std::vector<std::string> line = ft_split(cmdarg, 0);
    if (line.size() < 3)
    {
        ERR_NEEDMOREPARAMS();
        return ;
    }
    std::string cmd = line[0];
    if (cmd != "MODE")
    {
        ERR_CMDDISMATCH("MODE");
        return ;
    }
    std::string ch = line[1];
    if (ch[0] != '#' && ch[0] != '&'){
        ERR_BADCHANMASK(ch);
        return ;
    }
    Channel target;
    bool    is_in = false;
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (channels[i].getname() == ch)
        {
            target = channels[i];
            is_in = true;
            break;
        }
    }
    if (!is_in)
    {
        ERR_NOSUCHCHANNEL(ch);
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
    std::map <std::string , std::string> modes;
    std::vector<std::string> split_params = ft_split(mode_param, 0);
    size_t j = 0;
    for (size_t i = 0; i < mode.length(); i++)
    {
        smode = "";
        if (mode[i] == '+' || mode[i] == '-'){
            current_sign = mode[i];
            continue;
        }
        if (current_sign == '\0')
            continue;
        if (current_sign == '+' || current_sign == '-')
        {
            if (mode[i] == 'i' || mode[i] == 't' || (mode[i] == 'k' && current_sign == '-')
                || (mode[i] == 'l' && current_sign == '-')){
                smode += current_sign;
                smode += mode[i];
                modes[smode] = "";
                target.signmodes.push_back(smode);
            }
            
            while(j < split_params.size())
            {
                if (mode[i] == 'k'){
                    if (current_sign == '+'){
                        if (line.size() < 3){
                            ERR_NEEDMOREPARAMS();
                            break;
                        }
                        else {
                            smode += current_sign;
                            smode += mode[i];
                            modes[smode] = split_params[j];
                            target.signmodes.push_back(smode);
                            j++;
                            break;
                        }
                    }
                }
                else if (mode[i] == 'o'){
                    if (current_sign == '+' || current_sign == '-'){
                        if (line.size() < 3){
                            ERR_NEEDMOREPARAMS();
                            break;
                        }
                        else {
                            smode += current_sign;
                            smode += mode[i];
                            modes[smode] = split_params[j];
                            target.signmodes.push_back(smode);
                            j++;
                            break;
                        }
                    }
                }
                else if (mode[i] == 'l'){
                    if (current_sign == '+'){
                        if (line.size() < 3){
                            ERR_NEEDMOREPARAMS();
                            break;
                        }
                        else {
                            smode += current_sign;
                            smode += mode[i];
                            modes[smode] = split_params[j];
                            target.signmodes.push_back(smode);
                            j++;
                            break;
                        }
                    }
                }
                else 
                    break;
            }
            
        }   
    }
    
    for (size_t i = 0; i < target.signmodes.size(); i++)
    {
        std::cout << target.signmodes[i] <<  " !!!  ";
    }
    std::cout << std::endl;
    
    std::cout << "here azbi "<< std::endl;
    std::map<std::string , std::string>::iterator mp;
    for (mp = modes.begin(); mp != modes.end(); ++mp)
    {
        std::cout << " ~~~~~~ "<< mp->first << "   " << mp->second << std::endl;
    }
    

}
