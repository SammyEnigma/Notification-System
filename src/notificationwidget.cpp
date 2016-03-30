#include "notificationwidget.h"
#include <QTimer>

NotificationWidget::NotificationWidget(QWidget *parent, QPixmap icon, QString msg) : QWidget(parent)
{
    Q_UNUSED(icon)
    Q_UNUSED(msg)

    m_timeout = new QTimer(this);
    connect(m_timeout, &QTimer::timeout, this, &NotificationWidget::fadeAway);
    m_timeout->start(3000);
}

void NotificationWidget::fadeAway()
{

}
