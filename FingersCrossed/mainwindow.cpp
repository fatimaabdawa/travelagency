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
#include "historique.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers );
    ui->tableView2->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ok.notification_Ouverture("GESTION HOTELS/DESTINATIONS");
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


    m->setMedia(QUrl::fromLocalFile("C:/Users/Haboub/Documents/FingersCrossed/click.mp3"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NewAddedMail(QString name, QString receiver)
{
    Smtp* smtp = new Smtp("nooblolsaibot1@gmail.com", "haboubax", "smtp.gmail.com", 465);
    if(smtp->sendMail("nooblolsaibot1@gmail.com",receiver,"","Une nouvelle destination "+name+" a été ajouté au répertoire"))
        QMessageBox::information(nullptr,QObject::tr("mail"),"Votre mail a été envoyé.");
}


void MainWindow::on_ajouter_destination_clicked()
{
    m->play();
    tmpdestination.setPromo( ui->promo_aajouter->text().toInt());
    tmpdestination.setNom(ui->nom_aajout->text());
    tmpdestination.setDescription(ui->description_aajouter->text());
    QString nom=ui->nom_aajout->text();
    if(ui->nom_aajout->hasAcceptableInput() && ui->promo_aajouter->hasAcceptableInput()){
    bool test=tmpdestination.ajouter();
    if(test)
    {
        ok.notification_ajout_destination(nom);
        //NewAddedMail(nom,receiver);
        ui->tableView->setModel(tmpdestination.afficher());
        ui->comboBox->setModel(tmpdestination.ModelCodeDestinations());
        ui->code_asupprimer->setModel(tmpdestination.ModelCodeDestinations());
        QMessageBox::information(nullptr,QObject::tr("Ajout Destination"),"Destination Ajoutée");

        //HISTORIQUE
        QString textajouter;
            QString nom;
            historique h;
            QSqlQuery qry;
            qry.prepare("select * from destination");
            if (qry.exec())
            {
                while (qry.next())
                {
        nom =qry.value(0).toString();
                }
            }

            textajouter="L'ajout d'un produit dans la base de donnees de reference = "+nom+" a ete effectuee avec succees";
            h.write(textajouter);


    }

    }

}

void MainWindow::on_SupprimerDestination_clicked()
{
    m->play();
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
    m->play();
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
    m->play();
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
    m->play();
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
    m->play();
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
    m->play();
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
    m->play();
    int b=arg1;
    etat=b;
    ui->tableView2->setModel(tmphotel.recherche(valeur,etat));

}

void MainWindow::on_pushButton_clicked()
{
    m->play();
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
    m->play();
    player->play();
}

void MainWindow::on_mute_button_clicked()
{
    m->play();
    player->stop();
}

void MainWindow::on_ascendingtr_clicked()
{
    m->play();
    etat = 1;
    ui->tableView->setModel(tmpdestination.recherche(valeur,etat));
}

void MainWindow::on_descendingtr_clicked()
{
    m->play();
    etat = 0;
    ui->tableView->setModel(tmpdestination.recherche(valeur,etat));
}

void MainWindow::on_ascend_clicked()
{
    m->play();
    etat = 1;
    ui->tableView2->setModel(tmphotel.recherche(valeur,etat));
}

void MainWindow::on_descend_clicked()
{
    m->play();
    etat = 0;
    ui->tableView2->setModel(tmphotel.recherche(valeur,etat));
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    m->play();
    QString val =ui->tableView->model()->data(index).toString();
    int ivl = ui->tableView->model()->data(index).toInt();
    tmpdestination.pkeor(val,ivl);
    int ofkepw = tmpdestination.getCode();
    QString code = QString::number(ofkepw);
    ui->comboBox->setCurrentText(code);
    QString promotion = QString::number(tmpdestination.getPromo());
    ui->nom_amodifier->setText(tmpdestination.getNom());
    ui->description_amodifier->setText(tmpdestination.getDescription());
    ui->promo_amodifier->setText(promotion);

}

void MainWindow::on_tableView2_activated(const QModelIndex &index)
{
    m->play();

    QString vl = ui->tableView2->model()->data(index).toString();
    int ivl = ui->tableView2->model()->data(index).toInt();
    tmphotel.pkeor(vl,ivl);
    QString etl = QString::number(tmphotel.getEtoiles());
    QString cpn = QString::number(tmphotel.getCout_par_nuit());

    ui->nomhotel_amodifier->setText(tmphotel.getNom());
    ui->etoileshotel_amodifier->setText(etl);
    ui->couthotel_amodifier->setText(cpn);
    ui->adressehotel_amodifier->setText(tmphotel.getAdresse());

    QString ihdotel = QString::number(tmphotel.getId_hotel());

    ui->comboBox_2->setCurrentText(ihdotel);

}

void MainWindow::on_historique_clicked()
{
    m->play();
        ui->tableView->hide();
        historique h;
        ui->textBrowser->show();
        ui->textBrowser->setPlainText(h.read());
}

void MainWindow::on_historique_2_clicked()
{
    m->play();
    ui->textBrowser->hide();
    ui->tableView->show();
}
