#-------------------------------------------------
#
# Project created by QtCreator 2013-08-06T12:58:11
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4)
{
QT += widgets network
DEFINES += HAVE_QT5
}

#include(../../arms/superarm.pri)

TARGET = benefis
TEMPLATE = app
CONFIG += release

SOURCES += main.cpp\
        mainwindow.cpp \
    chdialog.cpp \
    crdialog.cpp \
    radialog.cpp \
    rtdialog.cpp \
    disrep.cpp

HEADERS  += mainwindow.h \
    chdialog.h \
    crdialog.h \
    radialog.h \
    rtdialog.h \
    version.rc \
    disrep.h

FORMS    += mainwindow.ui \
    chdialog.ui \
    crdialog.ui \
    radialog.ui \
    rtdialog.ui

RESOURCES += images.qrc
win32:RC_FILE += version.rc

INCLUDEPATH += ../../include/
INCLUDEPATH += ../../icore/

