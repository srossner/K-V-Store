#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <map>
#include <set>
#include <string>
#include <iostream>
#include <utility>

class Dictionary
{

public:
    Dictionary();

public:

    virtual void add(std::string key, std::string value) = 0;
    virtual void del(std::string key) = 0;
    virtual void get(std::string key) = 0;

    virtual ~Dictionary() {}


private:
    static std::map<std::string, std::string> dictionary;

};

#endif // DICTIONARY_H

