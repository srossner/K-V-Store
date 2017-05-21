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


typedef std::vector<std::pair<utility::string_t, json::value>> field_map;



class RestServer
{
public:
    static RestServer& getInstance();

    void start();
    void stop();
    std::map<utility::string_t, utility::string_t> getDictionary();

private:

    RestServer();

    static void handle_get(http_request request);
    static void handle_post(http_request request);
    static void handle_put(http_request request);
    static void handle_del(http_request request);

};

#endif // RESTSERVER_H
