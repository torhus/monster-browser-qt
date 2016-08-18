#include "mainwindow.h"
#include "masterlist.h"
#include "serveractions.h"
#include "servermodel.h"
#include "serverview.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Monster Browser");
    a.setApplicationVersion("Qt");
    a.setApplicationDisplayName(a.applicationName() + " " +
                                a.applicationVersion());

    // Create this global object here to give it correct lifetime.
    ServerActions sa;
    serverActions = &sa;

    MainWindow w;
    w.show();

    // Testing.
    MasterList master;
    master.load("68");
    serverView->setModel(new ServerModel(&master));

    return a.exec();
}
