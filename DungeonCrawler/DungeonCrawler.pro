TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        abstractcontroller.cpp \
        abstractui.cpp \
        active.cpp \
        character.cpp \
        door.cpp \
        dungeoncrawler.cpp \
        floor.cpp \
        level.cpp \
        main.cpp \
        passive.cpp \
        pit.cpp \
        portal.cpp \
        ramp.cpp \
        switch.cpp \
        terminalui.cpp \
        tile.cpp \
        wall.cpp

HEADERS += \
    abstractcontroller.h \
    abstractui.h \
    active.h \
    character.h \
    door.h \
    dungeoncrawler.h \
    floor.h \
    level.h \
    passive.h \
    pit.h \
    portal.h \
    ramp.h \
    switch.h \
    terminalui.h \
    tile.h \
    wall.h
