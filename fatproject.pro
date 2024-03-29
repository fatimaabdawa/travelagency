QT       += core gui sql
QT       += core gui network
QT       += core gui network sql printsupport serialport charts \
            multimedia multimediawidgets
QT += multimedia
QT+=serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    connexion.cpp \
    evenemant.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    prromtion.cpp \
    qcustomplot.cpp \
    smtp.cpp \
    statistique.cpp

HEADERS += \
    arduino.h \
    connexion.h \
    evenemant.h \
    login.h \
    mainwindow.h \
    prromtion.h \
    qcustomplot.h \
    smtp.h \
    statistique.h

FORMS += \
    capteur.ui \
    login.ui \
    mainwindow.ui \
    statistique.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    fatima.qrc

DISTFILES += \
    ../../../Pictures/Camera Roll/206005-OZQ0RM-390.jpg
