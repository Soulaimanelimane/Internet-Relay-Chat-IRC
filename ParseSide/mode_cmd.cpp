/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 23:19:25 by omaezzem          #+#    #+#             */
/*   Updated: 2026/02/26 15:02:35 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseSide.hpp"

void    ParseSide::Parse_mode(std::string &cmdarg, std::vector<Channel> &channels)
{
    std::vector<std::string> line = ft_split(cmdarg, ' ');
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
    char    current_sign;
    std::string    smode;
    std::string mode_param;
    if (line.size() >= 4)
    {
        mode_param = line[3];
        for (size_t i = 4; i < line.size(); i++){
            mode_param += " ";
            mode_param += line[i];
        }
    }
    std::map <std::string , std::string> modes;
    std::vector<std::string> split_params = ft_split(mode_param, ' ');
    for (size_t i = 0; i < mode.length(); i++)
    {
        if (mode[i] == '+' || mode[i] == '-'){
            current_sign = mode[i];
            i++;
        }
        if (current_sign == '+' || current_sign == '-')
        {
            if (mode[i] == 'i' || mode[i] == 't' || (mode[i] == 'k' && current_sign == '-')
                || (mode[i] == 'l' && current_sign == '-')){
                smode = current_sign + mode[i];
                target.signmodes.push_back(smode);
                modes[smode] = "";
            }
            for (size_t j = 0; j < split_params.size(); j++)
            {
                if (mode[i] == 'k'){
                    if (current_sign == '+'){
                        if (line.size() < 3){
                            ERR_NEEDMOREPARAMS();
                            break;
                        }
                        else {
                            smode = current_sign + mode[i];
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
                            smode = current_sign + mode[i];
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
                            smode = current_sign + mode[i];
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
}
