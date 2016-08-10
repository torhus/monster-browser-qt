#include "serverdata.h"
#include <iostream>
using namespace std;


void ServerData::print() const
{
    cout << rawName.toStdString() << '\n';

    for (size_t i = 0; i < server.size(); i++) {
        cout << server[i].toStdString();
        if (i < (server.size() - 1))
            cout << (' ');
    }
    cout << endl;

    // Cvars.
    for (const auto& cvar: cvars) {
        cout << "cvar " << cvar[0].toStdString() << ' ' <<
                cvar[1].toStdString() << '\n';
    }

    // Players.
    for (const auto& p: players) {
        cout << "player " << p[0].toStdString() << ' ' << p[1].toStdString() <<
                ' ' << p[2].toStdString() << '\n';
    }
}
