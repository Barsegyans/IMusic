#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T16:27:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IMusic
TEMPLATE = app

SOURCES += main.cpp\
    mainwindow.cpp \
    item.cpp \
    album.cpp \
    artist.cpp \
    track.cpp \
    musicmodel.cpp \
    ratingdelegate.cpp \
    ratingwidget.cpp \
    albumdialog.cpp \
    artisdialog.cpp \

HEADERS  += mainwindow.h \
    item.h \
    album.h \
    artist.h \
    track.h \
    musicmodel.h \
    ratingdelegate.h \
    ratingwidget.h \
    albumdialog.h \
    artistdialog.h \


FORMS    += mainwindow.ui \
    albumdialog.ui \
    artistdialog.ui \

RESOURCES += \
    rs.qrc
