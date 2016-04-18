#-------------------------------------------------
#
# Project created by QtCreator 2015-12-07T21:01:55
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    ../src/configparser.h \
    ../src/controlkey.h \
    ../src/controller.h \
    ../src/macplatform.h \
    ../src/platform.h \
    ../src/vector2f.h \
    ../src/windowsplatform.h \
    ../src/x11platform.h \
    mainwindow.h \
    qdebugstream.h

SOURCES += \
    ../src/configparser.cpp \
    ../src/controlkey.cpp \
    ../src/controller.cpp \
    ../src/macplatform.cpp \
    ../src/platform.cpp \
    ../src/vector2f.cpp \
    ../src/windowsplatform.cpp \
    ../src/x11platform.cpp \
    main.cpp \
    mainwindow.cpp

TARGET = ControlKey-GUI
TEMPLATE = app
FORMS += mainwindow.ui

DESTDIR = ../app
CONFIG += c++11

unix {
LIBS += -lX11 -lXtst -lSDL2main -lSDL2
}

win32 {
LIBS += -lSDL2main -lSDL2
}
