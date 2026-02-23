#include "ParseSide.hpp"

void    parse_PASS(std::string &cmdarg)
{
    std::vector<std::string> line = ft_split(cmdarg, ' ');
    std::string cmd = line[0];
    if (cmd != "PASS"){
        ERR_CMDDISMATCH(cmd);
        return;
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
    // check if is registred before pass
    // check if is match client pass with server password
}