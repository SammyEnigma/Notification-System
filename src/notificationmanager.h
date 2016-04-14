#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QObject>

class NotificationWidget;

class NotificationManager : public QObject
{
    Q_OBJECT
public:
    explicit NotificationManager();
    ~NotificationManager();

    void showNotification(QString title, QString message, QPixmap icon = QPixmap());

    uint maxWidgets() const;
    void setMaxWidgets(const uint &maxWidgets);

private:
    uint m_maxWidgets;
    QList<NotificationWidget*> *m_widgets;
};

#endif // NOTIFICATIONMANAGER_H
