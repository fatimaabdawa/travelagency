#include "mainwindow.h"
#include "login.h"
#include "connexion.h"
#include <QApplication>
#include <QMessageBox>
#include "notification.h"
#include "smtp.h"
#include <iostream>
#include <QPropertyAnimation>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connexion c;

    //StylishApp
    QFile styleFile(":/img/darkorng.qss");
    styleFile.open( QFile::ReadOnly );
    QString style( styleFile.readAll() );
    a.setStyleSheet(style);

    bool test=c.ouvrirConnexion();
     if(test)
    {
        QSplashScreen splash;
        splash.setPixmap(QPixmap(":/img/travel_background.jpg"));
        MainWindow w;
        login l;
        splash.show();
        QTimer::singleShot(2000,&splash,&QSplashScreen::close);
        QTimer::singleShot(2500,&l,&QSplashScreen::showFullScreen);
        l.show();
        QObject::connect(&l,&login::adminSignal,&w,&MainWindow::showFullScreen);
        return a.exec();
    }
     return 0;

}
