#-------------------------------------------------
#
# Project created by QtCreator 2018-11-13T17:51:15
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGLView
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

QMAKE_CXX = g++

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11


SOURCES += \
        main.cpp \
        openglmainwindow.cpp \
    openglview.cpp \
    Primitivies/shaderdata.cpp \
    Primitivies/shadergenerator.cpp

HEADERS += \
        openglmainwindow.h \
    openglview.h \
    Math \
    Primitivies \
    Math/vector3d.h \
    Primitivies/vertex.h \
    Primitivies/shaderdata.h \
    Math/vector3d.h \
    Primitivies/shaderdata.h \
    Primitivies/vertex.h \
    Primitivies/shadergenerator.h

FORMS += \
        openglmainwindow.ui

## Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

