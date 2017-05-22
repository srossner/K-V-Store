#ifndef RESTSERVER_H
#define RESTSERVER_H

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#include <iostream>
#include <map>
#include <set>
#include <string>

#include "memorystrategy.h"

typedef std::vector<std::pair<utility::string_t, json::value>> field_map;


class RestServer
{
public:
    RestServer();

    void start();
    void stop();

    void setMemoryStrategy( MemoryStrategy_t memoryStrategy );

private:

    static void handle_get(http_request request);
    static void handle_post(http_request request);
    static void handle_put(http_request request);
    static void handle_del(http_request request);

    MemoryStrategy_t m_MemoryStrategy;


    static std::map<utility::string_t, utility::string_t> m_dictionary;

};

#endif // RESTSERVER_H
