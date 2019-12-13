#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QApplication>
#include "mainwindow.h"
#include "login.h"
#include "connexion.h"
#include <QMessageBox>
#include "notification.h"
#include "smtp.h"
#include <iostream>
#include <QPropertyAnimation>
#include <QAnimationGroup>
#include <QTimer>
#include <QMediaPlayer>
#include "arduino.h"

#include "destination.h"


login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    /*QPixmap back1("C:/Users/Haboub/Pictures/Wallpapers/witcherHorizon.jpg");
    QPropertyAnimation *animationConnect = new QPropertyAnimation(ui->connecter,"geometry");
    //QPropertyAnimation *animationID = new QPropertyAnimation(ui->company,"geometry");
    // QPropertyAnimation *animationPW = new QPropertyAnimation(ui->password,"geometry");
    animationConnect->setDuration(5000);
    animationConnect->setStartValue(QRect(0,0,500,150));
    animationConnect->setEndValue(QRect(400,400,100,50));
    animationConnect->start();
    pl.setMedia(QUrl("C:/Users/Haboub/Desktop/Musi9/Daryl Hall & John Oates - Maneater (Official Music Video).mp3"));
   // pl.play();
   animationID->setDuration(2000);
    animationID->setStartValue(QRect(0,0,100,30));
    animationID->setEndValue(QRect(100,200,311,41));
    animationID->start();

    animationPW->setDuration(2000);
    animationPW->setStartValue(QRect(0,0,500,150));
    animationPW->setEndValue(QRect(100,100,100,30));
    animationPW->start();
*/


    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }

    //QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

    ui->Wrongpassword->hide();

}
/*
void login::update_label()
{
    if(A.getserial()->waitForReadyRead(10))
    data=A.read_from_arduino();
if(data == "1")
    qDebug() << "ventilator is  ON";
    else if(data== "0" )
        qDebug() << "ventilator is  OFF";

}
*/

login::~login()
{
    delete ui;
}


void login::on_connecter_clicked()
{
    QString id=ui->identifier->text();
    QString pw = ui->password->text();

    int logging = Authentification(id,pw);
    if(logging >= 1 && logging <= 6)
    {
        A.close_arduino();
    }
    switch(logging){
    case 1 :
    {
        emit habibSignal();
    }
    break;
    case 3 :
    {
        emit MohamedSignal();
        QMediaPlayer *m= new QMediaPlayer();
        m->setMedia(QUrl::fromLocalFile("/Users/Haboub/Documents/FingersCrossed/acceuil.mp3"));
        m->play();
    }
        break;
    case 2:
    {
        emit OussemaSignal();
    }
        break;
    case 4:
    {
        emit salahSignal();
    }
        break;
    case 5:
    {
        emit fatimaSignal();
    }
        break;
    case 6 :
    {
        emit adminSignal();
    }break;
     case 0 :
    {
        ui->Wrongpassword->show();
    }
       break;
    }
}

void login::on_showpassword_clicked(bool checked)
{
    if(checked)
    {
        ui->password->setEchoMode(QLineEdit::EchoMode(0));
    }
    else
    {
        ui->password->setEchoMode(QLineEdit::EchoMode(2));
    }
}



int login::Authentification(QString log,QString pw)
{
    QString prod = "Produits";
    QString vent = "Ventes";
    QString cl = "Clients";
    QString emp = "Employes";
    QString prom = "Marketing";
    QString yep = "Administrator";
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select * from employe");
    query->exec();
    while(query->next())
    {
        if(query->value(1).toString() == pw && query->value(2) == log)
        {
            if(query->value(3).toString()==prod)
                return 1;
            else if(query->value(3).toString()== vent)
                return 2;
            else if(query->value(3).toString()== cl)
                return 3;
            else if(query->value(3).toString()== emp)
                return 4;
            else if(query->value(3).toString()== prom)
                return 5;
            else if(query->value(3).toString() == yep)
                return 6;
            else return 0;
        }
    }
    return  0;
}

void login::on_pushButton_clicked()
{
    QByteArray byte = "1";

    A.write_to_arduino(byte);
    if(A.getserial()->waitForReadyRead(10))
        data=A.read_from_arduino();
    qDebug() << "data : " << data;
}

void login::on_pushButton_2_clicked()
{
    // QByteArray byte = "00";
    QByteArray byte = "0";
    A.write_to_arduino("0");
    A.write_to_arduino(byte);
    if(A.getserial()->waitForReadyRead(10))
        data=A.read_from_arduino();
    qDebug() << "data : " << data;
}


