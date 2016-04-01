#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include <QtWidgets/QWidget>

class QTimeLine;

class NotificationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NotificationWidget(QString title, QString message, QPixmap icon = QPixmap());
    ~NotificationWidget();

protected:
    void showEvent(QShowEvent *ev) Q_DECL_OVERRIDE;

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
