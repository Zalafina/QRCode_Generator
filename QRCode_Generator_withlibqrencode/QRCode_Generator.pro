#-------------------------------------------------
#
# Project created by QtCreator 2016-03-28T13:21:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    TARGET_ARCH=$${QT_ARCH}
} else {
    TARGET_ARCH=$${QMAKE_HOST.arch}
}

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

linux-g++-64 {
    LIBS += -L../libs/linux/x64/
    LIBS += -lqrencode
}
win32-msvc {
    contains(TARGET_ARCH, x86_64) {
        ARCHITECTURE = x64
        LIBS += -L../libs/win/x64/
    } else {
        ARCHITECTURE = x86
        LIBS += -L../libs/win/x86/
    }
    message("ARCHITECTURE="$$ARCHITECTURE)
}

FORMS    += mainwindow.ui

