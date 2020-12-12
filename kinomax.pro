QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addmovie.cpp \
    catigories.cpp \
    halls.cpp \
    main.cpp \
    mainwindow.cpp \
    movies.cpp \
    autorization.cpp \
    multiplier.cpp \
    seats.cpp

HEADERS += \
    addmovie.h \
    catigories.h \
    halls.h \
   mainwindow.h \
    movies.h \
    autorization.h \
    multiplier.h \
    seats.h

FORMS += \
    addmovie.ui \
    catigories.ui \
    halls.ui \
    mainwindow.ui \
    movies.ui \
    autorization.ui \
    multiplier.ui \
    seats.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
