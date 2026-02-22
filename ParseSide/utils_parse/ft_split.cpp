#include "../ParseSide.hpp"

std::vector<std::string> ft_split(const std::string& str, char delim)
{
    std::vector<std::string> result;
    std::string token;
    std::istringstream iss(str);

    while (std::getline(iss, token, delim))
    {
        if (!token.empty()) // skip empty tokens (optional)
            result.push_back(token);
    }

    return result;
}