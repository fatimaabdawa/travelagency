#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reserverhotel.h"
#include "reservervoyage.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QComboBox>
#include "smtp.h"
#include "notification.h"
#include "cstat.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->centralWidget()->setStyleSheet("background-image:url(C:/Users/Pc Store/Desktop/background_travel.jpg); background-position:center;");
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
}
MainWindow::~MainWindow()
{
    delete ui;
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


// CRUD VOYAGE

void MainWindow::on_reservervoyage_ajout_clicked()
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

void MainWindow::on_datereservation_rv_ajout_userDateChanged(const QDate &date)
{
    tmpreservoyage.set_datederesevation(date.toString());
}

void MainWindow::on_datedepart_rv_ajout_userDateChanged(const QDate &date)
{
    tmpreservoyage.set_datedeaprt(date.toString());
}

void MainWindow::on_datearrivee_rv_ajout_userDateChanged(const QDate &date)
{
    tmpreservoyage.set_datearrivee(date.toString());
}


void MainWindow::on_numeropasseport_rv_ajout_currentTextChanged(const QString &arg1)
{
    tmpreservoyage.set_numeropasseport(arg1.toInt());
}

void MainWindow::on_typebillet_rv_ajout_currentTextChanged(const QString &arg1)
{
    tmpreservoyage.set_typebillet(arg1);
}

void MainWindow::on_classe_rv_ajout_currentTextChanged(const QString &arg1)
{
    tmpreservoyage.set_classe(arg1);
}

void MainWindow::on_datereservation_rv_modif_userDateChanged(const QDate &date)
{
    tmpmodifvoyage.set_datederesevation(date.toString());
}

void MainWindow::on_datedepart_rv_modif_userDateChanged(const QDate &date)
{
    tmpmodifvoyage.set_datedeaprt(date.toString());
}

void MainWindow::on_datearrivee_rv_modif_userDateChanged(const QDate &date)
{
    tmpmodifvoyage.set_datearrivee(date.toString());
}

void MainWindow::on_rv_modifier_clicked()
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
void MainWindow::on_radioButton_clicked()
{
    ui->tabresvoyage->setModel(tmpreservoyage.trie_refvoyage());
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->tabresvoyage->setModel(tmpreservoyage.trie_destination());
}
void MainWindow::on_supprimer_rv_clicked()
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

void MainWindow::on_Ajout_rhotel_clicked()
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
void MainWindow::on_datereservation_ajout_userDateChanged(const QDate &date)
{
    tmpajouth.set_datederesevation(date.toString());
}

void MainWindow::on_datearrivee_ajout_userDateChanged(const QDate &date)
{
    tmpajouth.set_datearrivee(date.toString());
}

void MainWindow::on_datedepart_ajout_userDateChanged(const QDate &date)
{
    tmpajouth.set_datedeaprt(date.toString());
}



void MainWindow::on_stat_bushonputt_clicked()
{
    cstat *s = new cstat();
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
    player->pause();
}

void MainWindow::on_chercher_trier_rv_textChanged(const QString &arg1)
{
    QString seek = arg1;
    ui->tabresvoyage->setModel(tmpreservoyage.chercher(seek));

}





void MainWindow::on_supprimer_rhotel_clicked()
{
    tmpreshotel.set_numeropasseport(ui->idhotel_supprimer->currentText().toInt());
    bool test=tmpreshotel.supprimer();
    if(test) {ui->tabreshotel->setModel(tmpreshotel.afficher());
        ui->idhotel_supprimer->setModel(tmpreshotel.NumeroPassePortReserverHotel());
        ui->numeropasseport_combobox->setModel(tmpreshotel.NumeroPasseportModelHotel());
    }
}
void MainWindow::on_modifier_rhotel_clicked()
{
    tmpreshotel.set_numeropasseport(ui->idhotel_supprimer->currentText().toInt());
    tmpreshotel.set_duree(ui->rh_duree_modif->text().toInt());
    bool test=tmpreshotel.modifier();
    if(test)
        ui->tabreshotel->setModel(tmpreshotel.afficher());
}

void MainWindow::on_rh_dater_modifier_userDateChanged(const QDate &date)
{
    tmpreshotel.set_datederesevation(date.toString());
}

void MainWindow::on_rh_datea_modifier_userDateChanged(const QDate &date)
{
    tmpreshotel.set_datearrivee(date.toString());
}

void MainWindow::on_rh_dated_modifier_userDateChanged(const QDate &date)
{
    tmpreshotel.set_datedeaprt(date.toString());
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    player->setVolume(position);
}

void MainWindow::on_pushButton_clicked()
{
    player->play();
}

void MainWindow::on_pushButton_2_clicked()
{
    player->pause();
}



void MainWindow::on_idhotel_combobox_currentIndexChanged(const QString &arg1)
{
    QString nom=tmpajouth.RetourNomHotel(arg1);
    ui->nomhotel_rhotel->setText(nom);
}

void MainWindow::on_numeropasseport_combobox_currentIndexChanged(const QString &arg1)
{
    QString nom=tmpajouth.retourNomClient(arg1.toInt());
    ui->nomclient_rhotel->setText(nom);
}

void MainWindow::on_codedestination_rv_ajout_currentIndexChanged(const QString &arg1)
{
    QString name = tmpreservoyage.getNomDestinationFromtable(arg1.toInt());
    ui->nomdestination_rv->setText(name);
}

