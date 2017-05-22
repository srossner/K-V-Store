#ifndef LRU_DICTIONARY_H
#define LRU_DICTIONARY_H

#include "dictionary.h"


class LRU_Dictionary : public Dictionary
{

public:
    LRU_Dictionary();
    void add(std::string key, std::string value);
    void del(std::string key);
    void get(std::string key);

};

#endif // LRU_DICTIONARY_H
