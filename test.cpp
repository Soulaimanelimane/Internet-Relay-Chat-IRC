#include <libc.h>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> list ;

    list.resize(5);
    for (size_t i = 0; i <= 110000; i++)
        list[i] = i;
    std::cout << list.size() << std::endl;
    for (size_t i = 0; i <= 110000; i++)
        std::cout << list[i] << std::endl;

// sofia  |wait a minute | hurts | looking out for you | say so | on & on |lush life | waterlemon |
    
}