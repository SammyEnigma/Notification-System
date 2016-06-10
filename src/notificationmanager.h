#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QObject>
#include <QPixmap>

class NotificationWidget;

class NotificationManager : public QObject
{
    Q_OBJECT
public:
    explicit NotificationManager();
    ~NotificationManager();

    void showNotification(NotificationWidget * const widget);

    uint maxWidgets() const;
    void setMaxWidgets(const uint &maxWidgets);

    QSize widgetSize() const;
    void setWidgetSize(const QSize &widgetSize);

    QEasingCurve curve() const;
    void setCurve(const QEasingCurve &curve);

private slots:
    void removeWidget();
    void updateWidgetsPosition();

private:
    uint m_maxWidgets;
    QList<NotificationWidget*> *m_widgets;
    int m_zoom;
    QSize m_widgetSize; // the size of shown widgets
    QPoint m_position;  // position on the desktop where the first widget will appear
    int m_offset;       // offset on Oy axis for a new widget position
    QEasingCurve m_curve;
};

#endif // NOTIFICATIONMANAGER_H
