#ifndef RESTSERVER_H
#define RESTSERVER_H

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

#include <iostream>
#include <map>
#include <set>
#include <string>

#include "memorystrategy.h"

class RestServer
{
public:
    RestServer();

    void start();
    void stop();

    void setMemoryStrategy( MemoryStrategy_t memoryStrategy );

    void setMAX_SIZE( int MAX_SIZE );

private:

    static void handle_get (web::http::http_request request);
    static void handle_post(web::http::http_request request);
    static void handle_put (web::http::http_request request);
    static void handle_del (web::http::http_request request);

    MemoryStrategy_t m_MemoryStrategy;

    int MAX_SIZE;

    bool running;

};

#endif // RESTSERVER_H
