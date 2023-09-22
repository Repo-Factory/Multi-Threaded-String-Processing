/* 
 * @brief Class CharsMap will hold hash map data member to map letters to an index
 *        of TrieNode* array found in TrieNode struct.
 *
 * This charsMap can be passed around as a dependency to give Trie access to mapping. 
 * This mapping will be checked to find which child of the current trie node should be
 * set from nullptr to a new TrieNode (if any). 
 */

#include <stdio.h>
#include <cstring>
#include "chars_map.hpp"

namespace
{
    #define SPECIAL_CHARACTERS {' ', '\'', '-', '_'}
    #define SPECIAL_CHARACTER_SIZE 4
    #define ALPHABET_SIZE 26
    #define FIRST_UPPERCASE_LETTER 'A'
    #define FIRST_LOWERCASE_LETTER 'a'    
    #define NULL_TERMINATOR_CHAR '\0'
    #define LASTCHARACTER_INDEX 30
    #define LOOP_COUNTER_INIT 0
    #define NOT_FOUND 999
}

namespace
{ 
    void populateAlphabeticLetters(std::map<char, int>& charsMap) // Iterate through lower and uppercase alphabet, adding chars to hashMap
    {
        for (int i = LOOP_COUNTER_INIT; i < ALPHABET_SIZE; i++) {
            charsMap.insert({FIRST_LOWERCASE_LETTER + i, i});
            charsMap.insert({FIRST_UPPERCASE_LETTER + i, i});     // Note that the map is case insensitive, these map to same value              
        }
    }

    void populateSpecialCharacters(std::map<char, int>& charsMap) // Move special chars from macro to hashMap
    {
        const char specialChars[] = SPECIAL_CHARACTERS;
        for (int i = LOOP_COUNTER_INIT; i < SPECIAL_CHARACTER_SIZE; i++) {
            charsMap.insert({specialChars[i], i + ALPHABET_SIZE});  // Place special characters after alphabetic letters
        }
        charsMap.insert({NULL_TERMINATOR_CHAR, LASTCHARACTER_INDEX}); // This can't be stored in macro as it will be read as array termination
    }
}

CharsMap::CharsMap() // Constructor of class simply populates the hash map data member with all the mappings
{
    populateAlphabeticLetters(this->charsMap);
    populateSpecialCharacters(this->charsMap);
}

int CharsMap::getMapping(const char charToCheck) const // public API to get mapping of char
{
    auto it = charsMap.find(charToCheck);
    if (it != charsMap.end()) {
        return it->second;
    } else {
        return NOT_FOUND;
    }
}