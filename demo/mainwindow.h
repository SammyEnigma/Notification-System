#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class NotificationManager;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private Q_SLOTS:
    void clickButton();

private:
    NotificationManager *m_manager;
    int number;
};

#endif // MAINWINDOW_H
