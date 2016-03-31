#include <QApplication>
#include "..\src\notificationwidget.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    NotificationWidget *w = new NotificationWidget(QPixmap(), QString("Test string"), 0);

    w->deleteLater();
    return app.exec();
}
