#include "restserver.h"
#include "dictionary.h"
#include "all_dictionary.h"
#include "fifo_dictionary.h"
#include "lru_dictionary.h"

#define TRACE(msg)            cout << msg
#define TRACE_ACTION(a, k, v) cout << a << " (" << k << ", " << v << ")\n"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
using namespace std;

static http_listener listener("http://*:9000/restdemo");
static shared_ptr<Dictionary> dictionary;


void RestServer::setMemoryStrategy( MemoryStrategy_t memoryStrategy )
{
    m_MemoryStrategy = memoryStrategy;
    cout << std::endl<< "Memory Strategy: " << m_MemoryStrategy << std::endl;

    switch(memoryStrategy)
    {
    case ALL:
        dictionary = std::shared_ptr<Dictionary>(new All_Dictionary);
        break;
    case FIFO:
        dictionary = std::shared_ptr<Dictionary>(new FIFO_Dictionary);
        break;
    case LRU:
        dictionary = std::shared_ptr<Dictionary>(new LRU_Dictionary);
        break;
    }

    dictionary->setMAX_SIZE(MAX_SIZE);
}

void RestServer::setMAX_SIZE( int MAX_SIZE )
{
    this->MAX_SIZE = MAX_SIZE;
    if(running)
        dictionary->setMAX_SIZE(MAX_SIZE);
}

void handle_request(http_request request, function<void(const json::value &, field_map &)> action)
{
    field_map answer;

    request.extract_json().then
    (
        [&answer, &action](pplx::task<json::value> task)
        {
            try{
                const auto & jvalue = task.get();

                if (!jvalue.is_null())
                {
                    action(jvalue, answer);
                }
            }catch (http_exception const & e)
            {
                cout << e.what() << endl;
            }
        }
    ).wait();

    request.reply(status_codes::OK, json::value::object(answer));
}

RestServer::RestServer()
{

    running = false;
    listener.support(methods::GET,    RestServer::handle_get);
    listener.support(methods::POST,   RestServer::handle_post);
    listener.support(methods::PUT,    RestServer::handle_put);
    listener.support(methods::DEL,    RestServer::handle_del);

}

void RestServer::start()
{
    try{
        listener.open().then
        (
            [&]()
            {
                cout << "\n"
                     << "starting to listen\n";
            }
        ).wait();

    }catch (exception const & e){

        cout << e.what() << endl;
    }
    running = true;
}

void RestServer::stop()
{
    listener.close();
    running = false;
}

void RestServer::handle_get(http_request request)
{
    TRACE("\nhandle GET\n");

    handle_request(
        request,
        [](const json::value & jvalue, field_map & answer)
        {
            for (auto const & e : jvalue.as_array())
            {
                if (e.is_string())
                {
                    auto key = e.as_string();

                    if (!dictionary->find(key))
                    {
                        answer.push_back(make_pair(key, json::value("<NotFound>")));
                    }
                    else
                    {
                        TRACE_ACTION("found", key, dictionary->get(key));
                        answer.push_back(make_pair(key, json::value(dictionary->get(key))));
                    }
                }else{
                    if (e.is_number() )
                    {
                        int key = e.as_integer ();
                        if ( key == 1 )
                        {

                            answer = dictionary->getAll();
                        }
                    }
                }
            }
        }
    );
}


void RestServer::handle_post(http_request request)
{
    TRACE("\nhandle POST\n");

    handle_request( request,
        [](const json::value & jvalue, field_map & answer)
        {
            for (auto const & e : jvalue.as_array())
            {
                if (e.is_string())
                {
                    auto key = e.as_string();

                    if (!dictionary->find(key))
                    {
                        answer.push_back(make_pair(key, json::value("<nil>")));
                    }
                    else
                    {
                        answer.push_back(make_pair(key , json::value( dictionary->get(key) )));
                    }
                }
            }
        }
    );
}

void RestServer::handle_put(http_request request)
{
    TRACE("\nhandle PUT\n");

    handle_request( request,

        [](const json::value & jvalue, field_map & answer)
        {
            for (auto const & e : jvalue.as_object())
            {
                if (e.second.is_string())
                {
                    auto key = e.first;
                    auto value = e.second.as_string();

                    if (!dictionary->find(key))
                    {
                        TRACE_ACTION("added", key, value);
                        answer.push_back(make_pair(key, json::value("<put>")));
                        dictionary->insert(key, value);
                    }
                    else
                    {
                        TRACE_ACTION("updated", key, value);
                        answer.push_back(make_pair(key, json::value("<updated>")));
                        dictionary->update(key, value);
                    }
                }
            }
        }
    );
}

void RestServer::handle_del(http_request request)
{
    TRACE("\nhandle DEL\n");

    handle_request(request,

        [](const json::value & jvalue, field_map & answer)
        {
            set<utility::string_t> keys;
            for (auto const & e : jvalue.as_array())
            {
                if (e.is_string())
                {
                    auto key = e.as_string();

                    if (!dictionary->find(key))
                    {
                        answer.push_back(make_pair(key, json::value("<failed>")));
                    }
                    else
                    {
                        TRACE_ACTION("deleted", key, dictionary->get(key));
                        answer.push_back(make_pair(key, json::value("<deleted>")));
                        keys.insert(key);
                    }
                }
            }
            for (auto const & key : keys)
                dictionary->erase(key);
        }
    );
}











