#ifndef FIFO_DICTIONARY_H
#define FIFO_DICTIONARY_H

#include "dictionary.h"

#include <map>
#include <queue>
#include <set>
#include <string>
#include <iostream>
#include <utility>
#include <cpprest/json.h>

#include "memorystrategy.h"


class FIFO_Dictionary : public Dictionary
{

public:
    FIFO_Dictionary();

    void insert(std::string key, std::string value);

    void update(std::string key, std::string value);

    void erase(std::string key);

    std::string get(std::string key);

    bool find(std::string key);

    field_map getAll();

    std::size_t getNumberOfElements();

private:

};

#endif // FIFO_DICTIONARY_H
