#include "mainwindow.h"
#include "masterlist.h"
#include "serveractions.h"
#include "servermodel.h"
#include "serverview.h"
#include <QApplication>


void setAppName()
{
    qApp->setApplicationName("Monster Browser");
    qApp->setApplicationVersion("Qt");
    QString fullAppName(qApp->applicationName() + " " +
                        qApp->applicationVersion());

#ifdef DEBUG
    qApp->setApplicationDisplayName(QString("%1 %2 (rev. %3) *DEBUG BUILD*")
                                    .arg(fullAppName).arg(__DATE__)
                                    .arg(REVISION));
#elif
    qApp->setApplicationDisplayName(fullAppName);
#endif

}


void shutdownHandler()
{
    qInfo("Shutting down...");
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    setAppName();

    QObject::connect(&app, &QApplication::aboutToQuit, shutdownHandler);

    serverActions = new ServerActions;

    MainWindow w;
    w.show();

    // Testing.
    MasterList master("master.smokin-guns.org");
    master.load("68");
    serverView->setModel(new ServerModel(&master));

    return app.exec();
}
