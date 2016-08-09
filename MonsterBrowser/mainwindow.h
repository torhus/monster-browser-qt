#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "serverview.h"
#include <QMainWindow>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private:
    ServerView* serverView_;
};

#endif // MAINWINDOW_H
