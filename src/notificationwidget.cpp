#include "notificationwidget.h"
#include <QTimer>

NotificationWidget::NotificationWidget(QPixmap icon, QString msg, QWidget *parent) : QWidget(parent)
{
    Q_UNUSED(icon)
    Q_UNUSED(msg)

    m_timeout = new QTimer(this);
    connect(m_timeout, &QTimer::timeout, this, &NotificationWidget::fadeAway);
    m_timeout->start(3000);
}

NotificationWidget::~NotificationWidget()
{
    if (m_timeout->isActive())
        m_timeout->stop();

    delete m_timeout;
    m_timeout = Q_NULLPTR;
}

void NotificationWidget::fadeOut()
{
    this->hide();
    emit deleted();
    this->deleteLater();
}
