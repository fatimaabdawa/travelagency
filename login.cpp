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
#include <QTimer>
login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    //this->centralWidget()->setStyleSheet("background-image:url(C:/Users/Pc Store/Desktop/background_travel.jpg); background-position:center;");
    //QPixmap back1("C:/Users/Pc Store/Desktop/background_travel.jpg)");
    QPropertyAnimation *animationConnect = new QPropertyAnimation(ui->connecter,"geometry");
    // QPropertyAnimation *animationID = new QPropertyAnimation(ui->identifier,"geometry");
    // QPropertyAnimation *animationPW = new QPropertyAnimation(ui->password,"geometry");
    animationConnect->setDuration(5000);
    animationConnect->setStartValue(QRect(0,0,500,150));
    animationConnect->setEndValue(QRect(400,400,100,50));
    animationConnect->start();
    pl.setMedia(QUrl("C:/Users/Haboub/Desktop/Musi9/Daryl Hall & John Oates - Maneater (Official Music Video).mp3"));
    pl.play();
/*
 *
    animationID->setDuration(2000);
    animationID->setStartValue(QRect(0,0,500,150));
    animationID->setEndValue(QRect(100,200,100,30));
    animationID->start();

    animationPW->setDuration(2000);
    animationPW->setStartValue(QRect(0,0,500,150));
    animationPW->setEndValue(QRect(100,100,100,30));
    animationPW->start();*/
    ui->Wrongpassword->hide();
}


login::~login()
{
    delete ui;
}


void login::on_connecter_clicked()
{
    QString id=ui->identifier->text();
    QString pw = ui->password->text();
  if(id == "oussema" and pw == "oussema")
    {
      emit adminSignal();
      close();
    }else
      {
      ui->Wrongpassword->show();
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
