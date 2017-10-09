#-------------------------------------------------
#
# Project created by QtCreator 2016-03-28T13:21:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRCode_Generator
TEMPLATE = app

RC_ICONS = image/my_icon.ico

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

include(QRCode/QRCode.pri)
