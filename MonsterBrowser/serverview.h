#ifndef SERVERVIEW_H
#define SERVERVIEW_H

#include <QTreeView>


class ServerView : public QTreeView
{
    Q_OBJECT
public:
    ServerView(QWidget* parent);
    ~ServerView() override;
    void setModel(QAbstractItemModel *model) override;
};

#endif // SERVERVIEW_H
