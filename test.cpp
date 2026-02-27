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
    string str = "PASS omar abdellah";
    stringstream iss(str);
    string h;
    while (iss >> h)
    {
        cout << h << endl;
    }
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

*/