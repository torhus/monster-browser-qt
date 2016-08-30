#include "common.h"
#include <QApplication>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>


static QtMessageHandler defaultMessageHandler;
static QFile* logFile;


static void customMessageHandler(QtMsgType type,
                                 const QMessageLogContext &context,
                                 const QString &msg)
{
    switch (type) {
        case QtDebugMsg:
        case QtInfoMsg:
        case QtWarningMsg:
        case QtCriticalMsg:
        case QtFatalMsg:
            logFile->write(msg.toLocal8Bit());
            logFile->write("\n");
            break;
    }
    defaultMessageHandler(type, context, msg);
}



void initLogging()
{
    logFile = new QFile("LOG.TXT");
    // https://bugreports.qt.io/browse/QTBUG-14809
    QIODevice::OpenMode mode = QIODevice::Text | QIODevice::Unbuffered;

    // Stop the file from growing indefinitely.
    if (QFileInfo(logFile->fileName()).size() > (100 * 1024))
        mode |= QIODevice::WriteOnly;
    else
        mode |= QIODevice::Append;

    if (!logFile->open(mode)) {
        QMessageBox::warning(0, "Warning", "Unable to open log file.");
        delete logFile;
        logFile = nullptr;
    }
    else {
        const char* sep =
               "-------------------------------------------------------------";
        QTextStream out(logFile);

        out << "\n" << sep << "\n" << qApp->applicationDisplayName();
        out << " started at ";
        out << QDateTime::currentDateTime().toString(Qt::ISODate) << "\n";
        out << sep << endl;

        defaultMessageHandler = qInstallMessageHandler(customMessageHandler);
    }
}


void shutDownLogging()
{
    qInstallMessageHandler(0);
    delete logFile;
}
