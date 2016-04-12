#include "notificationwidget.h"
#include <QTimer>
#include <QTimeLine>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QDebug>

NotificationWidget::NotificationWidget(QString title, QString message, QPixmap icon)
    : QWidget(0),
      m_timeout(new QTimer(this)),
      m_fader(new QTimeLine(500, this)),
      m_fading(true)
{
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

    connect(m_timeout, &QTimer::timeout, this, &NotificationWidget::hide);

    connect(m_fader, &QTimeLine::valueChanged, this, &NotificationWidget::faderValueChanged);
    connect(m_fader, &QTimeLine::finished, this, &NotificationWidget::faderFinished);
}

NotificationWidget::~NotificationWidget()
{
    if (m_timeout->isActive())
        m_timeout->stop();
    delete m_timeout;
    m_timeout = Q_NULLPTR;

    if (m_fader->state() != QTimeLine::NotRunning)
        m_fader->stop();
    delete m_fader;
    m_fader = Q_NULLPTR;

    emit deleted();
}

void NotificationWidget::showEvent(QShowEvent *ev)
{
    setWindowOpacity( m_fading ? 0.0 : 1.0 );

    QWidget::showEvent(ev);

    if (m_fading) {
        m_fader->setDirection(QTimeLine::Forward);
        m_fader->start();
    } else {
        m_timeout->start(3000);
    }
}

void NotificationWidget::mousePressEvent(QMouseEvent *ev)
{
    emit clicked();
    QWidget::mousePressEvent(ev);
}

void NotificationWidget::setVisible(bool visible)
{
    qDebug() << Q_FUNC_INFO;
    if (!visible && m_fading && m_fader->direction() == QTimeLine::Forward) {   // Fading enabled visible false
        m_fader->setDirection(QTimeLine::Backward);
        m_fader->start();
    } else if (!visible) { // visible false - delete themselves
        this->deleteLater();
    } else {    // standart handler
        QWidget::setVisible(visible);
    }
}

void NotificationWidget::faderValueChanged(qreal value)
{
    setWindowOpacity(value);
}

void NotificationWidget::faderFinished()
{
    if (m_fader->direction() == QTimeLine::Forward)
        m_timeout->start(3000);     // starting timer after fader finish work and widget opacity is 1.0
    else
        this->deleteLater();        // In case of backward direction delete themselves
}

bool NotificationWidget::fading() const
{
    return m_fading;
}

void NotificationWidget::setFading(bool fading)
{
    m_fading = fading;
}
