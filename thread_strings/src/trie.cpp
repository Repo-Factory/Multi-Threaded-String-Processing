/* 
 * @brief Class Trie defines TrieNode struct and Trie class
 *
 * This trie data structure will be used for efficient searches of substrings in string
 * Trie class will have operations to insert and search strings (char*)
 * 
 * @dependency CharsMap
 */

#include "trie.hpp"
#include <cstdlib>

#define VALID_CHARACTERS 31
#define NULL_TERMINATOR_INDEX 30
#define NOT_FOUND 999               // Defined in chars_map API

struct TrieNode
{
    TrieNode* next[VALID_CHARACTERS];
};

namespace // Constructor helpers
{
    TrieNode* initTrieNode()
    {
        TrieNode* node = new TrieNode;
        for (int i = 0; i < VALID_CHARACTERS; ++i) {
            node->next[i] = nullptr;    // Explicitly set array values to nullptr
        }
        return node;
    }

    CharsMap* initCharsMap()
    {
        return new CharsMap();
    }
}

namespace // Destructor helpers
{
    void cleanTreeNode(TrieNode* root)
    {
        if (root == nullptr) {
            return; // base case: empty tree or means we stop the function
        }
        for (TrieNode* nextNode : root->next) {
            cleanTreeNode(nextNode); // delete each child in array by calling function recursively
        }
        delete(root); // delete the current node (happens after deleting its children)
    }
    
    void cleanCharsMap(CharsMap* charsMap)
    {
        delete(charsMap);
    }
}

Trie::Trie()
{
    this->charsMap = initCharsMap();
    this->root = initTrieNode();
}

Trie::~Trie()
{
    cleanCharsMap(this->charsMap);
    cleanTreeNode(this->root);
}

bool Trie::insertString(const char* word, TrieNode* currentNode)
{
    const int charIndex = this->charsMap->getMapping(*word);  // Get mapping from dependency
    if (charIndex == NOT_FOUND)
        return insertString(++word, currentNode);       // Skip insertion of invalid characters
    if (currentNode->next[charIndex] == nullptr)   
        currentNode->next[charIndex] = initTrieNode();  // Populating from nullptr to new TrieNode indicates insertion of letter
    if (charIndex == NULL_TERMINATOR_INDEX) 
        return true;                                    // Reaching end of string means return insertion success
    TrieNode* nextNode = currentNode->next[charIndex];
    return insertString(++word, nextNode);              // Recursively move down tree and insert letters
}

bool Trie::searchString(const char* word, TrieNode* currentNode)
{
    const int charIndex = this->charsMap->getMapping(*word);  // Get mapping from dependency
    if (charIndex == NOT_FOUND)                         
        return false;                                   // If character doesn't have mapping, clearly can't be in tree
    if (charIndex == NULL_TERMINATOR_INDEX) 
        return true;                                    // Reaching end of string means string was found
    if (currentNode->next[charIndex] == nullptr)
        return false;                                   // If expected next letter is set to nullptr, it can be deduced words isn't found
    TrieNode* nextNode = currentNode->next[charIndex];
    return searchString(++word, nextNode);              // Recursively move down tree and search letters
}