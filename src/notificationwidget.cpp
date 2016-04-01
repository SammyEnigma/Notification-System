#include "notificationwidget.h"
#include <QTimer>
#include <QTimeLine>
#include <QHBoxLayout>
#include <QScreen>
#include <QApplication>

NotificationWidget::NotificationWidget(QString title, QString message, QPixmap icon)
    : QWidget(0),
      m_timeout(new QTimer(this)),
      m_fader(new QTimeLine(300, this))
{
    Q_UNUSED(icon)
    Q_UNUSED(message)
    Q_UNUSED(title)

    setWindowFlags(Qt::Tool |
                   Qt::FramelessWindowHint |
                   Qt::WindowSystemMenuHint |
                   Qt::WindowStaysOnTopHint);

    setAttribute(Qt::WA_NoSystemBackground, true);
    // Do we really need attribute below? Or setting above just do it for us
    setAttribute(Qt::WA_TranslucentBackground, true);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QWidget *displayWidget = new QWidget;
    displayWidget->setGeometry(0, 0, this->width(), this->height());

    // 96 pixels = 1 logical inch. The standart DPI settings 100% (96 DPI)
    int zoom_app = qApp->primaryScreen()->logicalDotsPerInch() / 96.0;
    zoom_app /= devicePixelRatio();


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
