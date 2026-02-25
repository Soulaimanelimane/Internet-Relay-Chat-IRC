#include "ParseSide.hpp"

void    ParseSide::parse_PASS(Client &client, std::string &cmdarg, std::string &correct_pass)
{
    std::vector<std::string> line = ft_split(cmdarg, ' ');
    std::string cmd = line[0];
    if (cmd != "PASS"){
        ERR_CMDDISMATCH(cmd);
        return ;
    }
    if (line.size() < 2){
        ERR_NEEDMOREPARAMS();
        return;
    }
    if (line.size() > 2){
        ERR_TOOMANYPARAMS();
        return;
    }

    std::string client_password = line[1];
    if (client_password.length() > 255){
        ERR_EXCEEDLIMIT();
        return;
    }
    // if (!client_password.empty() && client_password[client_password.size() - 1] == '\r')
    //     client_password.erase(client_password.size() - 1);
    // if(client_password[client_password.size() - 1] == '\n')
    //     client_password.pop_back();
    // if(line[1] == "brahim")
    // std::cout << correct_pass << "hrerewewrqwerqwerasldfkjas\n";
        // std::cout << "->> \n" << client_password << std::endl<< "espace\n" << correct_pass;
    if(client_password == correct_pass)
    {
        client.set_pass() = true;
        std::cout << "password correct :) \n";
    }
    // check if is registred before pass
    // check if is match client pass with server password
}