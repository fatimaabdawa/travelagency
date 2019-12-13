#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include"mainwindow.h"
#include"ui_mainwindow.h"
#include"QTableWidget"
#include"QTableView"
#include"QTableWidgetItem"
#include <QSound>



login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);


     db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("fatima");//inserer nom de l'utilisateur
    db.setPassword("esprit19");//inserer mot de passe de cet utilisateur

     if(!db.open())
         ui->label->setText("failed to open database");
     else
         ui->label->setText("connected...");
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QSound::play("C:/Users/asus/Downloads/boutton.wav");
    QString USERNAME,PASSWORD;
    ui->lineEdit_username->text();
    ui->lineEdit_password->text();




      if(!db.isOpen()){
          qDebug()<<"failed to open database";
      return;
      }

       QSqlQuery qry;
      if(qry.exec("SELECT FROM * USERNAME,PASSWORD from EMPLOYE WHERE USERNAME = :USERNAME and PASSWORD = :PASSWORD "))
          qry.bindValue(":USERNAME", USERNAME);
         qry.bindValue(":PASSWORD", PASSWORD);



      {
             int count=0;
             while (qry.next())
             {
                count ++;
             }

       if(count==1)
       ui->label->setText("username and password  not correct");


       if(count<1){
       ui->label->setText("username and password are correct");
       this->hide();




       }
}



     }

