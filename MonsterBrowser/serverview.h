#ifndef SERVERVIEW_H
#define SERVERVIEW_H

#include "servermodel.h"
#include <QTreeView>


class ServerView : public QTreeView
{
    Q_OBJECT
public:
    ServerView(QWidget* parent);
    ~ServerView() override;
    void setModel(QAbstractItemModel* model) override;
    ServerModel* serverModel() const;

private:
    ServerModel* serverModel_;
};

#endif // SERVERVIEW_H
