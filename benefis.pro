greaterThan(QT_MAJOR_VERSION, 4) {
QT += widgets network
DEFINES += HAVE_QT5
} else {
QT += core gui network qt3support xml
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
#   disrep.cpp

HEADERS  += mainwindow.h \
    chdialog.h \
    crdialog.h \
    radialog.h \
    rtdialog.h \
    version.rc \
#   disrep.h

FORMS    += mainwindow.ui \
    chdialog.ui \
    crdialog.ui \
    radialog.ui \
    rtdialog.ui

RESOURCES += images.qrc
win32:RC_FILE += version.rc

#INCLUDEPATH += ../../include/
#INCLUDEPATH += ../../icore/

