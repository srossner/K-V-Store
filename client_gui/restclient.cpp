#include "restclient.h"

using namespace std;

static http_client httpclient("http://*:9000");


void display_field_map_json( const json::value & jvalue, QString* response )
{
    if (!jvalue.is_null())
    {
        string res = "";
        for (auto const & e : jvalue.as_object())
        {
            res = res + e.first + " : " + e.second.as_string() + "\n";
            cout << res;
        }

        *response = QString::fromStdString(res);
    }
}

pplx::task<http_response> make_task_request(http_client & client,
    method mtd,
    json::value const & jvalue)
{
    return (mtd == methods::HEAD) ?
        client.request(mtd, "/restdemo") :
        client.request(mtd, "/restdemo", jvalue);
}



void make_request(http_client & client, method mtd, json::value const & jvalue, QString* response )
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
        [=](pplx::task<json::value> previousTask)
        {
            try
            {
                display_field_map_json(previousTask.get(), response );

            }
            catch (http_exception const & e)
            {
                cout << "make_request\n " << e.what() << endl;
            }
        }
    ).wait();
}

RestClient::RestClient(QObject *parent) : QObject(parent)
{

}

void RestClient::put( QString key, QString value )
{
    std::vector<std::pair<utility::string_t, json::value>> putvalue;
    putvalue.push_back(make_pair(key.toUtf8().constData(), json::value(value.toUtf8().constData())));

    make_request(httpclient, methods::PUT, json::value::object(putvalue), &put_response);
}

void RestClient::del( QString key )
{
    auto delValue = json::value::array();
    delValue[0] = json::value(key.toUtf8().constData());

    make_request(httpclient, methods::DEL, delValue, &del_response);
}

void RestClient::get( QString key )
{
    auto getValue = json::value::array();
    getValue[0] = json::value(key.toUtf8().constData());

    make_request(httpclient, methods::GET, getValue, &get_response);
}


