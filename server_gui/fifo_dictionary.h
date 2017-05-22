#ifndef FIFO_DICTIONARY_H
#define FIFO_DICTIONARY_H

#include "dictionary.h"


class FIFO_Dictionary : public Dictionary
{

public:
    FIFO_Dictionary();
    void add(std::string key, std::string value);
    void del(std::string key);
    void get(std::string key);

};

#endif // FIFO_DICTIONARY_H
