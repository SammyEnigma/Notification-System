#include <QApplication>
#include "notificationwidget.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    NotificationWidget *w = new NotificationWidget(QString("Title"), QString("Message"), QPixmap());

    w->deleteLater();
    return app.exec();
}
