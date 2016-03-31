#include "notificationwidget.h"
#include <QTimer>
#include <QTimeLine>

NotificationWidget::NotificationWidget(QPixmap icon, QString msg, QWidget *parent)
    : QWidget(parent),
      m_timeout(new QTimer(this)),
      m_fader(new QTimeLine(300, this))
{
    Q_UNUSED(icon)
    Q_UNUSED(msg)

    connect(m_timeout, &QTimer::timeout, this, &NotificationWidget::fadeOut);
    m_timeout->start(3000);
}

NotificationWidget::~NotificationWidget()
{
    if (m_timeout->isActive())
        m_timeout->stop();

    delete m_timeout;
    m_timeout = Q_NULLPTR;
}

void NotificationWidget::showEvent(QShowEvent *ev)
{
    QWidget::showEvent(ev);
}

void NotificationWidget::fadeOut()
{
    this->hide();
    emit deleted();
    this->deleteLater();
}
