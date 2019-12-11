#include "formclient.h"
#include "ui_formclient.h"
#include "client.h"
#include "clientvip.h"
#include "smtp.h"
#include "statistique.h"
#include <QMessageBox>
#include "mainwindow.h"
#include <QApplication>

Formclient::Formclient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formclient)
{
    ui->setupUi(this);
}

Formclient::~Formclient()
{
    delete ui;
}

void Formclient::on_pushButton_ajouterclient_clicked()
{
    int i;
    bool testt=false;
    QString nom=ui->ajoutnomclient->text();
    QString prenom=ui->ajoutprenomclient->text();
    int numeropasseport=ui->ajoutnpclient->text().toInt();
    QString mail=ui->ajoutmailclient->text();
    QString pays=ui->ajoutpaysclient->text();
    int age=ui->ajoutageclient->text().toInt();
    client c(nom,prenom,numeropasseport,mail,pays,age);
    bool r=c.fctqverifmail(mail);
    bool rs=c.fctqverinp(numeropasseport);
    for (i=0;i<mail.length();i++)
    {
        if (mail[i]=="@")
        {testt=true;}
    }
    if(rs==false)
    {
        if ((testt==true)&&(r==false))
        {
           bool test=c.ajouter();
        }
        else
        {
            QMessageBox::about(this,"ERROR","Adresse mail existe déja ou ne contient pas '@'");
        }

    }
    else
    {
        QMessageBox::about(this,"ERROR","Numero du passeport existe déja");
    }
}

void Formclient::on_tabWidget_currentChanged(int index)
{
    ui->tableclient->setModel(tmpclient.afficher());
    ui->comboBoxmodifclient->setModel(tmpclient.GetNumpassModel());
    ui->comboBoxsuppclient->setModel(tmpclient.GetNumpassModel());
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));



}

void Formclient::on_comboBoxmodifclient_activated(const QString &arg1)
{
    tmpclient.set_numpasseport(arg1.toInt());
    tmpclient.recherche();
    ui->nouvnomclient->setText(tmpclient.getnom());
    ui->nouvprenomclient->setText(tmpclient.getprenom());
    ui->nouvmailclient->setText(tmpclient.getmail());
    ui->nouvpaysclient->setText(tmpclient.getpays());
    QString age=QString::number(tmpclient.getage());
    ui->nouvageclient->setText(age);
}

void Formclient::on_pushButton_modifclient_clicked()
{
    int i;
    bool testt=false;
    int numeropasseport=ui->comboBoxmodifclient->currentText().toInt();
    QString nom=ui->nouvnomclient->text();
    QString prenom=ui->nouvprenomclient->text();
    QString mail=ui->nouvmailclient->text();
    QString pays=ui->nouvpaysclient->text();
    int age=ui->nouvageclient->text().toInt();
    client c(nom,prenom,numeropasseport,mail,pays,age);
    bool r=c.fctqverifmail(mail);
    for (i=0;i<mail.length();i++)
    {
        if (mail[i]=="@")
        {testt=true;}
    }
    if (testt==true)
    {
    bool test=tmpclient.modifier(numeropasseport,nom,prenom,mail,pays,age);
    }
    else
    {
        QMessageBox::about(this,"ERROR","Adresse mail ne contient pas '@'");
    }
    ui->tableclient->setModel(tmpclient.afficher());

}

void Formclient::on_pushButton_suppclient_clicked()
{
    int np=ui->comboBoxsuppclient->currentText().toInt();
    bool test=tmpclient.supprimer(np);
    if(test)
    {
       ui->tableclient->setModel(tmpclient.afficher());
       ui->comboBoxsuppclient->setModel(tmpclient.GetNumpassModel());
       ui->comboBoxmodifclient->setModel(tmpclient.GetNumpassModel());

    }
}

void Formclient::on_rechercheclient_textChanged(const QString &arg1)
{
    ui->tableclient->setModel(tmpclient.afficher2(arg1));

}

void Formclient::on_pushButton_ajouterclientvip_clicked()
{
    int i;
    bool testt=false;
    QString nom=ui->ajoutnomclientvip->text();
    QString prenom=ui->ajoutprenomclientvip->text();
    int numeropasseport=ui->ajoutnpclientvip->text().toInt();
    QString mail=ui->ajoutmailclientvip->text();
    QString profession=ui->ajoutprofessionclientvip->text();
    QString pays=ui->ajoutpaysclientvip->text();
    int age=ui->ajoutageclientvip->text().toInt();
    clientvip c(nom,prenom,numeropasseport,mail,profession,pays,age);
    bool r=c.fctqverifmail(mail);
    bool rs=c.fctqverinp(numeropasseport);
    for (i=0;i<mail.length();i++)
    {
        if (mail[i]=="@")
        {testt=true;}
    }
    if(rs==false)
    {
        if ((testt==true)&&(r==false))
        {
           bool test=c.ajouter();
        }
        else
        {
            QMessageBox::about(this,"ERROR","Adresse mail existe déja ou ne contient pas '@'");
        }

    }
    else
    {
        QMessageBox::about(this,"ERROR","Numero du passeport existe déja");
    }
}

void Formclient::on_tabWidget_2_currentChanged(int index)
{
    ui->tableclientvip->setModel(tmpclientvip.afficher());
    ui->comboBoxsuppclientvip->setModel(tmpclientvip.GetNumpassModel());
    ui->comboBoxmodifclientvip->setModel(tmpclientvip.GetNumpassModel());
}

void Formclient::on_comboBoxmodifclientvip_activated(const QString &arg1)
{
    tmpclientvip.set_numpasseport(arg1.toInt());
    tmpclientvip.recherche();
    ui->nouvnomclientvip->setText(tmpclientvip.getnom());
    ui->nouvprenomclientvip->setText(tmpclientvip.getprenom());
    ui->nouvmailclientvip->setText(tmpclientvip.getmail());
    ui->nouvprofessionclientvip->setText(tmpclientvip.getprofession());
    ui->nouvpaysclientvip->setText(tmpclientvip.getpays());
    QString age=QString::number(tmpclientvip.getage());
    ui->nouvageclientvip->setText(age);
}

void Formclient::on_pushButton_modifclientvip_clicked()
{
    int i;
    bool testt=false;
    QString nom=ui->nouvnomclientvip->text();
    QString prenom=ui->nouvprenomclientvip->text();
    int numeropasseport=ui->comboBoxmodifclientvip->currentText().toInt();
    QString mail=ui->nouvmailclientvip->text();
    QString profession=ui->nouvprofessionclientvip->text();
    QString pays=ui->nouvpaysclientvip->text();
    int age=ui->nouvageclientvip->text().toInt();
    clientvip c(nom,prenom,numeropasseport,mail,profession,pays,age);
    bool r=c.fctqverifmail(mail);
    for (i=0;i<mail.length();i++)
    {
        if (mail[i]=="@")
        {testt=true;}
    }
    if (testt==true)
    {
        bool test=tmpclientvip.modifier(numeropasseport,nom,prenom,mail,profession,pays,age);
    }
    else
    {
        QMessageBox::about(this,"ERROR","Adresse mail ne contient pas '@'");
    }
    ui->tableclientvip->setModel(tmpclientvip.afficher());

}

void Formclient::on_pushButton_suppclientvip_clicked()
{
    int np=ui->comboBoxsuppclientvip->currentText().toInt();
    bool test=tmpclientvip.supprimer(np);
    if(test)
    {
       ui->tableclientvip->setModel(tmpclientvip.afficher());

       ui->comboBoxsuppclientvip->setModel(tmpclientvip.GetNumpassModel());
       ui->comboBoxmodifclientvip->setModel(tmpclientvip.GetNumpassModel());

    }
}

void Formclient::on_rechercheclientvip_2_textChanged(const QString &arg1)
{
    ui->tableclientvip->setModel(tmpclientvip.afficher2(arg1));

}



void Formclient::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toUShort());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void Formclient::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


void Formclient::on_sendBtn_clicked()
{
   sendMail();
}

void Formclient::on_exitBtn_clicked()
{
    close();
}
void Formclient::on_statbutton_clicked()
{
    statistique*a=new statistique();
    a->show();
}
