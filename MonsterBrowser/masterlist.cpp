#include "masterlist.h"
#include "colorednames.h"
#include <iostream>
#include <utility>
using namespace std;
#include <QElapsedTimer>
#include <QFile>
#include <QMessageBox>
#include <QXmlStreamReader>


MasterList::MasterList(const QString& server) : server_(server)
{
    fileName_ = QString(server_ + ".xml").replace(':', '_');
}


void MasterList::load(const QString& defaultProtocolVersion)
{
    qInfo("Opening '%s'...", qUtf8Printable(fileName_));

    QElapsedTimer timer;
    timer.start();
    QFile f(fileName_);

    defaultProtocolVersion_ = defaultProtocolVersion;

    if (!f.open(QFile::ReadOnly)) {
        QMessageBox::critical(nullptr, "Error",
                              QString("Error while trying to open %1:\n%2")
                              .arg(fileName_).arg(f.errorString()));
        return;
    }

    QXmlStreamReader xml(&f);

    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            if (xml.name() == "cvar") {
                addCvar(xml.attributes());
            }
            else if (xml.name() == "player") {
                addPlayer(xml.attributes());
            }
            else if (xml.name() == "server") {
                startServer(xml.attributes());
            }
        }
    }

    qInfo("Loaded %d servers in %.2f seconds.", size(),
          timer.elapsed() / 1000.0);

    if (xml.hasError()) {
        QMessageBox::critical(nullptr, "Error",
                           QString("Error at line %1 while loading %2:\n %3" )
                              .arg(xml.lineNumber()).arg(fileName_)
                              .arg(xml.errorString()));
    }
}


void MasterList::startServer(QXmlStreamAttributes& attributes)
{
    ServerData sd;

    for (const auto& a: attributes) {
        if (a.name() == "name") {
            sd.rawName = a.value().toString();

            sd.server[ServerColumn::NAME] =
                                         stripColorCodes(a.value().toString());
        }
        else if (a.name() == "country_code") {
            sd.server[ServerColumn::COUNTRY] = a.value().toString();
        }
        else if (a.name() == "address") {
            sd.server[ServerColumn::ADDRESS] = a.value().toString();
        }
        else if (a.name() == "protocol_version") {
            sd.protocolVersion = a.value().toString();
        }
        else if (a.name() == "ping") {
            sd.server[ServerColumn::PING] = a.value().toString();
        }
        else if (a.name() == "player_count") {
            sd.server[ServerColumn::PLAYERS] = a.value().toString();
        }
        else if (a.name() == "country_code") {
            sd.server[ServerColumn::COUNTRY] = a.value().toString();
        }
        else if (a.name() == "map") {
            sd.server[ServerColumn::MAP] = a.value().toString();
        }
        else if (a.name() == "persistent") {
            sd.persistent = (a.value() == "true");
        }
        else if (a.name() == "fail_count") {
            sd.failCount = a.value().toInt();
        }
    }

    // Make sure there's a protocol version.  This makes it less likely the
    // server is being 'forgotten' and never queried or deleted.
    // It also takes care of upgrading from the old XML files, where there
    // was no protocol_version attribute.
    if (sd.protocolVersion.isEmpty())
        sd.protocolVersion = defaultProtocolVersion_;

    push_back(std::move(sd));
}


void MasterList::addCvar(QXmlStreamAttributes& attr)
{
    QString key(attr.value("key").toString());
    QString value(attr.value("value").toString());

     if (key.compare("g_gametype", Qt::CaseInsensitive) == 0)
         last().server[ServerColumn::GAMETYPE] = value;
     else if (key.compare("g_needpass", Qt::CaseInsensitive) == 0)
         last().server[ServerColumn::PASSWORDED] = value;

    last().cvars.push_back({key, value});
}


void MasterList::addPlayer(QXmlStreamAttributes& attr)
{
    last().players.push_back({QString(),
                              attr.value("score").toString(),
                              attr.value("ping").toString(),
                              attr.value("name").toString()});
}
