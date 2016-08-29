#-------------------------------------------------
#
# Project created by QtCreator 2016-08-24T20:59:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShowVideo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    trackingmethods.cpp \
    methods3d.cpp

HEADERS  += mainwindow.h \
    player.h \
    trackingmethods.h \
    methods3d.h

FORMS    += mainwindow.ui


INCLUDEPATH += D:\OpenCV\opencv\build\include

LIBS +=-LD:\OpenCV\opencv\build\x86\vc12\lib\
    -lopencv_calib3d2413 \
    -lopencv_contrib2413 \
    -lopencv_core2413 \
    -lopencv_features2d2413 \
    -lopencv_flann2413 \
    -lopencv_gpu2413 \
    -lopencv_highgui2413 \
    -lopencv_imgproc2413 \
    -lopencv_legacy2413 \
    -lopencv_ml2413 \
    -lopencv_nonfree2413 \
    -lopencv_objdetect2413 \
    -lopencv_ocl2413 \
    -lopencv_photo2413 \
    -lopencv_stitching2413 \
    -lopencv_superres2413 \
    -lopencv_ts2413 \
    -lopencv_video2413 \
    -lopencv_videostab2413
