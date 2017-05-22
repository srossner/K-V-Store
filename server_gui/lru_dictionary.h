#ifndef LRU_DICTIONARY_H
#define LRU_DICTIONARY_H

#include "dictionary.h"

#include <map>
#include <list>
#include <set>
#include <string>
#include <iostream>
#include <utility>
#include <cpprest/json.h>



class LRU_Dictionary : public Dictionary
{

public:
    LRU_Dictionary();

    void insert(std::string key, std::string value);

    void update(std::string key, std::string value);

    void erase(std::string key);

    std::string get(std::string key);

    bool find(std::string key);

    field_map getAll();

    std::size_t getNumberOfElements();

};

#endif // LRU_DICTIONARY_H
