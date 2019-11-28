#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<prromtion.h>
#include "qtableview.h"
#include <QSqlQueryModel>
#include <QMessageBox>
#include"login.h"
#include"statistique.h"
#include "smtp.h"
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include <QtMultimedia/QSound>
#include <QtMultimedia/QMediaPlayer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
refresh();
ui->tablepromotion->setModel(tmpprromotion.afficher());
ui->tableView_evenement->setModel(tmpevenemant.afficher());
connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
 connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void  MainWindow::refresh()
{
ui->tableView_evenement->setModel(tmpevenemant.afficher());
    ui->comboBox->setModel(tmpevenemant.afficher_list());
    ui->comboBox_2->setModel(tmpevenemant.afficher_list());

}


void MainWindow::on_pushButton_clicked()
{

    int id = ui->lineEdit_id1->text().toInt();
    QString Ddebut = ui->dateEdit_debut->text();
    QString Dfin = ui->dateEdit_fin->text();
    int pourcentage = ui->lineEdit_pourcentage->text().toInt();
     prromtion p(id,Ddebut,Dfin,pourcentage);
bool test= p.ajouter();
if(test)
{
    ui->tablepromotion->setModel(tmpprromotion.afficher());
    QMessageBox::information(nullptr, QObject::tr("Ajouter une promotion"),
                      QObject::tr("promotion ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter une promotion"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_3_clicked()
{
    int id = ui->lineEdit_6->text().toInt();
    bool test=tmpprromotion.supprimer(id);
    if(test)
    {ui->tablepromotion->setModel(tmpprromotion.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une promotion"),
                    QObject::tr("promotion supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une promotion"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_4_clicked()
{

  QString  id = ui->lineEdit_id2->text();
    QString dateD = ui->dateDebut->text();
    QString dateF = ui->dateEdit_fin->text();
     QString nom = ui->lineEdit_nom->text();
      QString lieu = ui->lineEdit_lieu->text();

     evenemant e(id,dateD,dateF,nom,lieu);
bool test= e.ajouter();
if(test)
{

    ui->tableView_evenement->setModel(tmpevenemant.afficher());
    QMessageBox::information(nullptr, QObject::tr("Ajouter un evenement"),
                      QObject::tr("evenement ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);


    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un evenement"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

}






void MainWindow::on_comboBox_supprimer_activated(const QString &arg1)
{
    ui->supp->setText(arg1);
}

void MainWindow::on_pushButton_2_clicked()
{
    int id= ui->lineEdit_idmodifpro->text().toInt();
    QString Ddebut= ui->dateEdit_modifprodebut->text();
    QString Dfin = ui->dateEdit_modifprofin->text();
    int pourcentage = ui->lineEdit_modifpropourcentage->text().toInt();

prromtion p;
bool test;
test=p.modifier(id,Ddebut,Dfin,pourcentage);
if(test)
{ ui->tablepromotion->setModel(tmpprromotion.afficher());

   QMessageBox::information(nullptr,QObject::tr("modifier promotion"),
     QObject::tr(" promotion modifer") ,QMessageBox::Cancel);

  }else

      QMessageBox::critical(nullptr,QObject::tr("modifier promotion"),
        QObject::tr("merci de remplir tout les champs correctement") ,QMessageBox::Cancel) ;
}

void MainWindow::on_consulter_stat_clicked()
{

    ui->tablestat->setModel(tmpevenemant.stats());
    statistique*a=new statistique();
    a->show();
}


void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toUShort());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());

}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void MainWindow::on_pushbouton_print_clicked()
{
    QPrinter printer;
        printer.setPrinterName("fatima");
        QPrintDialog dialog(&printer,this);
        if(dialog.exec()==QDialog::Rejected)
            return;
        ui->textEdit_print->print(&printer);
}

void MainWindow::on_comboBox_2_activated(const QString &arg1)
{

    ui->supp->setText(arg1);

}

void MainWindow::on_comboBox_activated(const QString &arg1)
{

    tmpevenemant.setid(arg1);
         tmpevenemant.chercher();
    ui->nom_modifier->setText(tmpevenemant.get_nom());
    ui->lieu_modifier->setText(tmpevenemant.get_lieu());

}

void MainWindow::on_supprimer_clicked()
{
    if(tmpevenemant.supprimer(ui->supp->text())){
        refresh();
       ui->supp->clear();

    }
    evenemant e;
     bool test;
     test=e.modifier();
     if(test)
     { ui->tablepromotion->setModel(tmpprromotion.afficher());

        QMessageBox::information(nullptr,QObject::tr("supprimer evenement"),
          QObject::tr(" evenement modife") ,QMessageBox::Cancel);

       }else

           QMessageBox::critical(nullptr,QObject::tr("modifier evenement"),
             QObject::tr("merci de remplir tout les champs correctement") ,QMessageBox::Cancel) ;
}

void MainWindow::on_dateDebut_userDateChanged(const QDate &date)
{

    tmpevenemant.setdateD(date.toString());
}

void MainWindow::on_datefin_userDateChanged(const QDate &date)
{
    tmpevenemant.setdateF(date.toString());
}

void MainWindow::on_dated_userDateChanged(const QDate &date)
{
     tmpevenemant.setdateD(date.toString());
}

void MainWindow::on_datef_userDateChanged(const QDate &date)
{

    tmpevenemant.setdateF(date.toString());
}

void MainWindow::on_modifier_clicked_clicked()
{
    tmpevenemant.setnom(ui->nom_modifier->text());
     tmpevenemant.setlieu(ui->lieu_modifier->text());
     if(tmpevenemant.modifier())
     {
         refresh();
     }
    evenemant e;
     bool test;
     test=e.modifier();
     if(test)
     { ui->tablepromotion->setModel(tmpprromotion.afficher());

        QMessageBox::information(nullptr,QObject::tr("modifier evenement"),
          QObject::tr(" evenement modife") ,QMessageBox::Cancel);

       }else

           QMessageBox::critical(nullptr,QObject::tr("modifier evenement"),
             QObject::tr("merci de remplir tout les champs correctement") ,QMessageBox::Cancel) ;
}
