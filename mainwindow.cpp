#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QComboBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->idhotel_combobox->setModel(tmpreshotel.CodeModelHotel());
    ui->idhotel_supprimer->setModel(tmpreshotel.IdHotelReserverHotel());
    ui->numeropasseport_combobox->setModel(tmpreshotel.NumeroPasseportModelHotel());
    ui->numeropasseport_supprimer->setModel(tmpreshotel.NumeroPassePortReserverHotel());
    ui->tabresvoyage->setModel(tmpreservoyage.afficher());
    ui->tabreshotel->setModel(tmpreshotel.afficher());

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_idhotel_combobox_currentIndexChanged(const QString &arg1)
{
    QString arg=arg1;
    QString id= (ui->idhotel_combobox->currentText());
    QSqlQuery query;
    query.prepare("select * from hotel where nom='"+id+"'");
    query.exec();
    while(query.next())
    {
        ui->nomhotel_ajout->setText(query.value(4).toString());
    }
}

void MainWindow::on_Ajout_rhotel_clicked()
{
 QString nom = ui->nomhotel_ajout->text();
 tmpajouth.set_nom(nom);
 int idhotel = ui->idhotel_combobox->currentText().toInt();
 QDate datedepart = QDate::fromString(ui->datedepart_ajout->text());
 QDate dateretour = QDate::fromString(ui->datearrivee_ajout->text());
 QDate datereservation = QDate::fromString(ui->datereservation_ajout->text());
 int duree = ui->duree_ajout->text().toInt();

 int passeportnumber = ui->numeropasseport_combobox->currentText().toInt();
 reserverhotel rh(duree,idhotel,nom,datedepart,dateretour,datereservation,passeportnumber);
 bool test = rh.ajouter();
 if(test){
     ui->tabreshotel->setModel(tmpreshotel.afficher());
 }
}

void MainWindow::on_numeropasseport_combobox_currentIndexChanged(const QString &arg1)
{
    QString numeropasseport= ui->numeropasseport_combobox->currentText();
    QSqlQuery query;
    query.prepare("select * from CLIENT where NUMEROPASSEPORT='"+numeropasseport+"'");
    query.exec();
    while(query.next())
    {
        ui->nompasseport_ajout->setText(query.value(0).toString());
    }
}


void MainWindow::on_supprimer_rhotel_clicked()
{
    int numeropasseport = ui->numeropasseport_supprimer->currentText().toInt();
    int idhotel = ui->idhotel_supprimer->currentText().toInt();
    reserverhotel rh;
    bool supprime=rh.supprimer(idhotel,numeropasseport);
    if(supprime)
    {
     ui->tabreshotel->setModel(tmpreshotel.afficher());
    }
    else
    {

    }
}
int static refvoy = - 1;
void MainWindow::on_reservervoyage_ajout_clicked()
{

    int refvoyage = refvoy+1;
    int numpasseport = ui->numeropasseport_rv_ajout->currentText().toInt();
    int codedestination = ui->codedestination_rv_ajout->currentText().toInt();
    QString datedepart = ui->datedepart_rv_ajout->text();
    QString datearrivee = ui->datearrivee_rv_ajout->text();
    QString datereservation = ui->datereservation_rv_ajout->text();
    QString classe = ui->classe_rv_ajout->currentText();
    QString typebillet = ui->typebillet_rv_ajout->currentText();
    reservervoyage v(refvoyage, typebillet,classe,datedepart,datearrivee,datereservation, codedestination ,numpasseport);
    bool added=v.ajouter();
    if(added)
    {
      ui->tabresvoyage->setModel(tmpreservoyage.afficher());
    }
    else
    {

    }

}

void MainWindow::on_codedestination_rv_ajout_currentIndexChanged(const QString &arg1)
{
    QString idhotel = arg1;
    QSqlQuery query;
    query.exec("select nom from hotel where idhotel='"+idhotel+"'");
    while(query.next())
    {
        ui->nomdestination_rv_ajout->setText(query.value(0).toString());
    }

}

void MainWindow::on_modifier_rhotel_clicked()
{
    QString id;
}

void MainWindow::on_datereservation_ajout_userDateChanged(const QDate &date)
{
    tmpajouth.set_datederesevation(date);
}



void MainWindow::on_idhotel_supprimer_currentIndexChanged(const QString &arg1)
{
    QString idhotel= ui->idhotel_supprimer->currentText();
    QSqlQuery query;
    query.prepare("select * from reserverhotel where idhotel='"+idhotel+"'");
    query.exec();
    while(query.next())
    {
        ui->rh_duree_modif->setText(query.value(5).toString());
        ui->rh_datea_modifier->setDate(query.value(3).toDate());
        ui->rh_dater_modifier->setDate(query.value(4).toDate());
        ui->rh_dated_modifier->setDate(query.value(2).toDate());

    }
}
