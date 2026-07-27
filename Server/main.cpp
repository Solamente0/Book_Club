#include <QApplication>
#include <QDebug>
#include "Database.h"
#include "network/Server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // تنظیم اطلاعات اپلیکیشن
    QApplication::setApplicationName("BookClub Server");
    QApplication::setApplicationVersion("1.0");

    QObject::connect(&Server::instance(), &Server::logMessage,
                      [](const QString &message) { qInfo().noquote() << message; });

    if (!Server::instance().startServer()) {
        qCritical() << "Failed to start BookClub server.";
        return 1;
    }

    return a.exec();
}
