#ifndef ALL_DICTIONARY_H
#define ALL_DICTIONARY_H

#include "dictionary.h"


class All_Dictionary : public Dictionary
{

public:
    All_Dictionary();

    void add(std::string key, std::string value);
    void del(std::string key);
    void get(std::string key);

};


#endif // ALL_DICTIONARY_H
