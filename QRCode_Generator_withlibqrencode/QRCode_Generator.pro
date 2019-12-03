#-------------------------------------------------
#
# Project created by QtCreator 2016-03-28T13:21:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRCode_Generator
TEMPLATE = app

CONFIG(debug, debug|release){
    DEFINES += DEBUG_LOGOUT_ON
    message("Debug Build")
}

CONFIG(release, debug|release){
    message("Release Build")
}

RC_ICONS = image/my_icon.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    generator/qrcode_generator.cpp

HEADERS  += mainwindow.h \
        libs_inc/qrencode.h \
    generator/qrcode_generator.h

INCLUDEPATH += libs_inc \
        generator

unix:{
	LIBS += -L../libs/linux/
    LIBS += -lqrencode
}
win32:{
	LIBS += -L../libs/win/x64/
}

FORMS    += mainwindow.ui

