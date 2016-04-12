#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include <QtWidgets/QWidget>

class QTimeLine;

class NotificationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NotificationWidget(QString title, QString message, QPixmap icon = QPixmap());
    ~NotificationWidget();

    bool fading() const;
    void setFading(bool fading);

protected:
    void showEvent(QShowEvent *ev) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
    void setVisible(bool visible) Q_DECL_OVERRIDE;

private slots:
    void faderValueChanged(qreal value);
    void faderFinished();

signals:
    void deleted();
    void clicked();

private:
    QTimer *m_timeout;
    QTimeLine *m_fader;
    bool m_fading;
};


#endif // NOTIFICATIONWIDGET_H
