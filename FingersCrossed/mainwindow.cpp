#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDialog>
#include <QString>
#include <QSqlQueryModel>
#include <QMessageBox>
#include "hotel.h"
#include <QPixmap>
#include <QComboBox>
#include "notification.h"
#include "smtp.h"
#include "qcustomplot.h"
#include "statistique.h"
#include <QTime>
#include <QMainWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ok.notification_Ouverture("GESTION HOTELS/DESTINATIONS");
    ui->tableView->setModel(tmpdestination.afficher());
    ui->tableView2->setModel(tmphotel.afficherH());
    ui->comboBox->setModel(tmpdestination.ModelCodeDestinations());
    ui->comboBox_2->setModel(tmphotel.ModelidhotelHotel());
    ui->idhotel_asupprimer->setModel(tmphotel.ModelidhotelHotel());
    ui->Code_destination_ajouthotel->setModel(tmpdestination.ModelCodeDestinations());
    ui->code_asupprimer->setModel(tmpdestination.ModelCodeDestinations());
    QPixmap back1("C:/Users/Haboub/Pictures/Wallpapers/witcherHorizon.jpg");
    QPixmap back2("C:/Users/Haboub/Pictures/Wallpapers/trave1background.jpg");
    QPixmap back3("C:/Users/Haboub/Pictures/Wallpapers/hotel1background.jpg");
    QPixmap back4("C:/Users/Haboub/Pictures/Wallpapers/hotel2background.jpg");
    player->setMedia(QUrl("C:/Users/Haboub/Desktop/Musi9/Daryl Hall & John Oates - Maneater (Official Music Video).mp3"));

    ui->promo_aajouter->setValidator(new QRegExpValidator(QRegExp("[0-1]"),this));
    ui->nom_aajout->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z-0-9]+"),this));
    //ui->description_aajouter->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z-0-9]+"),this));
    ui->promo_amodifier->setValidator(new QRegExpValidator(QRegExp("[0-1]"),this));
    ui->nom_amodifier->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z-0-9]+"),this));
    //ui->description_amodifier->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z-0-9]+"),this));

    ui->cout_ajout_hotel->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));
    ui->couthotel_amodifier->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));
    ui->etoiles_ajout_hotel->setValidator(new QRegExpValidator(QRegExp("[0-9]"),this));
    ui->etoileshotel_amodifier->setValidator(new QRegExpValidator(QRegExp("[0-9]"),this));




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_destination_clicked()
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

void MainWindow::on_SupprimerDestination_clicked()
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

void MainWindow::on_ajouter_hotel_clicked()
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


void MainWindow::on_supprimer_hotel_clicked()
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


void MainWindow::on_comboBox_currentIndexChanged()
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

void MainWindow::on_Modifier_clicked()
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

void MainWindow::on_comboBox_2_currentIndexChanged()
{
    tmphotel.setiIdhotel(ui->comboBox_2->currentText().toInt());
    tmphotel.chercher();
    ui->nomhotel_amodifier->setText(tmphotel.getNom());
    ui->adressehotel_amodifier->setText(tmphotel.getAdresse());
    ui->etoileshotel_amodifier->setText(QString::number(tmphotel.getEtoiles()));
    ui->couthotel_amodifier->setText(QString::number(tmphotel.getCout_par_nuit()));

}

void MainWindow::on_ModifierHotel_clicked()
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

void MainWindow::on_trierChercher_2_textChanged(const QString &arg1)
{
    valeur=arg1;
    ui->tableView->setModel(tmpdestination.recherche(valeur,etat));
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    etat=arg1;
    ui->tableView->setModel(tmpdestination.recherche(valeur,etat));
}

void MainWindow::on_trierChercher_textChanged(const QString &arg1)
{

    valeur=arg1;
    ui->tableView2->setModel(tmphotel.recherche(valeur,etat));
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    int b=arg1;
    etat=b;
    ui->tableView2->setModel(tmphotel.recherche(valeur,etat));

}

void MainWindow::on_pushButton_clicked()
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
void MainWindow::on_Code_destination_ajouthotel_currentIndexChanged()
{
    destination d;
    d.setCode(ui->Code_destination_ajouthotel->currentText().toInt());
    tmpdestination.setCode(ui->Code_destination_ajouthotel->currentText().toInt());
    tmpdestination.chercher(d.getCode());

}

void MainWindow::on_pushButton_2_clicked()
{
    statistique *s = new statistique();
    s->show();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    player->setVolume(position);
}

void MainWindow::on_music_button_clicked()
{
    player->play();
}

void MainWindow::on_mute_button_clicked()
{
    player->stop();
}
