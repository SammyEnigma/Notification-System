#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include <QtWidgets/QWidget>

class QTimeLine;

class NotificationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NotificationWidget(QPixmap icon, QString msg, QWidget *parent = 0);
    ~NotificationWidget();

protected:
    void showEvent(QShowEvent *ev);

private slots:
    void fadeOut();

signals:
    void deleted();
    void clicked();

private:
    QTimer *m_timeout;
    QTimeLine *m_fader;
};


#endif // NOTIFICATIONWIDGET_H
