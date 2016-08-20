#ifndef WORKEROBJECT_H
#define WORKEROBJECT_H

#include <QObject>


/**
 * Does all work that happens in the background thread.
 */
class WorkerObject : public QObject
{
    Q_OBJECT
public:
    explicit WorkerObject(QObject *parent = 0);
    void abortAction();

signals:
    void actionFinished();

public slots:
    void queueAction(int action);

private:
    bool abort_;
};

#endif // WORKEROBJECT_H
