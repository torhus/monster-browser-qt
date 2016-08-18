#include "mainwindow.h"
#include "serverview.h"
#include <QGridLayout>


ServerView* serverView;


MainWindow::MainWindow()
    : QMainWindow(0)
{
    resize(800, 600);

    auto centralWidget = new QWidget(this);
    auto mainLayout = new QGridLayout(centralWidget);
    serverView_ = new ServerView(centralWidget);
    serverView = serverView_;
    mainLayout->addWidget(serverView_, 0, 0);
    setCentralWidget(centralWidget);

    toolBar_ = new MainToolBar(this);
    addToolBar(toolBar_);
}

MainWindow::~MainWindow()
{

}
