#include "ParseSide.hpp"

void    ParseSide::parse_PASS(Client &client, std::string &cmdarg, std::string &correct_pass)
{
    std::vector<std::string> line = ft_split(cmdarg, 0);
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
    if(client_password == correct_pass)
    {
        client.set_pass() = true;
        std::cout << "CLIENT[" << client.get_fd() << "] : " <<  "PASSWORD CORRECT :) \n";
        send(client.get_fd(), "--> Password accepted :)\n", 25, 0);
    }
    else
    {
        std::cout << "CLIENT[" << client.get_fd() << "] : " << "PASSWORD INCORRECT :( \n";
    }
}