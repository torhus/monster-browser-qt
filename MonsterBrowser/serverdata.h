#ifndef SERVERDATA_H
#define SERVERDATA_H

#include <array>
#include <QString>
#include <QVector>


namespace PlayerColumn {
    enum { NAME, SCORE, PING, RAWNAME, N_COLUMNS };
}

namespace ServerColumn {
    enum { COUNTRY, NAME, PASSWORDED, PING, PLAYERS, GAMETYPE, MAP, ADDRESS,
           MAX, N_COLUMNS };
}


/* Stores all data for a server. */
struct ServerData
{
    // server name, with any color codes intact
    QString rawName;
    // name (without color codes), ping, playercount, map, etc.
    // Note: If this is a zero-length array, this object is considered to be
    // empty, and can be deleted.
    std::array<QString, ServerColumn::N_COLUMNS> server;
    // list of players, with country, name, score, ping, and raw name (with
    // color codes) for each.
    QVector<std::array<QString, PlayerColumn::N_COLUMNS>> players;
    // list of cvars, with key and value for each
    QVector<std::array<QString, 2>> cvars;

    int failCount = 0;
    bool persistent;
    QString protocolVersion;

    int humanCount() const;
    int botCount() const;
    int maxClients() const;
    void print() const;
};


// For sorting ServerData objects.
struct ServerLessThan
{
    ServerLessThan(int column, bool reverse)
        : col_(column), rev_(reverse) { }
    bool operator()(const ServerData& a, const ServerData& b) const;

private:
    int col_;
    bool rev_;
};


#endif // SERVERDATA_H
