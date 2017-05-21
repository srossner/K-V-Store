#include <cpprest/http_client.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

#include <iostream>
using namespace std;

void display_field_map_json( const json::value & jvalue)
{
    if (!jvalue.is_null())
    {
        for (auto const & e : jvalue.as_object())
        {
            cout << e.first << " : " << e.second.as_string() << endl;
        }
    }
}

pplx::task<http_response> make_task_request(http_client & client,
    method mtd,
    json::value const & jvalue)
{
    return (mtd == methods::GET || mtd == methods::HEAD) ?
        client.request(mtd, "/restdemo") :
        client.request(mtd, "/restdemo", jvalue);
}

void make_request(http_client & client, method mtd, json::value const & jvalue)
{
    make_task_request(client, mtd, jvalue).then
    (
        [](http_response response)

        {
            if (response.status_code() == status_codes::OK)
            {
                return response.extract_json();
            }
            return pplx::task_from_result(json::value());
        }

    ).then(
        [](pplx::task<json::value> previousTask)
        {
            try
            {
                display_field_map_json(previousTask.get());
            }
            catch (http_exception const & e)
            {
                cout << e.what() << endl;
            }
        }
    ).wait();
}

int main()
{
    http_client client("http://*:9000");

    std::vector<std::pair<utility::string_t, json::value>> putvalue;
    putvalue.push_back(make_pair("one", json::value("100")));
    putvalue.push_back(make_pair("two", json::value("200")));

    cout << "\nput values\n";
    make_request(client, methods::PUT, json::value::object(putvalue));

    auto getvalue = json::value::array();
    getvalue[0] = json::value("one");
    getvalue[1] = json::value("two");
    getvalue[2] = json::value("three");

    cout << "\nget values (POST)\n";
    make_request(client, methods::POST, getvalue);

    auto delvalue = json::value::array();
    delvalue[0] = json::value("one");

    cout << "\ndelete values\n";
    make_request(client, methods::DEL, delvalue);

    cout << "\nget values (POST)\n";
    make_request(client, methods::POST, getvalue);

    cout << "\nget values (GET)\n";
    make_request(client, methods::GET, json::value::null());

    return 0;
}
