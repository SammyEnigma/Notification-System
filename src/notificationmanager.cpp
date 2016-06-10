#include "notificationmanager.h"
#include "notificationwidget.h"
#include <QDebug>
#include <QApplication>
#include <QScreen>
#include <QDesktopWidget>
#include <QPropertyAnimation>

NotificationManager::NotificationManager() :
    m_maxWidgets(3),
    m_widgets(new QList<NotificationWidget*>()),
    m_offset(0),
    m_curve(QEasingCurve::InCubic)
{
    // 96 pixels = 1 logical inch. The standart DPI settings 100% (96 DPI)
    m_zoom = qApp->primaryScreen()->logicalDotsPerInch() / 96.0;
    m_zoom /= qApp->primaryScreen()->devicePixelRatio();
    QRect desktopRect = QApplication::desktop()->availableGeometry();

    m_widgetSize = QSize(255 * m_zoom, 100 * m_zoom);
    m_position = QPoint(desktopRect.width()  - m_widgetSize.width(),
                        desktopRect.height() - m_widgetSize.height());
}

NotificationManager::~NotificationManager()
{
    while (!m_widgets->isEmpty()) {
        NotificationWidget *obj = m_widgets->takeFirst();
        obj->deleteLater();
    }
    delete m_widgets;
    m_widgets = Q_NULLPTR;
}

void NotificationManager::showNotification(NotificationWidget * const widget)
{
    if (widget == Q_NULLPTR)
        return;

    m_offset = (m_widgets->count() > 0) ? m_offset - 100 * m_zoom : 0;
    widget->setMinimumSize(m_widgetSize);
    widget->setGeometry(m_position.x(), m_position.y() + m_offset,
                        m_widgetSize.width(), m_widgetSize.height());

    connect(widget, &NotificationWidget::finished, this, &NotificationManager::removeWidget);
    m_widgets->append(widget);

    widget->show();
}

uint NotificationManager::maxWidgets() const
{
    return m_maxWidgets;
}

void NotificationManager::setMaxWidgets(const uint &maxWidgets)
{
    m_maxWidgets = maxWidgets;
}

void NotificationManager::removeWidget()
{
    if (NotificationWidget *widget = qobject_cast<NotificationWidget*>(QObject::sender())) {
        int index = m_widgets->indexOf(widget);
        if (index > -1) {
           NotificationWidget *removed = m_widgets->takeAt(index);
           removed->deleteLater();

           updateWidgetsPosition();
        }
    } else {
        qDebug() << "Failed while casting from QObject* to NotificationWidget*";
    }
}

void NotificationManager::updateWidgetsPosition()
{
    m_offset = 0;
    for (auto it = m_widgets->begin(); it != m_widgets->end(); ++it) {
        QPropertyAnimation *animation = new QPropertyAnimation(*it, "pos");
        animation->setDuration(200);
        animation->setStartValue((*it)->pos());
        animation->setEndValue(QPoint(m_position.x(), m_position.y() + m_offset));
        animation->setEasingCurve(m_curve);
        animation->start();
        m_offset -= 100 * m_zoom;
    }
}

QEasingCurve NotificationManager::curve() const
{
    return m_curve;
}

void NotificationManager::setCurve(const QEasingCurve &curve)
{
    m_curve = curve;
}

QSize NotificationManager::widgetSize() const
{
    return m_widgetSize;
}

void NotificationManager::setWidgetSize(const QSize &widgetSize)
{
    m_widgetSize = widgetSize;
}
