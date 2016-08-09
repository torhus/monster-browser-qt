#include "mainwindow.h"
#include "serverview.h"
#include <QGridLayout>


MainWindow::MainWindow()
    : QMainWindow(0)
{
    resize(800, 600);

    auto centralWidget = new QWidget(this);
    auto mainLayout = new QGridLayout(centralWidget);
    serverView_ = new ServerView(centralWidget);
    mainLayout->addWidget(serverView_, 0, 0);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{

}
