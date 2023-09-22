#ifndef CHAR_MAP_H
#define CHAR_MAP_H

#include <map>

class CharsMap
{
    public:
        CharsMap();
        int getMapping(const char charToCheck) const;
    private:
        std::map<char, int> charsMap;
};

#endif