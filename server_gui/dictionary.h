#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <map>
#include <set>
#include <string>
#include <iostream>
#include <utility>
#include <cpprest/json.h>

#include "memorystrategy.h"


class Dictionary
{

public:
    Dictionary();

public:

    virtual void insert(std::string key, std::string value) = 0;

    virtual void update(std::string key, std::string value) = 0;

    virtual void erase(std::string key) = 0;

    virtual std::string get(std::string key) = 0;

    virtual bool find(std::string key) = 0;

    virtual field_map getAll() = 0;

    virtual std::size_t getNumberOfElements() = 0;

    virtual ~Dictionary() {}

    void setMAX_SIZE(int MAX_SIZE){  MAX_NUMBER_OF_ELEMENTS = MAX_SIZE;}

protected:
    size_t MAX_NUMBER_OF_ELEMENTS;

};


#endif // DICTIONARY_H

