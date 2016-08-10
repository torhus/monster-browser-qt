#ifndef MASTERLIST_H
#define MASTERLIST_H

#include "serverdata.h"
#include <QVector>
#include <QXmlStreamAttributes>
#include <QXmlStreamReader>


class MasterList : public QVector<ServerData>
{
public:
    void load(QString defaultProtocolVersion);

private:
    QString defaultProtocolVersion_;

    void startServer(QXmlStreamAttributes&);
    void addCvar(QXmlStreamAttributes&);
    void addPlayer(QXmlStreamAttributes&);
};


#endif // MASTERLIST_H
