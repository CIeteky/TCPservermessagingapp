QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    clienthandler.cpp \
    main.cpp \
    mainwindow.cpp \
    clienthandler.cpp
 

HEADERS += \
    clienthandler.h \
    mainwindow.h \
    clienthandler.h 
FORMS += \
    mainwindow.ui 


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
