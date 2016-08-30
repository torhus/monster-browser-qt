#include "mainwindow.h"
#include "common.h"
#include "masterlist.h"
#include "serveractions.h"
#include "servermodel.h"
#include "serverview.h"
#include <QApplication>


static MainWindow* mainWindow;


void setAppName()
{
    qApp->setApplicationName("Monster Browser");
    qApp->setApplicationVersion("Qt");
    QString fullAppName(qApp->applicationName() + " " +
                        qApp->applicationVersion());

#ifdef QT_NO_DEBUG
    qApp->setApplicationDisplayName(fullAppName);
#else
    qApp->setApplicationDisplayName(QString("%1 %2 (rev. %3) *DEBUG BUILD*")
                                    .arg(fullAppName).arg(__DATE__)
                                    .arg(REVISION));
#endif

}


void shutdownHandler()
{
    qInfo("Shutting down...");

    delete mainWindow;
    delete serverActions;

    shutDownLogging();
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    setAppName();

    /* QApplication.exec does not always return, so we can't place shutdown
     * code after it in main, and we can't rely on destructors for local
     * objects in main, nor for statically allocated objects being called
     * automatically. This seems to be the offical way to deal with the issue.
     */
    QObject::connect(&app, &QApplication::aboutToQuit, shutdownHandler);

    initLogging();

    serverActions = new ServerActions;

    mainWindow = new MainWindow;
    mainWindow->show();

    // Testing.
    MasterList master("master.smokin-guns.org");
    master.load("68");
    serverView->setModel(new ServerModel(&master));

    return app.exec();
}
