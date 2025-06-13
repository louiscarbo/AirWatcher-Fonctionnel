#if ! defined ( Utils )
#define Utils
using Timestamp = std::chrono::time_point<std::chrono::system_clock>;
#include <string>
#include <iomanip>   // pour std::get_time
#include <sstream>
#include <chrono>
#include <ctime>
#include <iostream>
using namespace std;

static Timestamp parseTimestamp(const std::string &input)
{
    std::tm tm = {};
    std::istringstream ss(input);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

    if (ss.fail()) {
        std::cerr << "Erreur parsing : " << input << std::endl;
        return Timestamp{};
    }

    
    // mktime suppose heure locale, donc pour garder l'heure exacte
    // on peut désactiver l'ajustement DST automatique
    tm.tm_isdst = 0; // 0 = ne pas considérer l'heure d'été

    std::time_t tt = std::mktime(&tm);// mktime assume tm en heure locale
    if (tt == -1) {
        std::cerr << "Erreur mktime : " << input << std::endl;
        return Timestamp{};
    }

    return std::chrono::system_clock::from_time_t(tt);
}


#endif // Utils