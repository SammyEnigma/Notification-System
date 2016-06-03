#include "mainwindow.h"
#include "notificationmanager.h"
#include "notificationwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_manager(new NotificationManager),
    number(0)
{
    setupUi(this);

    connect(pushButton, &QPushButton::clicked, this, &MainWindow::clickButton);
}

void MainWindow::clickButton()
{
    m_manager->showNotification(new NotificationWidget("Title", QString::number(number++)));
}
