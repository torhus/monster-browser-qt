#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Monster Browser");
    a.setApplicationVersion("Qt");
    a.setApplicationDisplayName(a.applicationName() + " " +
                                a.applicationVersion());

    MainWindow w;
    w.show();

    return a.exec();
}
