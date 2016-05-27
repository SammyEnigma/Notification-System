#include <QApplication>
#include "notificationwidget.h"
#include "notificationmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    NotificationWidget *w = new NotificationWidget(QString("Title"), QString("Message"), QPixmap());
//    QObject::connect(w, &NotificationWidget::finished, w, &NotificationWidget::deleteLater);
//    QObject::connect(w, &NotificationWidget::finished, &app, &QApplication::quit);
//    w->show();

    NotificationManager *m = new NotificationManager();
    m->showNotification(QString("Title"), QString("Message"), QPixmap());

    return app.exec();
}
