#-------------------------------------------------
#
# Project created by QtCreator 2021-04-12T16:20:25
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UAVCS
TEMPLATE = app

SOURCES += main.cpp\
    Src/FileThread.cpp \
    Src/Jsonwrite.cpp \
    Src/MainThread.cpp \
    Src/MainWidget.cpp \
    Src/MapDataThread.cpp \
    Src/MapForm.cpp \
    Src/MapThread.cpp \
    Src/guess.cpp \
    Src/mapwidget.cpp \
    Src/SettingWidget.cpp \
    Src/RecThread.cpp \
    Src/mouthread.cpp \
    Src/mysm.cpp \
    Src/showtrack.cpp \
    Src/AirThread.cpp \
    Src/GetData.cpp \
    Src/GetVedio.cpp \
    Include/dist/jsoncpp.cpp

HEADERS  += \
    Include/AirThread.h\
    Include/FileThread.h \
    Include/GetData.h \
    Include/GetVedio.h \
    Include/Jsonwrite.h \
    Include/MainThread.h \
    Include/MainWidget.h \
    Include/MapDataThread.h \
    Include/MapForm.h \
    Include/MapThread.h \
    Include/SettingWidget.h \
    Include/guess.h \
    Include/mouthread.h \
    Include/mysm.h \ 
    Include/showtrack.h \
    Include/signals.h \
    Include/jsonwrite.h \
    Include/mapwidget.h \
    Include/RecThread.h \   
    Include/dist/json/json.h \
    Include/dist/json/json-forwards.h

FORMS    += \
    UI/MainWidget.ui \
    UI/MapForm.ui \
    UI/SettingWidget.ui

DISTFILES += \
    Image/show.png \
    Resource/map.jpg \
    Resource/5d7164056c089314f72168bdb82e30f9.jpeg \
    Resource/6a6c8d407ccbfa3c5f5f44b79e82622a.jpeg \
    Resource/7cee96267c17b3999cfe981baced3bdb.jpeg \
    Resource/71f5cec2353e90579bc6aa80529adf0b.jpeg \
    Resource/af5f9b6c517d868a22c10be4cf2785d9.jpeg \
    Resource/c87e87f57a8ab85608723ad6684da32c.jpg

INCLUDEPATH += C:\Qt\Qt5.12.4\5.12.4\mingw73_32\include\CSSC\
               D:\opencv\OpenCV-MinGW-Build-OpenCV-4.5.0-with-contrib\OpenCV-MinGW-Build-OpenCV-4.5.0-with-contrib\include


LIBS += C:\Qt\Qt5.12.4\5.12.4\mingw73_32\lib\libCSSCDesignerPlugin.a\
        D:\opencv\OpenCV-MinGW-Build-OpenCV-4.5.0-with-contrib\OpenCV-MinGW-Build-OpenCV-4.5.0-with-contrib\x64\mingw\lib\libopencv*.a

RESOURCES += \
    res.qrc


win32: LIBS += -L$$PWD/../ZMQ/test_wy_lib/lib/ -lzmq

INCLUDEPATH += $$PWD/../ZMQ/test_wy_lib/include
DEPENDPATH += $$PWD/../ZMQ/test_wy_lib/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../ZMQ/test_wy_lib/lib/zmq.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../ZMQ/test_wy_lib/lib/libzmq.a

CONFIG += resources_big

#Release禁止输出qWarning/qDebug信息
#CONFIG (release, debug|release) {
#DEFINES += QT_NO_WARNING_OUTPUT
#DEFINES += QT_NO_DEBUG_OUTPUT
#}

#CONFIG += console
