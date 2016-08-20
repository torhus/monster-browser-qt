#ifndef SERVERACTIONS_H
#define SERVERACTIONS_H

#include "workerobject.h"
#include <QThread>



class ServerActions : public QObject
{
    Q_OBJECT
public:
    enum {actionCheckForNew, actionRefreshAll};
    ServerActions();
    virtual ~ServerActions();

signals:
    void queueAction(int action);

public slots:
    void checkForNew();
    void refreshAll();
    void actionFinished();

private:
    WorkerObject workerObject;
    QThread workerThread;
};


/* Global instance. */
extern ServerActions* serverActions;

#endif // SERVERACTIONS_H
