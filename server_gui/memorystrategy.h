#ifndef MEMORYSTRATEGY_H
#define MEMORYSTRATEGY_H


typedef std::vector<std::pair<utility::string_t, web::json::value>> field_map;


enum MemoryStrategy_t{
    ALL = 0,
    FIFO = 1,
    LRU = 2,
    SWAP = 3
};


#endif // MEMORYSTRATEGY_H
