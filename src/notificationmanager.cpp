#include "notificationmanager.h"
#include "notificationwidget.h"

NotificationManager::NotificationManager(uint maxWidgets) :
    m_maxWidgets(maxWidgets),
    m_widgets(new QList<NotificationWidget*>())
{

}

NotificationManager::~NotificationManager()
{
    while (!m_widgets->isEmpty()) {
        NotificationWidget *obj = m_widgets->takeFirst();
        delete obj;
        obj = Q_NULLPTR;
    }
    delete m_widgets;
    m_widgets = Q_NULLPTR;
}

uint NotificationManager::maxWidgets() const
{
    return m_maxWidgets;
}

void NotificationManager::setMaxWidgets(const uint &maxWidgets)
{
    m_maxWidgets = maxWidgets;
}
