#include "notificationwidget.h"
#include <QTimer>
#include <QTimeLine>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QFile>
#include <QDebug>

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
    setCursor(QCursor(Qt::PointingHandCursor));

    QWidget *displayWidget = new QWidget;
    displayWidget->setGeometry(0, 0, this->width(), this->height());
    displayWidget->setStyleSheet(".QWidget { "
                                    "background-color: rgba(0, 0, 0, 75%); "
                                    "border-width: 1pt;"
                                    "border-style: solid;"
                                    "border-radius: 10pt;"
                                    "border-color: #555555; }"
                                 ".QWidget:hover { "
                                    "background-color: rgba(68, 68, 68, 75%);"
                                    "border-width: 2pt;"
                                    "border-style: solid;"
                                    "border-radius: 10pt;"
                                    "border-color: #ffffff; }");

    // 96 pixels = 1 logical inch. The standart DPI settings 100% (96 DPI)
    int zoom = qApp->primaryScreen()->logicalDotsPerInch() / 96.0;
    zoom /= devicePixelRatio();

    QLabel *icon_ = new QLabel;
    icon_->setPixmap(icon);
    icon_->setMaximumSize(32 * zoom, 32 * zoom);

    QLabel *header = new QLabel(title);
    header->setMaximumSize(255 * zoom, 50 * zoom);
    header->setWordWrap(true);
    header->setStyleSheet("QLabel { "
                            "color: #ffffff;"
                            "font-weight: bold;"
                            "font-size: 12pt; }");

    QLabel *body = new QLabel(message);
    body->setMaximumSize(255 * zoom, 100 * zoom);
    body->setWordWrap(true);
    body->setStyleSheet("QLabel { "
                            "color: #ffffff;"
                            "font-size: 10pt; }");

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(icon_);

    QVBoxLayout *textLayout = new QVBoxLayout;
    textLayout->addWidget(header);
    textLayout->addWidget(body);

    mainLayout->addLayout(textLayout);
    displayWidget->setLayout(mainLayout);

    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(displayWidget);
    setLayout(container);

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

void NotificationWidget::mousePressEvent(QMouseEvent *ev)
{
    emit clicked();
    QWidget::mousePressEvent(ev);
}

void NotificationWidget::fadeOut()
{
    this->hide();
    emit deleted();
    this->deleteLater();
}
