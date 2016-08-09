#ifndef SERVERVIEW_H
#define SERVERVIEW_H

#include <QTreeView>


class ServerView : public QTreeView
{
    Q_OBJECT
public:
    ServerView(QWidget* parent);
    ~ServerView() override;

private:

};

#endif // SERVERVIEW_H
