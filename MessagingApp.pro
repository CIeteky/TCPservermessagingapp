QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    clienthandler.cpp \
    main.cpp \
    mainwindow.cpp \
    clienthandler.cpp \
    messagingclient.cpp

HEADERS += \
    clienthandler.h \
    mainwindow.h \
    clienthandler.h \
    messagingclient.h

FORMS += \
    mainwindow.ui \
    messagingclient.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
