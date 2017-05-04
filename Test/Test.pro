#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:02:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app

INCLUDEPATH += res/window/headers


SOURCES += \
    res/drawable/container.cpp \
    res/util/camera.cpp \
    res/util/input.cpp \
    res/window/modules/main.cpp \
    res/window/modules/mainwindow.cpp \
    res/window/modules/oglwidget.cpp \
    res/drawable/abstractDrawable.cpp \
    res/drawable/skybox.cpp \
    res/drawable/unitcube.cpp \
    res/drawable/floor.cpp
    res/drawable/container.cpp
    res/util/camera.cpp
    res/util/input.cpp
    res/window/modules/main.cpp
    res/window/modules/mainwindow.cpp
    res/window/modules/oglwidget.cpp

HEADERS  += \
    res/util/cachedvalue.h \
    res/util/cachedvalue.hpp \
    res/util/camera.h \
    res/util/input.h \
    res/window/headers/mainwindow.h \
    res/window/headers/oglwidget.h \
    res/drawable/header/abstractDrawable.h \
    res/drawable/header/abstractContainer.h \
    res/drawable/header/skybox.h \
    res/drawable/header/unitcube.h \
    res/drawable/header/floor.h
    res/drawable/container.h
    res/drawable/drawable.h
    res/util/cachedvalue.h
    res/util/cachedvalue.hpp
    res/util/camera.h
    res/util/input.h
    res/window/headers/mainwindow.h
    res/window/headers/oglwidget.h

FORMS    += \
    res/window/ui/mainwindow.ui

DISTFILES += \
    data/cube/fragmentshader.fsh \
    data/cube/vertexshader.vsh \
    data/vertexshader.vsh
