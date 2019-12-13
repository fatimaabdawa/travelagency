QT +=  core gui sql network printsupport multimedia multimediawidgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    client.cpp \
    clientform.cpp \
    clientvip.cpp \
    connexion.cpp \
    contrat.cpp \
    destination.cpp \
    employe.cpp \
    employeform.cpp \
    evenemant.cpp \
    historique.cpp \
    hotel.cpp \
    integratedone.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    marketingform.cpp \
    notification.cpp \
    prromtion.cpp \
    qcustomplot.cpp \
    reserverhotel.cpp \
    reservervoyage.cpp \
    smtp.cpp \
    statclient.cpp \
    statistique.cpp \
    voyageform.cpp

HEADERS += \
    arduino.h \
    client.h \
    clientform.h \
    clientvip.h \
    connexion.h \
    contrat.h \
    destination.h \
    employe.h \
    employeform.h \
    evenemant.h \
    historique.h \
    hotel.h \
    integratedone.h \
    login.h \
    mainwindow.h \
    marketingform.h \
    notification.h \
    prromtion.h \
    qcustomplot.h \
    reserverhotel.h \
    reservervoyage.h \
    smtp.h \
    statclient.h \
    statistique.h \
    voyageform.h

FORMS += \
    clientform.ui \
    employeform.ui \
    integratedone.ui \
    login.ui \
    mainwindow.ui \
    marketingform.ui \
    statclient.ui \
    statistique.ui \
    testintegral.ui \
    voyageform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc
