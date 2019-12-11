#include "mainwindow.h"
#include "login.h"
#include "connexion.h"
#include <QApplication>
#include <QMessageBox>
#include "notification.h"
#include "smtp.h"
#include <iostream>
#include <QPropertyAnimation>
#include "clientform.h"
#include "voyageform.h"
#include "employeform.h"
#include "marketingform.h"


#include "integratedone.h"

#include <QtSerialPort/QSerialPort>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connexion c;


    QFile styleFile(":/img/darkorng.qss");
    styleFile.open( QFile::ReadOnly );
    QString style( styleFile.readAll() );
    a.setStyleSheet(style);

    bool test=c.ouvrirConnexion();
     if(test)
    {
         /*
          * login l;
         MainWindow w;
         Clientform cf;
         voyageform vf;
         employeform ef;
         marketingform mf;
         QSplashScreen splash;
         splash.setPixmap(QPixmap(":/img/travel_background.jpg"));
         splash.show();
         QTimer::singleShot(8000,&splash,&QSplashScreen::close);
         QTimer::singleShot(5000,&l,&QSplashScreen::show);
         l.show();
         QObject::connect(&l,&login::adminSignal,&w,&MainWindow::show);
         QObject::connect(&l,&login::MohamedSignal,&cf,&Clientform::show);
         QObject::connect(&l,&login::OussemaSignal,&vf,&voyageform::show);
         QObject::connect(&l,&login::salahSignal,&ef,&employeform::show);
         QObject::connect(&l,&login::fatimaSignal,&mf,&marketingform::show);
         return a.exec();*/
         integratedone d;
         d.show();

         return a.exec();
    }
     return 0;

}


//StylishApp
/**/



/**/
