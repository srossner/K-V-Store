#ifndef SWAP_DICTIONARY_H
#define SWAP_DICTIONARY_H
#include "dictionary.h"

#include <map>
#include <set>
#include <string>
#include <iostream>
#include <utility>
#include <cpprest/json.h>
#include <fstream>
#include <cstdlib>
#include <cctype>

#include "memorystrategy.h"

class Swap_Dictionary : public Dictionary
{
public:
    Swap_Dictionary();

    void insert(std::string key, std::string value);

    void update(std::string key, std::string value);

    void erase(std::string key);

    std::string get(std::string key);

    bool find(std::string key);

    field_map getAll();

    std::size_t getNumberOfElements();

    ~Swap_Dictionary();

};

#endif // SWAP_DICTIONARY_H
