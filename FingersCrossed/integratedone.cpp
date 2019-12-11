#include "integratedone.h"
#include "ui_integratedone.h"
#include "client.h"
#include "clientvip.h"
#include "smtp.h"
#include "statclient.h"
#include <QMessageBox>
#include "integratedone.h"
#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include <QDate>
#include <QMediaPlayer>

integratedone::integratedone(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::integratedone)
{
    ui->setupUi(this);

    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();
    QDate date=QDate::currentDate();
    QString date_t=date.toString();
    //ui->mydate->setText(date_t);

    //MOHAMED

    //OUSSEMA

    ui->codedestination_rv_ajout->setModel(tmpajouth.CodeDestinationModel());
    ui->reference_voyage_combo->setModel(tmpmodifvoyage.get_ref_ajoutes());
    ui->idhotel_combobox->setModel(tmpajouth.CodeModelHotel());
    ui->idhotel_supprimer->setModel(tmpajouth.NumeroPassePortReserverHotel());
    ui->numeropasseport_combobox->setModel(tmpajouth.NumeroPasseportModelHotel());
    ui->numeropasseport_rv_ajout->setModel(tmpajouth.NumeroPasseportModelHotel());
    ui->tabresvoyage->setModel(tmpreservoyage.afficher());
    ui->tabreshotel->setModel(tmpajouth.afficher());
    player->setMedia(QUrl("C:/Users/Pc Store/Desktop/INTEGRA/yah/C.mp3"));
    player->play();
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));

    //YOUR HUMBLE SERVANT

    ui->tableView->setModel(tmpdestination.afficher());
    ui->tableView2->setModel(tmphotel.afficherH());
    ui->comboBox->setModel(tmpdestination.ModelCodeDestinations());
    ui->comboBox_2->setModel(tmphotel.ModelidhotelHotel());
    ui->idhotel_asupprimer->setModel(tmphotel.ModelidhotelHotel());
    ui->Code_destination_ajouthotel->setModel(tmpdestination.ModelCodeDestinations());
    ui->code_asupprimer->setModel(tmpdestination.ModelCodeDestinations());
    ui->promo_aajouter->setValidator(new QRegExpValidator(QRegExp("[0-1]"),this));
    ui->nom_aajout->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z-0-9]+"),this));
    ui->promo_amodifier->setValidator(new QRegExpValidator(QRegExp("[0-1]"),this));
    ui->nom_amodifier->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z-0-9]+"),this));
    ui->cout_ajout_hotel->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));
    ui->couthotel_amodifier->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));
    ui->etoiles_ajout_hotel->setValidator(new QRegExpValidator(QRegExp("[0-9]"),this));
    ui->etoileshotel_amodifier->setValidator(new QRegExpValidator(QRegExp("[0-9]"),this));

    //FATIMA

    refresh();
    ui->tablepromotion->setModel(tmpprromotion.afficher());
    ui->tableView_evenement->setModel(tmpevenemant.afficher());
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));



}

integratedone::~integratedone()
{
    delete ui;
}


//CHOOSE WHICH MODULE TO SHOW AND OPERATE.

void integratedone::on_intdestinations_clicked()
{
    ui->whole_in_one->setCurrentIndex(1);
}

void integratedone::on_intreservations_clicked()
{
    ui->whole_in_one->setCurrentIndex(4);
}

void integratedone::on_intemployes_clicked()
{
    ui->whole_in_one->setCurrentIndex(2);
}

void integratedone::on_intclients_clicked()
{
    ui->whole_in_one->setCurrentIndex(0);
}

void integratedone::on_intevents_clicked()
{
    ui->whole_in_one->setCurrentIndex(3);
}

// CLIENTS MODULE FUNCTIONS.



void integratedone::on_pushButton_ajouterclient_clicked()
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
           QMediaPlayer *m= new QMediaPlayer();
           m->setMedia(QUrl::fromLocalFile("/Users/Haboub/Documents/FingersCrossed/ajoutclient.mp3"));
           m->play();
        }
        else
        {
            QMediaPlayer *m= new QMediaPlayer();
            m->setMedia(QUrl::fromLocalFile("/Users/Haboub/Documents/FingersCrossed/verifmail.mp3"));
            m->play();
            QMessageBox::about(this,"ERROR","Adresse mail existe déja ou ne contient pas '@'");
        }

    }
    else
    {
        QMediaPlayer *m= new QMediaPlayer();
        m->setMedia(QUrl::fromLocalFile("/Users/Haboub/Documents/FingersCrossed/verifnumpass.mp3"));
        m->play();
        QMessageBox::about(this,"ERROR","Numero du passeport existe déja");
    }
}

void integratedone::on_tabWidget_currentChanged(int index)
{
    ui->tableclient->setModel(tmpclient.afficher());
    ui->comboBoxmodifclient->setModel(tmpclient.GetNumpassModel());
    ui->comboBoxsuppclient->setModel(tmpclient.GetNumpassModel());
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));



}

void integratedone::on_comboBoxmodifclient_activated(const QString &arg1)
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

void integratedone::on_pushButton_modifclient_clicked()
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
        QMediaPlayer *m= new QMediaPlayer();
        m->setMedia(QUrl::fromLocalFile("/Users/Haboub/Documents/FingersCrossed/modifclient.mp3"));
        m->play();
    bool test=tmpclient.modifier(numeropasseport,nom,prenom,mail,pays,age);
    }
    else
    {
        QMediaPlayer *m= new QMediaPlayer();
        m->setMedia(QUrl::fromLocalFile("/Users/Haboub/Documents/FingersCrossed/verifmail.mp3"));
        m->play();
        QMessageBox::about(this,"ERROR","Adresse mail ne contient pas '@'");
    }
    ui->tableclient->setModel(tmpclient.afficher());

}

void integratedone::on_pushButton_suppclient_clicked()
{
    int np=ui->comboBoxsuppclient->currentText().toInt();
    bool test=tmpclient.supprimer(np);
    if(test)
    {
        QMediaPlayer *m= new QMediaPlayer();
        m->setMedia(QUrl::fromLocalFile("/Users/Haboub/Documents/FingersCrossed/suppclient.mp3"));
        m->play();
       ui->tableclient->setModel(tmpclient.afficher());
       ui->comboBoxsuppclient->setModel(tmpclient.GetNumpassModel());
       ui->comboBoxmodifclient->setModel(tmpclient.GetNumpassModel());

    }
}

void integratedone::on_rechercheclient_textChanged(const QString &arg1)
{
    ui->tableclient->setModel(tmpclient.afficher2(arg1));

}

void integratedone::on_pushButton_ajouterclientvip_clicked()
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
           QMediaPlayer *m= new QMediaPlayer();
           m->setMedia(QUrl::fromLocalFile("/Users/Haboub/Documents/FingersCrossed/ajoutclient.mp3"));
           m->play();
        }
        else
        {
            QMediaPlayer *m= new QMediaPlayer();
            m->setMedia(QUrl::fromLocalFile("/Users/Haboub/Documents/FingersCrossed/verifmail.mp3"));
            m->play();
            QMessageBox::about(this,"ERROR","Adresse mail existe déja ou ne contient pas '@'");
        }

    }
    else
    {
        QMediaPlayer *m= new QMediaPlayer();
        m->setMedia(QUrl::fromLocalFile("/Users/Haboub/Documents/FingersCrossed/verifnumpass.mp3"));
        m->play();
        QMessageBox::about(this,"ERROR","Numero du passeport existe déja");
    }
}

void integratedone::on_tabWidget_2_currentChanged(int index)
{
    ui->tableclientvip->setModel(tmpclientvip.afficher());
    ui->comboBoxsuppclientvip->setModel(tmpclientvip.GetNumpassModel());
    ui->comboBoxmodifclientvip->setModel(tmpclientvip.GetNumpassModel());
}

void integratedone::on_comboBoxmodifclientvip_activated(const QString &arg1)
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

void integratedone::on_pushButton_modifclientvip_clicked()
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
        QMediaPlayer *m= new QMediaPlayer();
        m->setMedia(QUrl::fromLocalFile("/Users/Haboub/Documents/FingersCrossed/modifclient.mp3"));
        m->play();
        bool test=tmpclientvip.modifier(numeropasseport,nom,prenom,mail,profession,pays,age);
    }
    else
    {
        QMediaPlayer *m= new QMediaPlayer();
        m->setMedia(QUrl::fromLocalFile("/Users/Haboub/Documents/FingersCrossed/verifmail.mp3"));
        m->play();
        QMessageBox::about(this,"ERROR","Adresse mail ne contient pas '@'");
    }
    ui->tableclientvip->setModel(tmpclientvip.afficher());

}

void integratedone::on_pushButton_suppclientvip_clicked()
{
    int np=ui->comboBoxsuppclientvip->currentText().toInt();
    bool test=tmpclientvip.supprimer(np);
    if(test)
    {
        QMediaPlayer *m= new QMediaPlayer();
        m->setMedia(QUrl::fromLocalFile("/Users/Haboub/Documents/FingersCrossed/suppclient.mp3"));
        m->play();
       ui->tableclientvip->setModel(tmpclientvip.afficher());

       ui->comboBoxsuppclientvip->setModel(tmpclientvip.GetNumpassModel());
       ui->comboBoxmodifclientvip->setModel(tmpclientvip.GetNumpassModel());

    }
}

void integratedone::on_rechercheclientvip_2_textChanged(const QString &arg1)
{
    ui->tableclientvip->setModel(tmpclientvip.afficher2(arg1));

}



void integratedone::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toUShort());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void integratedone::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


void integratedone::on_sendBtn_clicked()
{
   sendMail();
}

void integratedone::on_exitBtn_clicked()
{
    close();
}
void integratedone::on_statbutton_clicked()
{
    statclient *a=new statclient();
    a->show();
}

void integratedone::on_rechercheclient_3_textChanged(const QString &arg1)
{
    ui->tableclient->setModel(tmpclient.afficher2(arg1));

}

void integratedone::on_rechercheclient_2_textChanged(const QString &arg1)
{
    ui->tableclientvip->setModel(tmpclientvip.afficher2(arg1));

}


// DESTINATIONS-HOTELS MODULE FUNCTIONS.

void integratedone::on_ajouter_destination_clicked()
{
    tmpdestination.setPromo( ui->promo_aajouter->text().toInt());
    tmpdestination.setNom(ui->nom_aajout->text());
    tmpdestination.setDescription(ui->description_aajouter->text());
    QString nom=ui->nom_aajout->text();
    if(ui->nom_aajout->hasAcceptableInput() && ui->promo_aajouter->hasAcceptableInput()){
    bool test=tmpdestination.ajouter();
    if(test)
    {
        ok.notification_ajout_destination(nom);
        ui->tableView->setModel(tmpdestination.afficher());
        ui->comboBox->setModel(tmpdestination.ModelCodeDestinations());
        ui->code_asupprimer->setModel(tmpdestination.ModelCodeDestinations());
        QMessageBox::information(nullptr,QObject::tr("Ajout Destination"),"Destination Ajoutée");
    }

    }

}

void integratedone::on_SupprimerDestination_clicked()
{
    int code= ui->code_asupprimer->currentText().toInt();
    bool test=tmpdestination.supprimer(code);
    if(test)
    {
        ui->tableView->setModel(tmpdestination.afficher());
        ui->comboBox->setModel(tmpdestination.ModelCodeDestinations());
        ui->code_asupprimer->setModel(tmpdestination.ModelCodeDestinations());
    }
    else
    {

    }
}

void integratedone::on_ajouter_hotel_clicked()
{
    tmphotel.setEtoiles(ui->etoiles_ajout_hotel->text().toInt());
    tmphotel.setNom(ui->nom_ajouter_hotel->text());
    tmphotel.setAdresse(ui->adresse_ajout_hotel->text());
    tmphotel.setCoutparnuit(ui->cout_ajout_hotel->text().toInt());
    tmphotel.setCodeDestination(ui->Code_destination_ajouthotel->currentText().toInt());
    bool test= tmphotel.ajouterH();
    if(test)
    {
        ok.notification_ajout_hotel(tmphotel.getNom());
        ui->comboBox_2->setModel(tmphotel.ModelidhotelHotel());
        ui->tableView2->setModel(tmphotel.afficherH());
        ui->idhotel_asupprimer->setModel(tmphotel.ModelidhotelHotel());
        QMessageBox::information(nullptr,QObject::tr("Ajout Hotel"),"Well done sire!");
    }else
        QMessageBox::information(nullptr,QObject::tr("Ajout Hotel"),"ERROR MY LIEGE");
}


void integratedone::on_supprimer_hotel_clicked()
{
    tmphotel.setiIdhotel(ui->idhotel_asupprimer->currentText().toInt());
    bool test=tmphotel.supprimer();
    if(test)
    {
        ui->tableView2->setModel(tmphotel.afficherH());
        ui->idhotel_asupprimer->setModel(tmphotel.ModelidhotelHotel());
        QMessageBox::information(nullptr,QObject::tr("Suppression Hotel"),"Well done sire!");
    }
    else
        QMessageBox::information(nullptr,QObject::tr("Suppression Hotel"),"ERROR MY LIEGE");
}


void integratedone::on_comboBox_currentIndexChanged()
{
    destination d;
    d.setCode(ui->comboBox->currentText().toInt());
    tmpdestination.setCode(ui->comboBox->currentText().toInt());
    d.chercher(ui->comboBox->currentText().toInt());
    tmpdestination.chercher(d.getCode());
    ui->nom_amodifier->setText(tmpdestination.getNom());
    ui->description_amodifier->setText(tmpdestination.getDescription());
    ui->promo_amodifier->setText(QString::number(tmpdestination.getPromo()));
}

void integratedone::on_Modifier_clicked()
{
    int code =ui->comboBox->currentText().toInt();
    int promo = ui->promo_amodifier->text().toInt();
    QString description = ui->description_amodifier->text();
    QString nom = ui->nom_amodifier->text();
    destination d;
    if(ui->promo_amodifier->hasAcceptableInput() && ui->nom_amodifier->hasAcceptableInput()){
    bool y=d.modifier(description,nom,code,promo);
    if(y)
    {
        ui->tableView->setModel(tmpdestination.afficher());
        QMessageBox::information(nullptr,QObject::tr("Modification Destination"),"Well done sire!");
    }
    else
    {
        QMessageBox::information(nullptr,QObject::tr("Modification Destination"),"Error my liege !");
    }

      }
}

void integratedone::on_comboBox_2_currentIndexChanged()
{
    tmphotel.setiIdhotel(ui->comboBox_2->currentText().toInt());
    tmphotel.chercher();
    ui->nomhotel_amodifier->setText(tmphotel.getNom());
    ui->adressehotel_amodifier->setText(tmphotel.getAdresse());
    ui->etoileshotel_amodifier->setText(QString::number(tmphotel.getEtoiles()));
    ui->couthotel_amodifier->setText(QString::number(tmphotel.getCout_par_nuit()));

}

void integratedone::on_ModifierHotel_clicked()
{
    tmphotel.setiIdhotel(ui->comboBox_2->currentText().toInt());
    tmphotel.setCoutparnuit(ui->couthotel_amodifier->text().toInt());
    tmphotel.setAdresse(ui->adressehotel_amodifier->text());
    tmphotel.setNom(ui->nomhotel_amodifier->text());
    tmphotel.setEtoiles(ui->etoileshotel_amodifier->text().toInt());
    bool y = tmphotel.modifier();
    if(y)
    {
        ui->comboBox_2->setModel(tmphotel.ModelidhotelHotel());
        ui->tableView2->setModel(tmphotel.afficherH());
        QMessageBox::information(nullptr,QObject::tr("Modification Hotel"),"Well done sire!");
    }
    else
    {
        QMessageBox::information(nullptr,QObject::tr("Modification Hotel"),"Error my liege !");
    }
}

void integratedone::on_trierChercher_2_textChanged(const QString &arg1)
{
    valeur=arg1;
    ui->tableView->setModel(tmpdestination.recherche(valeur,etat));
}

void integratedone::on_checkBox_stateChanged(int arg1)
{
    etat=arg1;
    ui->tableView->setModel(tmpdestination.recherche(valeur,etat));
}

void integratedone::on_trierChercher_textChanged(const QString &arg1)
{

    valeur=arg1;
    ui->tableView2->setModel(tmphotel.recherche(valeur,etat));
}

void integratedone::on_checkBox_2_stateChanged(int arg1)
{
    int b=arg1;
    etat=b;
    ui->tableView2->setModel(tmphotel.recherche(valeur,etat));

}

void integratedone::on_pushButton_clicked()
{
    QString receiver;
    QString objet;
    QString contenu;
    receiver = ui->receiver_line->text();
    objet = ui->about_line->text();
    contenu = ui->text_line->text();

    Smtp* smtp = new Smtp("nooblolsaibot1@gmail.com", "haboubax", "smtp.gmail.com", 465);
    if(smtp->sendMail("nooblolsaibot1@gmail.com",receiver,objet,contenu))
        QMessageBox::information(nullptr,QObject::tr("mail"),"Votre mail a été envoyé.");
}
void integratedone::on_Code_destination_ajouthotel_currentIndexChanged()
{
    destination d;
    d.setCode(ui->Code_destination_ajouthotel->currentText().toInt());
    tmpdestination.setCode(ui->Code_destination_ajouthotel->currentText().toInt());
    tmpdestination.chercher(d.getCode());

}

void integratedone::on_pushButton_2_clicked()
{
   // statistique *s = new statistique();
    //s->show();
}


// RESERVATIONS MODULE FUNCTIONS.

/*
void integratedone::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toUShort());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
*/
/*void integratedone::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
*/

// CRUD VOYAGE

void integratedone::on_reservervoyage_ajout_clicked()
{
    QString mail;
    tmpreservoyage.set_codedestination(ui->codedestination_rv_ajout->currentText().toInt());
    tmpreservoyage.set_numeropasseport(ui->numeropasseport_rv_ajout->currentText().toInt());
    tmpreservoyage.set_nomdestination(ui->nomdestination_rv->text());
    bool test=tmpreservoyage.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ajout d'un voyage "),
                                 QObject::tr("voyage ajouté.\n"
                                             "Click cancel to exit."), QMessageBox::Cancel);
        ui->tabresvoyage->setModel(tmpreservoyage.afficher());
        ui->reference_voyage_combo->setModel(tmpmodifvoyage.get_ref_ajoutes());
        ok.notification_ajout_destination(tmpreservoyage.get_nomdestination());
        mail=tmpreservoyage.retourMailClient();
        tmpreservoyage.mailing(mail);
    }
    else
    {

    }
}

void integratedone::on_datereservation_rv_ajout_userDateChanged(const QDate &date)
{
    tmpreservoyage.set_datederesevation(date.toString());
}

void integratedone::on_datedepart_rv_ajout_userDateChanged(const QDate &date)
{
    tmpreservoyage.set_datedeaprt(date.toString());
}

void integratedone::on_datearrivee_rv_ajout_userDateChanged(const QDate &date)
{
    tmpreservoyage.set_datearrivee(date.toString());
}


void integratedone::on_numeropasseport_rv_ajout_currentTextChanged(const QString &arg1)
{
    tmpreservoyage.set_numeropasseport(arg1.toInt());
}

void integratedone::on_typebillet_rv_ajout_currentTextChanged(const QString &arg1)
{
    tmpreservoyage.set_typebillet(arg1);
}

void integratedone::on_classe_rv_ajout_currentTextChanged(const QString &arg1)
{
    tmpreservoyage.set_classe(arg1);
}

void integratedone::on_datereservation_rv_modif_userDateChanged(const QDate &date)
{
    tmpmodifvoyage.set_datederesevation(date.toString());
}

void integratedone::on_datedepart_rv_modif_userDateChanged(const QDate &date)
{
    tmpmodifvoyage.set_datedeaprt(date.toString());
}

void integratedone::on_datearrivee_rv_modif_userDateChanged(const QDate &date)
{
    tmpmodifvoyage.set_datearrivee(date.toString());
}

void integratedone::on_rv_modifier_clicked()
{
    tmpmodifvoyage.set_classe(ui->classe_rv_modif->currentText());
    tmpmodifvoyage.set_datedeaprt(ui->datedepart_rv_ajout->text());
    tmpmodifvoyage.set_datearrivee(ui->datearrivee_rv_modif->text());
    tmpmodifvoyage.set_datederesevation(ui->datereservation_rv_modif->text());
    tmpmodifvoyage.set_typebillet(ui->typebillet_rv_modif->currentText());
    tmpmodifvoyage.set_refvoyage(ui->reference_voyage_combo->currentText().toInt());
    bool test = tmpmodifvoyage.modifier();
    if(test)
        ui->tabresvoyage->setModel(tmpreservoyage.afficher());
}
void integratedone::on_radioButton_clicked()
{
    ui->tabresvoyage->setModel(tmpreservoyage.trie_refvoyage());
}

void integratedone::on_radioButton_2_clicked()
{
    ui->tabresvoyage->setModel(tmpreservoyage.trie_destination());
}
void integratedone::on_supprimer_rv_clicked()
{
    reservervoyage sup;
    bool test = sup.supprimer(ui->reference_voyage_combo->currentText().toInt());
    if(test)
    {
        ui->reference_voyage_combo->setModel(tmpmodifvoyage.get_ref_ajoutes());
        ui->tabresvoyage->setModel(tmpreservoyage.afficher());
    }
}

//CRUD RESERVATION HOTEL

void integratedone::on_Ajout_rhotel_clicked()
{

    tmpajouth.set_duree(ui->duree_ajout->text().toInt());
    tmpajouth.set_idhotel(ui->idhotel_combobox->currentText().toInt());
    tmpajouth.set_numeropasseport(ui->numeropasseport_combobox->currentText().toInt());
    //tmpajouth.RetourNomHotel();
    tmpajouth.set_nom(ui->nomhotel_rhotel->text());
    tmpajouth.set_nomclient(ui->nomclient_rhotel->text());
    bool test=tmpajouth.ajouter();
    if(test)
    {
        ui->tabreshotel->setModel(tmpajouth.afficher());
        ui->numeropasseport_combobox->setModel(tmpajouth.NumeroPasseportModelHotel());
        ui->idhotel_supprimer->setModel(tmpajouth.NumeroPassePortReserverHotel());
        ok.notification_ajout_hotel(tmpajouth.get_nom());
    }
}
void integratedone::on_datereservation_ajout_userDateChanged(const QDate &date)
{
    tmpajouth.set_datederesevation(date.toString());
}

void integratedone::on_datearrivee_ajout_userDateChanged(const QDate &date)
{
    tmpajouth.set_datearrivee(date.toString());
}

void integratedone::on_datedepart_ajout_userDateChanged(const QDate &date)
{
    tmpajouth.set_datedeaprt(date.toString());
}


   /*
void integratedone::on_stat_bushonputt_clicked()
{
    cstat *s = new cstat();
    s->show();
}
   */
void integratedone::on_horizontalSlider_sliderMoved(int position)
{
    player->setVolume(position);
}

void integratedone::on_music_button_clicked()
{
    player->play();
}

void integratedone::on_mute_button_clicked()
{
    player->pause();
}

void integratedone::on_chercher_trier_rv_textChanged(const QString &arg1)
{
    QString seek = arg1;
    ui->tabresvoyage->setModel(tmpreservoyage.chercher(seek));
}





void integratedone::on_supprimer_rhotel_clicked()
{
    tmpreshotel.set_numeropasseport(ui->idhotel_supprimer->currentText().toInt());
    bool test=tmpreshotel.supprimer();
    if(test) {ui->tabreshotel->setModel(tmpreshotel.afficher());
        ui->idhotel_supprimer->setModel(tmpreshotel.NumeroPassePortReserverHotel());
        ui->numeropasseport_combobox->setModel(tmpreshotel.NumeroPasseportModelHotel());
    }
}
void integratedone::on_modifier_rhotel_clicked()
{
    tmpreshotel.set_numeropasseport(ui->idhotel_supprimer->currentText().toInt());
    tmpreshotel.set_duree(ui->rh_duree_modif->text().toInt());
    bool test=tmpreshotel.modifier();
    if(test)
        ui->tabreshotel->setModel(tmpreshotel.afficher());
}

void integratedone::on_rh_dater_modifier_userDateChanged(const QDate &date)
{
    tmpreshotel.set_datederesevation(date.toString());
}

void integratedone::on_rh_datea_modifier_userDateChanged(const QDate &date)
{
    tmpreshotel.set_datearrivee(date.toString());
}

void integratedone::on_rh_dated_modifier_userDateChanged(const QDate &date)
{
    tmpreshotel.set_datedeaprt(date.toString());
}

void integratedone::on_horizontalSlider_2_sliderMoved(int position)
{
    player->setVolume(position);
}
/*
void integratedone::on_pushButton_clicked()
{
    player->play();
}

void integratedone::on_pushButton_2_clicked()
{
    player->pause();
}
*/


void integratedone::on_idhotel_combobox_currentIndexChanged(const QString &arg1)
{
    QString nom=tmpajouth.RetourNomHotel(arg1);
    ui->nomhotel_rhotel->setText(nom);
}

void integratedone::on_numeropasseport_combobox_currentIndexChanged(const QString &arg1)
{
    QString nom=tmpajouth.retourNomClient(arg1.toInt());
    ui->nomclient_rhotel->setText(nom);
}

void integratedone::on_codedestination_rv_ajout_currentIndexChanged(const QString &arg1)
{
    QString name = tmpreservoyage.getNomDestinationFromtable(arg1.toInt());
    ui->nomdestination_rv->setText(name);
}




void integratedone::on_radioButton_3_clicked()
{
      ui->tabreshotel->setModel(tmpreshotel.trie_idhotel());
}

void integratedone::on_radioButton_4_clicked()
{
     ui->tabreshotel->setModel(tmpreshotel.trie_nomH());
}


void integratedone::on_lineEdit_textChanged(const QString &arg1)
{
    QString seek = arg1;
    ui->tabreshotel->setModel(tmpreshotel.chercher(seek));
}

// EVENTS-PROMOTIONS MODULE FUNCTIONS.


void  integratedone::refresh()
{
ui->tableView_evenement->setModel(tmpevenemant.afficher());
    ui->comboBox->setModel(tmpevenemant.afficher_list());
    ui->comboBox_5->setModel(tmpevenemant.afficher_list());

}





void integratedone::on_comboBox_supprimer_activated(const QString &arg1)
{
    ui->supp->setText(arg1);
}



void integratedone::on_consulter_stat_clicked()
{
     QSound::play("qrc:/boutton.wav");

    ui->tablestat->setModel(tmpevenemant.stats());
    statistique*a=new statistique();
    a->show();
}



void integratedone::on_pushbouton_print_clicked()
{QSound::play("qrc:/boutton.wav");
    QPrinter printer;
    printer.setPrinterName("fatima");
    QPrintDialog dialog(&printer,this);
    if(dialog.exec()==QDialog::Rejected)
       return;
       ui->textEdit_print->print(&printer);
}

void integratedone::on_comboBox_2_activated(const QString &arg1)
{

    ui->supp->setText(arg1);

}

/*void integratedone::on_comboBox_activated(const QString &arg1)
{

    tmpevenemant.setid(arg1);
         tmpevenemant.chercher();
    ui->nom->setText(tmpevenemant.get_nom());
    ui->lieu->setText(tmpevenemant.get_lieu());

}*/

void integratedone::on_supprimer_clicked()
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

void integratedone::on_dateDebut_userDateChanged(const QDate &date)
{

    tmpevenemant.setdateD(date.toString());
}

void integratedone::on_datefin_userDateChanged(const QDate &date)
{
    tmpevenemant.setdateF(date.toString());
}

void integratedone::on_dated_userDateChanged(const QDate &date)
{
     tmpevenemant.setdateD(date.toString());
}

void integratedone::on_datef_userDateChanged(const QDate &date)
{

    tmpevenemant.setdateF(date.toString());
}

void integratedone::on_modifier_clicked_clicked()
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

void integratedone::on_facebook_clicked()
{
    QString link="https://www.facebook.com/mustdotravels/";
    QDesktopServices::openUrl(QUrl(link));

}

void integratedone::on_TRI_clicked()
{
    ui->tableView_evenement->setModel(tmpevenemant.afficher_tri());
}

void integratedone::on_lineEdit_chercher_textChanged(const QString &arg1)
{
    ui->tableView_evenement->setModel(tmpevenemant.chercher_evenement(arg1));
}

void integratedone::on_pushButton_5_clicked()
{QSound::play("qrc:/boutton.wav");
    QString link="https://www.instagram.com/smart_travel_agency18/";
    QDesktopServices::openUrl(QUrl(link));
}

void integratedone::on_youtube_clicked()
{
QSound::play("qrc:/boutton.wav");
    QString link="https://www.youtube.com/watch?v=gG2ABStEDcw";
    QDesktopServices::openUrl(QUrl(link));
}

void integratedone::on_pushButton_7_clicked()
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

void integratedone::on_pushButton_6_clicked()
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


void integratedone::on_ajouterpro_clicked()
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

void integratedone::on_modifierpro_clicked()
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

void integratedone::on_supprimerpro_2_clicked()
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



void integratedone::on_ajouterevent_clicked()
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

void integratedone::on_comboBox_5_activated(const QString &arg1)
{

    tmpevenemant.setid(arg1);
         tmpevenemant.chercher();
    ui->nom->setText(tmpevenemant.get_nom());
    ui->lieu->setText(tmpevenemant.get_lieu());
}
