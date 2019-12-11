#include "marketingform.h"
#include "ui_marketingform.h"
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
#include<QDesktopServices>
#include<QUrl>
#include"QFile"
#include"QTextStream"

marketingform::marketingform(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::marketingform)
{
    ui->setupUi(this);
    refresh();
    ui->tablepromotion->setModel(tmpprromotion.afficher());
    ui->tableView_evenement->setModel(tmpevenemant.afficher());
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
     connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
}

marketingform::~marketingform()
{
    delete ui;
}


void  marketingform::refresh()
{
ui->tableView_evenement->setModel(tmpevenemant.afficher());
    ui->comboBox->setModel(tmpevenemant.afficher_list());
    ui->comboBox_5->setModel(tmpevenemant.afficher_list());

}





void marketingform::on_comboBox_supprimer_activated(const QString &arg1)
{
    ui->supp->setText(arg1);
}



void marketingform::on_consulter_stat_clicked()
{
     QSound::play("qrc:/boutton.wav");

    ui->tablestat->setModel(tmpevenemant.stats());
    statistique*a=new statistique();
    a->show();
}


void marketingform::sendMail()

{QSound::play("qrc:/boutton.wav");

    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toUShort());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());

}

void marketingform::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void marketingform::on_pushbouton_print_clicked()
{QSound::play("qrc:/boutton.wav");
    QPrinter printer;
        printer.setPrinterName("fatima");
        QPrintDialog dialog(&printer,this);
        if(dialog.exec()==QDialog::Rejected)
            return;
        ui->textEdit_print->print(&printer);
}

void marketingform::on_comboBox_2_activated(const QString &arg1)
{

    ui->supp->setText(arg1);

}

/*void marketingform::on_comboBox_activated(const QString &arg1)
{

    tmpevenemant.setid(arg1);
         tmpevenemant.chercher();
    ui->nom->setText(tmpevenemant.get_nom());
    ui->lieu->setText(tmpevenemant.get_lieu());

}*/

void marketingform::on_supprimer_clicked()
{QSound::play("qrc:/boutton.wav");
    if(tmpevenemant.supprimer(ui->supp->text())){
        refresh();
       ui->supp->clear();

    }
    evenemant e;
     bool test;
     test=e.modifier();
     if(test)
     { ui->tableView_evenement->setModel(tmpevenemant.afficher());

        QMessageBox::information(nullptr,QObject::tr("supprimer evenement"),
          QObject::tr(" evenement supprimer") ,QMessageBox::Cancel);

       }else

           QMessageBox::critical(nullptr,QObject::tr("supprimer evenement"),
             QObject::tr("erreur") ,QMessageBox::Cancel) ;
}

void marketingform::on_dateDebut_userDateChanged(const QDate &date)
{

    tmpevenemant.setdateD(date.toString());
}

void marketingform::on_datefin_userDateChanged(const QDate &date)
{
    tmpevenemant.setdateF(date.toString());
}

void marketingform::on_dated_userDateChanged(const QDate &date)
{
     tmpevenemant.setdateD(date.toString());
}

void marketingform::on_datef_userDateChanged(const QDate &date)
{

    tmpevenemant.setdateF(date.toString());
}

void marketingform::on_modifier_clicked_clicked()
{QSound::play("qrc:/boutton.wav");
    tmpevenemant.setnom(ui->nom->text());
     tmpevenemant.setlieu(ui->lieu->text());
     if(tmpevenemant.modifier())
     {
         refresh();
     }
    evenemant e;
     bool test;
     test=e.modifier();
     if(test)
     { ui->tableView_evenement->setModel(tmpevenemant.afficher());

        QMessageBox::information(nullptr,QObject::tr("modifier evenement"),
          QObject::tr(" evenement modife") ,QMessageBox::Cancel);

       }else

           QMessageBox::critical(nullptr,QObject::tr("modifier evenement"),
             QObject::tr("merci de remplir tout les champs correctement") ,QMessageBox::Cancel) ;
}

void marketingform::on_facebook_clicked()
{
    QString link="https://www.facebook.com/mustdotravels/";
    QDesktopServices::openUrl(QUrl(link));

}

void marketingform::on_TRI_clicked()
{
    ui->tableView_evenement->setModel(tmpevenemant.afficher_tri());
}

void marketingform::on_lineEdit_chercher_textChanged(const QString &arg1)
{
    ui->tableView_evenement->setModel(tmpevenemant.chercher_evenement(arg1));
}

void marketingform::on_pushButton_5_clicked()
{QSound::play("qrc:/boutton.wav");
    QString link="https://www.instagram.com/smart_travel_agency18/";
    QDesktopServices::openUrl(QUrl(link));
}

void marketingform::on_youtube_clicked()
{
QSound::play("qrc:/boutton.wav");
    QString link="https://www.youtube.com/watch?v=gG2ABStEDcw";
    QDesktopServices::openUrl(QUrl(link));
}

void marketingform::on_pushButton_7_clicked()
{QSound::play("qrc:/boutton.wav");
   QFile file("C:/Users/asus/Desktop/mailing/fatproject/myfile.txt");
   if(!file.open(QFile::WriteOnly))
   {
       QMessageBox::warning(this,"title","file not open");
   }
   QTextStream out(&file);
           QString text=ui->plainTextEdit2->toPlainText();
           out<<text;
           file.flush();
           file.close();
}

void marketingform::on_pushButton_6_clicked()
{QSound::play("qrc:/boutton.wav");
    QFile file("C:/Users/asus/Desktop/mailing/fatproject/myfile.txt");
    if(!file.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this,"title","file not open");
    }
    QTextStream in(&file);
            QString text= in.readAll();
            ui->plainTextEdit2->setPlainText(text);

            file.close();
 }


void marketingform::on_ajouterpro_clicked()
{
    QSound::play("qrc:/boutton.wav");
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

void marketingform::on_modifierpro_clicked()
{
    QSound::play("qrc:/boutton.wav");
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

void marketingform::on_supprimerpro_2_clicked()
{
    QSound::play("qrc:/boutton.wav");
   int id = ui->supprimerpro->text().toInt();
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



void marketingform::on_ajouterevent_clicked()
{
    QSound::play("qrc:/boutton.wav");

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

void marketingform::on_comboBox_5_activated(const QString &arg1)
{

    tmpevenemant.setid(arg1);
         tmpevenemant.chercher();
    ui->nom->setText(tmpevenemant.get_nom());
    ui->lieu->setText(tmpevenemant.get_lieu());
}
