#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "serverview.h"
#include "maintoolbar.h"
#include <QMainWindow>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private:
    ServerView* serverView_;
    MainToolBar* toolBar_;
};

extern ServerView* serverView;

#endif // MAINWINDOW_H
