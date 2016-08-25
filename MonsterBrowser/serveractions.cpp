/**
 * Implements the main functionality of the program.  Querying servers, etc.
 */

#include "serveractions.h"
#include "mainwindow.h"
#include "servermodel.h"
#include <QtDebug>


ServerActions* serverActions;


ServerActions::ServerActions()
{
    workerObject.moveToThread(&workerThread);
    connect(this, &ServerActions::queueAction, &workerObject,
            &WorkerObject::queueAction);
    connect(&workerObject, &WorkerObject::actionFinished, this,
            &ServerActions::actionFinished);
    workerThread.start();
}


ServerActions::~ServerActions()
{
    workerObject.abortAction();
    workerThread.exit();
    workerThread.wait();
}


/**
 * Refreshes all servers for the current game.
 */
void ServerActions::refreshAll()
{
    QVector<QString> addresses;

    qDebug() << "Refreshing all...";
    workerObject.abortAction();

    for (const auto& sd: serverView->serverModel()->master()) {
        addresses.push_back(sd.server[ServerColumn::ADDRESS]);
    }
    emit queueAction(actionRefreshAll);
}


/**
 * Checks for new servers for the current game.
 */
void ServerActions::checkForNew()
{
    qDebug() << "Checking for new servers...";
    workerObject.abortAction();
    emit queueAction(actionCheckForNew);
}


void ServerActions::actionFinished()
{
    qDebug() << "ServerAction::actionFinished()";
}
