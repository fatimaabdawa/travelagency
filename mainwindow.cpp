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
#include<QDesktopServices>
#include<QUrl>
#include"QFile"
#include"QTextStream"
#include"smtp.h"
#include"capteur.h"
#include"ui_capteur.h"
#include"arduino.h"
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPropertyAnimation *animation = new QPropertyAnimation(ui->animated, "geometry");
        animation->setDuration(10000);
        animation->setLoopCount(-1);
        animation->setStartValue(QRect(-400, 10, 371, 71));
        animation->setEndValue(QRect(700, 10, 371, 71));
        animation->start();
    int ret=a.connect_arduino();//lancer la cnx arduino
    switch(ret)
    {
    case(0):qDebug()<<"arduino is available and connected to:"<<a.getarduino_port_name();
        break;
    case(1):qDebug()<<"arduino is available but not connected to:"<<a.getarduino_port_name();
        break;
    case(-1):qDebug()<<"arduino is not available";
    }
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
    ui->comboBox_5->setModel(tmpevenemant.afficher_list());

}





void MainWindow::on_comboBox_supprimer_activated(const QString &arg1)
{
    ui->supp->setText(arg1);
}



void MainWindow::on_consulter_stat_clicked()
{
     QSound::play("C:/Users/asus/Downloads/boutton.wav");

    ui->tablestat->setModel(tmpevenemant.stats());
    statistique*a=new statistique();
    a->show();
}


void MainWindow::sendMail()

{QSound::play("C:/Users/asus/Downloads/boutton.wav");

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
{QSound::play("C:/Users/asus/Downloads/boutton.wav");
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

/*void MainWindow::on_comboBox_activated(const QString &arg1)
{

    tmpevenemant.setid(arg1);
         tmpevenemant.chercher();
    ui->nom->setText(tmpevenemant.get_nom());
    ui->lieu->setText(tmpevenemant.get_lieu());

}*/

void MainWindow::on_supprimer_clicked()
{QSound::play("C:/Users/asus/Downloads/boutton.wav");
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
{QSound::play("C:/Users/asus/Downloads/boutton.wav");
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

void MainWindow::on_facebook_clicked()
{
    QString link="https://www.facebook.com/mustdotravels/";
    QDesktopServices::openUrl(QUrl(link));

}

void MainWindow::on_TRI_clicked()
{
    ui->tableView_evenement->setModel(tmpevenemant.afficher_tri());
}

void MainWindow::on_lineEdit_chercher_textChanged(const QString &arg1)
{
    ui->tableView_evenement->setModel(tmpevenemant.chercher_evenement(arg1));
}

void MainWindow::on_pushButton_5_clicked()
{QSound::play("C:/Users/asus/Downloads/boutton.wav");
    QString link="https://www.instagram.com/smart_travel_agency18/";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_youtube_clicked()
{
QSound::play("C:/Users/asus/Downloads/boutton.wav");
    QString link="https://www.youtube.com/watch?v=gG2ABStEDcw";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_7_clicked()
{QSound::play("C:/Users/asus/Downloads/boutton.wav");
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

void MainWindow::on_pushButton_6_clicked()
{QSound::play("C:/Users/asus/Downloads/boutton.wav");
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


void MainWindow::on_ajouterpro_clicked()
{
    QSound::play("C:/Users/asus/Downloads/boutton.wav");
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

void MainWindow::on_modifierpro_clicked()
{
    QSound::play("C:/Users/asus/Downloads/boutton.wav");
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

void MainWindow::on_supprimerpro_2_clicked()
{
    QSound::play("C:/Users/asus/Downloads/boutton.wav");
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



void MainWindow::on_ajouterevent_clicked()
{
    QSound::play("C:/Users/asus/Downloads/boutton.wav");

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

void MainWindow::on_comboBox_5_activated(const QString &arg1)
{

    tmpevenemant.setid(arg1);
         tmpevenemant.chercher();
    ui->nom->setText(tmpevenemant.get_nom());
    ui->lieu->setText(tmpevenemant.get_lieu());
}



void MainWindow::update_label()
{
    data=a.read_from_arduino();
    if (data=="1")
        ui->fatima->setText("ON");
    else if(data=="0")
        ui->fatima->setText("OFF");
}


void MainWindow::on_pushButton_clicked()
{
   a.write_to_arduino("1");
   if(a.getserial()->waitForReadyRead(10))
      data=a.read_from_arduino();
      qDebug() << "data : " << data;
}

void MainWindow::on_OFF_pushbutton_clicked()
{
 a.write_to_arduino("0");
 if(a.getserial()->waitForReadyRead(10))
    data=a.read_from_arduino();
    qDebug() << "data : " << data;
}



