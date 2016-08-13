#include "serverdata.h"
#include <iostream>
using namespace std;


/*
 * Extract some info about the server.
 *
 * Default to zero when there is no info available.
 */
int ServerData::humanCount() const
{
    const QString& s = server[ServerColumn::PLAYERS];
    int plus = s.indexOf('+');

    return (plus != -1) ? s.leftRef(plus).toInt() : 0;
}


int ServerData::botCount() const
{
    const QString& s = server[ServerColumn::PLAYERS];
    int plus = s.indexOf('+');
    int slash = s.indexOf('/');

    if (plus == -1 || slash == -1)
        return 0;
    else
        return s.midRef(plus + 1, slash - plus - 1).toInt();
}


int ServerData::maxClients() const
{
    const QString& s = server[ServerColumn::PLAYERS];
    int slash = s.indexOf('/');

    return (slash != -1) ? s.midRef(slash + 1).toInt() : 0;
}


void ServerData::print() const
{
    cout << rawName.toStdString() << '\n';

    for (size_t i = 0; i < server.size(); i++) {
        cout << server[i].toStdString();
        if (i < (server.size() - 1))
            cout << (' ');
    }
    cout << endl;

    // Cvars
    for (const auto& cvar: cvars) {
        cout << "cvar " << cvar[0].toStdString() << ' ' <<
                cvar[1].toStdString() << '\n';
    }

    // Players
    for (const auto& p: players) {
        cout << "player " << p[0].toStdString() << ' ' << p[1].toStdString() <<
                ' ' << p[2].toStdString() << '\n';
    }
}


bool ServerLessThan::operator()(const ServerData& a, const ServerData& b) const
{
    int result;

    switch(col_) {
        case ServerColumn::PLAYERS:
            result = b.humanCount() - a.humanCount();
            if (result)
                break;
            result = b.botCount() - a.botCount();
            if (result)
                break;
            result = b.maxClients() - a.maxClients();
            break;
        case ServerColumn::PING:
            result = a.server[col_].toInt() - b.server[col_].toInt();
            break;
        default:
            result = QString::compare(a.server[col_], b.server[col_],
                                      Qt::CaseInsensitive);
    }

    return rev_ ? (result > 0) : (result < 0);
}
