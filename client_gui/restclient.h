#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QObject>
#include <QString>

#include <cpprest/http_client.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

#include <iostream>

class RestClient : public QObject
{
    Q_OBJECT
public:
    explicit RestClient(QObject *parent = 0);
    QString get_response;
    QString put_response;
    QString del_response;

signals:

public slots:

    void get( QString key );
    void put( QString key,QString value );
    void del( QString key );

    QString getGET(){ return get_response;}
    QString getPUT(){ return put_response;}
    QString getDEL(){ return del_response;}

private:

};

#endif // RESTCLIENT_H
