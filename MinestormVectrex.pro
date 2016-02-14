
QT       += core gui

CONFIG+=C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Minestorm_Game_by_NTuan
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    game/controller.cpp \
    game/game.cpp \
    game/gameboard.cpp \
    game/minestormgame.cpp \
    objects/bullet.cpp \
    objects/mine.cpp \
    objects/spaceship.cpp \
    objects/gameobject.cpp

HEADERS  += mainwindow.h \
    game/controller.h \
    game/game.h \
    game/gameboard.h \
    game/minestormgame.h \
    objects/bullet.h \
    objects/mine.h \
    objects/spaceship.h \
    objects/gameobject.h

FORMS    +=

OTHER_FILES +=

RESOURCES += \
    res.qrc
