#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

#define TRACE(msg)            cout << msg
#define TRACE_ACTION(a, k, v) cout << a << " (" << k << ", " << v << ")\n"

map<utility::string_t, utility::string_t> dictionary;


/* handlers implementation */

void handle_get(http_request request)
{
    TRACE("\nhandle GET\n");

    json::value answer;

    for (auto const & p : dictionary)
    {
        answer[p.first] = json::value(p.second);
    }

    request.reply(status_codes::OK, answer );
}

void handle_request(http_request request,
    function<void(const json::value &,  json::value &)> action)
{
     json::value answer;

    request
        .extract_json()
        .then([&answer, &action](pplx::task<json::value> task) {
        try
        {
            const auto & jvalue = task.get();

            if (!jvalue.is_null())
            {
                action(jvalue, answer);
            }
        }
        catch (http_exception const & e)
        {
            cout << e.what() << endl;
        }
    })
        .wait();

    request.reply(status_codes::OK, answer );
}

void handle_post(http_request request)
{
    TRACE("\nhandle POST\n");

    handle_request(
        request,
        [](const json::value & jvalue,  json::value & answer)
    {
        for (auto const & e : jvalue.as_array())
        {
            if (e.is_string())
            {
                auto key = e.as_string();

                auto pos = dictionary.find(key);
                if (pos == dictionary.end())
                {
                    answer[key] = json::value("<nil>");
                }
                else
                {
                    answer[pos->first] =  json::value(pos->second);
                }
            }
        }
    }
    );
}

void handle_put(http_request request)
{
    TRACE("\nhandle PUT\n");

    handle_request(
        request,
        [](const json::value & jvalue, json::value & answer)
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
                    answer[key] =  json::value("<put>");
                }
                else
                {
                    TRACE_ACTION("updated", key, value);
                    answer[key] =  json::value("<updated>");
                }

                dictionary[key] = value;
            }
        }
    }
    );
}

void handle_del(http_request request)
{
    TRACE("\nhandle DEL\n");

    handle_request(
        request,
        [](const json::value & jvalue, json::value & answer)
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
                    answer[key] =  json::value("<failed>");
                }
                else
                {
                    TRACE_ACTION("deleted", pos->first, pos->second);
                    answer[key] =  json::value("<deleted>");
                    keys.insert(key);
                }
            }
        }

        for (auto const & key : keys)
            dictionary.erase(key);
    }
    );
}



int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    http_listener listener("http://localhost/restdemo");

    listener.support(methods::GET, handle_get);
    listener.support(methods::POST, handle_post);
    listener.support(methods::PUT, handle_put);
    listener.support(methods::DEL, handle_del);

    try
    {
        listener
            .open()
            .then([&listener]() {TRACE("\nstarting to listen\n"); })
            .wait();

        while (true);
    }
    catch (exception const & e)
    {
        cout << e.what() << endl;
    }

    return app.exec();
}






