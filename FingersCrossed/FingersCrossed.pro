QT       += core gui sql network printsupport multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
LIB+= C:\Users\Haboub\Documents\build-FingersCrossed-Desktop_Qt_5_13_1_MinGW_32_bit-Debug\debug\libcrypto-1_1.dll
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connexion.cpp \
    destination.cpp \
    hotel.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    notification.cpp \
    qcustomplot.cpp \
    smtp.cpp \
    statistique.cpp

HEADERS += \
    connexion.h \
    destination.h \
    hotel.h \
    login.h \
    mainwindow.h \
    notification.h \
    qcustomplot.h \
    smtp.h \
    statistique.h

FORMS += \
    login.ui \
    mainwindow.ui \
    statistique.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc
