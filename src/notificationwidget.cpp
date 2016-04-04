#include "notificationwidget.h"
#include <QTimer>
#include <QTimeLine>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScreen>
#include <QApplication>
#include <QLabel>

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
    displayWidget->setStyleSheet(".QWidget{ background-color: rgba(0, 0, 0, 75%); }");

    // 96 pixels = 1 logical inch. The standart DPI settings 100% (96 DPI)
    int zoom_app = qApp->primaryScreen()->logicalDotsPerInch() / 96.0;
    zoom_app /= devicePixelRatio();

    QLabel *icon_ = new QLabel;
    icon_->setPixmap(icon);
    icon_->setMaximumSize(32 * zoom_app, 32 * zoom_app);

    QLabel *title_ = new QLabel(title);
    title_->setMaximumSize(255 * zoom_app, 50 * zoom_app);
    title_->setWordWrap(true);
    //title_->setText(title);

    QLabel *message_ = new QLabel(message);
    message_->setMaximumSize(255 * zoom_app, 100 * zoom_app);
    message_->setWordWrap(true);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(icon_);

    QVBoxLayout *textLayout = new QVBoxLayout;
    textLayout->addWidget(title_);
    textLayout->addWidget(message_);

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

void NotificationWidget::fadeOut()
{
    this->hide();
    emit deleted();
    this->deleteLater();
}
