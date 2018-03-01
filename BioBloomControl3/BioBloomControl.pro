#-------------------------------------------------
#
# Project created by QtCreator 2018-02-20T04:48:50
#
#-------------------------------------------------

QT       += core gui
QT       += charts
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BioBloomControl
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    biobloomunit.cpp \
    unitwindow.cpp \
    musicwindow.cpp \
    unitribbon.cpp \
    settingswindow.cpp \
    dataribbon.cpp \
    chart.cpp \
    graphdisplay.cpp \
    plantprofile.cpp \
    configurewindow.cpp

HEADERS += \
        mainwindow.h \
    biobloomunit.h \
    unitwindow.h \
    musicwindow.h \
    unitribbon.h \
    settingswindow.h \
    dataribbon.h \
    chart.h \
    graphdisplay.h \
    plantprofile.h \
    configurewindow.h

FORMS += \
        mainwindow.ui \
    unitwindow.ui \
    musicwindow.ui \
    unitribbon.ui \
    settingswindow.ui \
    dataribbon.ui \
    configurewindow.ui

RESOURCES += \
    Resources/biobloom.qrc
