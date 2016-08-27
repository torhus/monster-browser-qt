#include "workerobject.h"
#include <QThread>


WorkerObject::WorkerObject(QObject *parent) : QObject(parent)
{

}


void WorkerObject::abortAction()
{
    abort_ = true;
}


void WorkerObject::queueAction(int action)
{
    abort_ = false;
    qDebug("WorkerObject::queueAction()");
    for (;;) {
        if (abort_)
            break;
    }
    emit actionFinished();
}
