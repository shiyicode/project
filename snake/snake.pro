#-------------------------------------------------
#
# Project created by QtCreator 2016-04-03T15:42:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    board.cpp \
    snake.cpp

HEADERS  += mainwindow.h \
    board.h \
    snake.h

FORMS    +=

DISTFILES += \
    block.txt
