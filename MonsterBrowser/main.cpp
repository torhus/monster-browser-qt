#include "mainwindow.h"
#include "masterlist.h"
#include "serveractions.h"
#include "servermodel.h"
#include "serverview.h"
#include <QApplication>




void shutdownHandler()
{
    qInfo("Shutting down...");
}



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Monster Browser");
    app.setApplicationVersion("Qt");
    app.setApplicationDisplayName(app.applicationName() + " " +
                                  app.applicationVersion());

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
