#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include <QtWidgets/QWidget>

class NotificationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NotificationWidget(QWidget *parent = 0, QPixmap icon, QString msg);

private:
    QTimer *m_timeout;

private slots:
    void fadeAway();


signals:
    void deleted();
    void clicked();
};

#endif // NOTIFICATIONWIDGET_H
