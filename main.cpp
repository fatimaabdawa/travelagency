#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connexion.h"
#include <QtDebug>
#include"evenemant.h"
#include"login.h"
int main(int argc, char *argv[])
{  QApplication a(argc, argv);

    Connexion c;
 MainWindow w;

  if(c.ouvrirConnexion())
  {
  w.show();
  login l;
  l.show();
     return a.exec();
  }
  return 0;

}
