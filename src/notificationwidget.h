#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include <QtWidgets/QWidget>

class NotificationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NotificationWidget(QPixmap icon, QString msg, QWidget *parent = 0);
    ~NotificationWidget();

private:
    QTimer *m_timeout;

private slots:
    void fadeAway();


signals:
    void deleted();
    void clicked();
};


#endif // NOTIFICATIONWIDGET_H
