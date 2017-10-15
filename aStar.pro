TEMPLATE = app
CONFIG += console
CONFIG +=C++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    cgraphics.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    cgraphics.h

