#-------------------------------------------------
#
# Project created by QtCreator 2018-11-18T20:26:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRCODE_QT
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
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

INCLUDEPATH +=$$PWD/opencv4.0_dev_build_mingw32/include

LIBS += -L$$PWD/opencv4.0_dev_build_mingw32/x86/mingw/lib -lopencv_calib3d400.dll  -lopencv_core400.dll  -lopencv_highgui400.dll -lopencv_imgproc400.dll -lopencv_objdetect400.dll -lopencv_imgcodecs400.dll -lopencv_video400.dll -lopencv_videoio400.dll
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
