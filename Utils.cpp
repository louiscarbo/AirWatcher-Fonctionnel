#if ! defined ( Utils )
#define Utils

using Timestamp = std::chrono::time_point<std::chrono::system_clock>;
#include <string>
using namespace std;

static Timestamp parseTimestamp(const std::string &input)
{
    // attend le format "YYYY-MM-DD HH:MM:SS" (longueur 19)
    if (input.size() != 19
     || input[4] != '-' || input[7] != '-'
     || input[10] != ' ' || input[13] != ':' || input[16] != ':')
    {
        return Timestamp{};
    }

    std::tm tm = {};
    try {
        tm.tm_year = std::stoi(input.substr(0,4)) - 1900;
        tm.tm_mon  = std::stoi(input.substr(5,2)) - 1;
        tm.tm_mday = std::stoi(input.substr(8,2));
        tm.tm_hour = std::stoi(input.substr(11,2));
        tm.tm_min  = std::stoi(input.substr(14,2));
        tm.tm_sec  = std::stoi(input.substr(17,2));
    } catch (...) {
        return Timestamp{};
    }

    // mktime assume tm en heure locale
    std::time_t tt = std::mktime(&tm);
    return std::chrono::system_clock::from_time_t(tt);
}

#endif // Utils