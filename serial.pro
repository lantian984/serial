#-------------------------------------------------
#
# Project created by QtCreator 2020-09-13T11:35:12
#
#-------------------------------------------------

QT       += core gui
QT += serialport
QT += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serial
TEMPLATE = app

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
        Buffer/plotdatapack.cpp \
        Gui/plotgui.cpp \
        Gui/serialgui.cpp \
        SerialTool/serialtool.cpp \
        main.cpp \
        Gui\maingui.cpp \
        Buffer\serialdatapata.cpp \
        Json\json.cpp

HEADERS += \
    Buffer/plotdatapack.h \
    Gui/plotgui.h \
        Gui/serialgui.h \
        Gui\maingui.h \ \
    SerialTool/serialtool.h \
    Buffer\serialdatapata.h \
    Json\json.h


FORMS += \
    Gui/plotgui.ui \
        Gui/serialgui.ui \
        Gui\maingui.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
