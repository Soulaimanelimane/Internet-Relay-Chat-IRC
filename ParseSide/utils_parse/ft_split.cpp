#include "../ParseSide.hpp"

std::vector<std::string> ft_split(const std::string& str, char delim)
{
    std::vector<std::string> result;
    std::string token;
    std::istringstream iss(str);

    if (delim == 0)
    {
        while (iss >> token)
        {
            if (!token.empty()) 
                result.push_back(token);
        }
    }
    else
    {
        while (std::getline(iss, token, delim))
        {
            if (!token.empty()) 
                result.push_back(token);
        }
    }

    return result;
}