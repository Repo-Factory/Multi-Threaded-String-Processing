#ifndef TRIE_H
#define TRIE_H

#include <memory>
#include "chars_map.hpp"

struct TrieNode;

class Trie
{
    public:
        Trie();
        ~Trie();
        bool insertString(const char* word = nullptr, TrieNode* currentNode = nullptr);
        bool searchString(const char* word = nullptr, TrieNode* currentNode = nullptr);
        TrieNode* getRoot() {return this->root;}
    private:
        TrieNode* root = nullptr;
        CharsMap* charsMap = nullptr;
};

#endif