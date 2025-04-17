/* Alexander Dumais | 2023-2025
 * ltrim and rtrim taken from:
 * https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring
 */

#pragma once
#include <string>
#include <algorithm>

/**
 * @brief for every letter in std::string `s`, convert it to lower case
 * 
 * @param s the std::string being to which std::tolower is bring applied to, 
 * character by character
 */
static inline void toLower(std::string &s)
{
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c){ return std::tolower(c); });
}

/* trim from start (in place) */
static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

/* trim from end (in place) */
static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

/* trim both right and left */
static inline void trim(std::string & s)
{
    ltrim(s);
    rtrim(s);
}
