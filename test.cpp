#include <libc.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <libc.h>
#include <limits>

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
    string shelf;
    getline(cin, shelf);
    string srt;
    sort(shelf.begin() , shelf.end());
    if (shelf.size() %2 == 0)
    {
        for(size_t i = shelf.size() / 2; i < shelf.size() ; i++)
            srt += shelf[i];
        for(size_t i = (shelf.size() / 2) - 1; i >= 0 ; i--)
            srt += shelf[i];
    }
    else
    {

    }
}

/*
{
echo "PASS red"
echo "NICK sender"
echo "USER sender 0 * :sender"
sleep 2
echo -e "PRIVMSG mylimechatnick :\001DCC SEND Makefile 2130706433 25252 505\001"
} | nc -C localhost 25252





{
echo "PASS soul\r"
echo "NICK sender\r"
echo "USER sender 0 * :sender\r"
sleep 2
echo -e "PRIVMSG brahim :\001DCC SEND text.txt 2130706433 9999 1\001\r"
} | nc -C localhost 2005



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