
QT       += core gui

CONFIG+=C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Minestorm_Game_by_NTuan
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controller.cpp \
    gameboard.cpp \
    game.cpp \
    minestormgame.cpp \
    spaceship.cpp \
    bullet.cpp \
    mine.cpp

HEADERS  += mainwindow.h \
    controller.h \
    gameboard.h \
    game.h \
    minestormgame.h \
    spaceship.h \
    bullet.h \
    mine.h

FORMS    +=

OTHER_FILES +=
