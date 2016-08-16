#include "mainwindow.h"
#include "serveractions.h"
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

    return a.exec();
}
