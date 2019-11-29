#include "mainwindow.h"
#include <connexion.h>
#include <QApplication>
#include "reserverhotel.h"
#include "reservervoyage.h"
#include <QMessageBox>
#include <iostream>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
       Connexion c;
       QFile styleFile( ":/img/darkorng.qss" );
       styleFile.open( QFile::ReadOnly );

       // Apply the loaded stylesheet
       QString style( styleFile.readAll() );
       a.setStyleSheet( style );

       bool test=c.ouvrirConnexion();
   if(test){

   MainWindow w;
       w.show();
       //QMessageBox::information(nullptr,QObject::tr("Bienvenue !"),"Vous etes connecte a la base !");
       return a.exec();
   }
   else //QMessageBox::information(nullptr,QObject::tr("ERROR !"),"Probleme de connexion a la base !");
       return 0;
}
