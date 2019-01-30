#-------------------------------------------------
#
# Project created by QtCreator 2018-11-13T17:51:15
#
#-------------------------------------------------

#QT       += core gui core


QT += widgets
#TARGET = OpenGLView
#CONFIG += console
#CONFIG -= app_bundle
#TEMPLATE = app

CONFIG += c++11

SOURCES += \
        main.cpp \
        openglmainwindow.cpp \
    openglview.cpp \
    Math/transform3d.cpp \
    Math/perspectivematrix.cpp \
    Math/camera.cpp \
    Primitivies/axisShader.cpp \
    Math/orthomatrix.cpp \
    Primitivies/arrowShader.cpp \
    Primitivies/cubeShader.cpp \
    Primitivies/gridShader.cpp \
    Primitivies/shaderData.cpp \
    Primitivies/shaderGenerator.cpp \
    Primitivies/triangleShader.cpp \
    Primitivies/sphereShader.cpp

HEADERS += \
        openglmainwindow.h \
    openglview.h \
    Math \
    Primitivies \
    Math/vector3d.h \
    Primitivies/vertex.h \
    Math/vector3d.h \
    Primitivies/vertex.h \
    Primitivies/shaderGenerator.h \
    Math/transform3d.h \
    Math/perspectivematrix.h \
    Math/camera.h \
    Primitivies/axisShader.h \
    Math/orthomatrix.h \
    Primitivies/arrowShader.h \
    Primitivies/cubeShader.h \
    Primitivies/gridShader.h \
    Primitivies/shaderData.h \
    Primitivies/triangleShader.h \
    Primitivies/sphereShader.h

FORMS += \
        openglmainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

