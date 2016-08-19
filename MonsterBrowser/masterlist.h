#ifndef MASTERLIST_H
#define MASTERLIST_H

#include "serverdata.h"
#include <QVector>
#include <QXmlStreamAttributes>
#include <QXmlStreamReader>


class MasterList : public QVector<ServerData>
{
public:
    MasterList(const QString& server);
    QString server() const { return server_; }
    QString fileName() const { return fileName_; }
    void load(const QString& defaultProtocolVersion);

private:
    QString server_;
    QString fileName_;
    QString defaultProtocolVersion_;

    void startServer(QXmlStreamAttributes&);
    void addCvar(QXmlStreamAttributes&);
    void addPlayer(QXmlStreamAttributes&);
};


#endif // MASTERLIST_H
