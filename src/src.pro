QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
CONFIG += staticlib c++11
TARGET = Notification


SOURCES += \
    notificationwidget.cpp \
    notificationmanager.cpp

HEADERS += \
    notificationwidget.h \
    notificationmanager.h


