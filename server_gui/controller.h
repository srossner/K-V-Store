#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include <QtQml>

#include "restserver.h"



class Controller : public QObject
{
    Q_OBJECT
public:

    explicit Controller(QObject *parent = 0);

    void start(){ m_Server.start(); }
    void stop() { m_Server.stop();  }

private:
    RestServer m_Server;

public slots:

    void setMemoryStrategy( int memoryStrategy ){ m_Server.setMemoryStrategy((MemoryStrategy_t) memoryStrategy); }

    void setMAX_SIZE( int MAX_SIZE ){ m_Server.setMAX_SIZE(MAX_SIZE);}

private:

};

#endif // CONTROLLER_H
