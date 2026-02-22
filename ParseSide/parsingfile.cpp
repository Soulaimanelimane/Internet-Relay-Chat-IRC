#include "ParseSide.hpp"

void ParseSide::addusernicktoclient(std::vector<Client*> &clients)
{
    size_t i = 0;

    while (i < nick.size() && i < clients.size()){
        clients[i]->set_name(nick[i], user[i]);
        i++;
    }
}
