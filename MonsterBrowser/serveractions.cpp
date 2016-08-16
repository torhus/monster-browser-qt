/**
 * Implements the main functionality of the program.  Querying servers, etc.
 */

#include "serveractions.h"
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
