#include "restserver.h"

#define TRACE(msg)            cout << msg
#define TRACE_ACTION(a, k, v) cout << a << " (" << k << ", " << v << ")\n"

using namespace std;

static http_listener listener("http://*:9000/restdemo");

static std::map<utility::string_t, utility::string_t> dictionary;

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

RestServer& RestServer::getInstance()
{
    static RestServer server;
    return server;
}

RestServer::RestServer()
{

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
}

void RestServer::stop()
{
    listener.close();
}

std::map<utility::string_t, utility::string_t> RestServer::getDictionary()
{
    return dictionary;
}

void RestServer::handle_get(http_request request)
{
    TRACE("\nhandle GET\n");

    handle_request(
        request,
        [](const json::value & jvalue, field_map & answer)
        {

            set<utility::string_t> keys;
            for (auto const & e : jvalue.as_array())
            {
                if (e.is_string())
                {
                    auto key = e.as_string();

                    auto pos = dictionary.find(key);
                    if (pos == dictionary.end())
                    {
                        answer.push_back(make_pair(key, json::value("<NotFound>")));
                    }
                    else
                    {
                        TRACE_ACTION("found", pos->first, pos->second);
                        answer.push_back(make_pair(key, json::value(pos->second )));
                        keys.insert(key);
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

                    auto pos = dictionary.find(key);
                    if (pos == dictionary.end())
                    {
                        answer.push_back(make_pair(key, json::value("<nil>")));
                    }
                    else
                    {
                        answer.push_back(make_pair(pos->first, json::value(pos->second)));
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

                    if (dictionary.find(key) == dictionary.end())
                    {
                        TRACE_ACTION("added", key, value);
                        answer.push_back(make_pair(key, json::value("<put>")));
                    }
                    else
                    {
                        TRACE_ACTION("updated", key, value);
                        answer.push_back(make_pair(key, json::value("<updated>")));
                    }

                    dictionary[key] = value;
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

                    auto pos = dictionary.find(key);
                    if (pos == dictionary.end())
                    {
                        answer.push_back(make_pair(key, json::value("<failed>")));
                    }
                    else
                    {
                        TRACE_ACTION("deleted", pos->first, pos->second);
                        answer.push_back(make_pair(key, json::value("<deleted>")));
                        keys.insert(key);
                    }
                }
            }
            for (auto const & key : keys)
                dictionary.erase(key);
        }
    );
}











