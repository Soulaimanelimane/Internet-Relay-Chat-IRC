#include <libc.h>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
int main()
{
    // std::vector<int> list ;

    // list.resize(5);
    // for (size_t i = 0; i <= 110000; i++)
    //     list[i] = i;
    // std::cout << list.size() << std::endl;
    // for (size_t i = 0; i <= 110000; i++)
    //     std::cout << list[i] << std::endl;

// sofia  |wait a minute | hurts | looking out for you | say so | on & on |lush life | waterlemon |
    // string str = "PASS omar abdellah";
    // stringstream iss(str);
    // string h;
    // while (iss >> h)
    // {
        
    // }
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t i = 5; i < 15; i++)
        {
            std::cout <<  i << std::endl;
        }
    }
    
    int fd = open("text.txt", O_CREAT | O_RDWR , 0777);

    send(fd, "azul flawen atarwa ", 20 , 0);
}

/*
pass soul
nick soulaimane 
user limane  0 * : aday

pass soul
nick ahmed 
user billa   0 * : taroudant


pass soul
nick soufiane 
user idrissi   0 * : setatt

pass soul
nick brahim 
user benaali   0 * : tadla



pass sl
nick ahmed 
user billa   0 * : taroudant
join #1337,#42
Welcome ahmed to the channel #1337
WELCOME YOU are now a  member in this channel don't forget to  set the setting for this channel using the command help to see all command
:soufiane!~Server_irc JOIN #42
:soufiane!~Server_irc JOIN #1337
privmsg #42 : let me go 


*/