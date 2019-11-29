#include "mainwindow.h"
#include "ui_mainwindow.h"
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ok.notification_Ouverture("GESTION HOTELS/DESTINATIONS");
    ui->tableView->setModel(tmpdestination.afficher());
    ui->tableView2->setModel(tmphotel.afficherH());
    ui->comboBox->setModel(tmpdestination.ModelCodeDestinations());
    ui->comboBox_2->setModel(tmphotel.ModelidhotelHotel());
    //ui->Code_destination_ajouthotel->setModel(tmpdestination.ModelCodeDestinations());
    QPixmap back1("C:/Users/Haboub/Pictures/Wallpapers/witcherHorizon.jpg");
    QPixmap back2("C:/Users/Haboub/Pictures/Wallpapers/trave1background.jpg");
    QPixmap back3("C:/Users/Haboub/Pictures/Wallpapers/hotel1background.jpg");
    QPixmap back4("C:/Users/Haboub/Pictures/Wallpapers/hotel2background.jpg");
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
    bool test=tmpdestination.ajouter();
    if(test)
    {
        ok.notification_ajout_destination(nom);
        ui->tableView->setModel(tmpdestination.afficher());
        ui->comboBox->setModel(tmpdestination.ModelCodeDestinations());
        QMessageBox::information(nullptr,QObject::tr("Ajout Destination"),"Destination Ajoutée");
    }

}

void MainWindow::on_SupprimerDestination_clicked()
{
    int code= ui->code_asupprimer->text().toInt();

    bool test=tmpdestination.supprimer(code);
    if(test)
    {
        ui->tableView->setModel(tmpdestination.afficher());
        ui->comboBox->setModel(tmpdestination.ModelCodeDestinations());
        ui->code_asupprimer->setText("");
    }
    else
    {

    }
}

void MainWindow::on_ajouter_hotel_clicked()
{
    tmphotel.setiIdhotel(ui->id_ajout_hotel->text().toInt());
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
        QMessageBox::information(nullptr,QObject::tr("Ajout Hotel"),"Well done sire!");
    }else
        QMessageBox::information(nullptr,QObject::tr("Ajout Hotel"),"ERROR MY LIEGE");
}


void MainWindow::on_supprimer_hotel_clicked()
{
    tmphotel.setiIdhotel(ui->idhotel_asupprimer->text().toInt());
    bool test=tmphotel.supprimer();
    if(test)
    {
        ui->tableView2->setModel(tmphotel.afficherH());
        QMessageBox::information(nullptr,QObject::tr("Suppression Hotel"),"Well done sire!");
    }
    else
        QMessageBox::information(nullptr,QObject::tr("Suppression Hotel"),"ERROR MY LIEGE");
}


void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
        tmpdestination.setCode(ui->comboBox->currentText().toInt());
        tmpdestination.chercher();
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

void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    QString idhotel = QString::number(arg1.toInt());
    QSqlQuery query;
    tmphotel.setiIdhotel(ui->comboBox_2->currentText().toInt());
    tmphotel.chercher();
    while(query.next())
    {
        ui->nomhotel_amodifier->setText(tmphotel.getNom());
        ui->adressehotel_amodifier->setText(tmphotel.getAdresse());
        ui->etoileshotel_amodifier->setText(QString::number(tmphotel.getEtoiles()));
        ui->couthotel_amodifier->setText(QString::number(tmphotel.getCout_par_nuit()));
    }
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

void MainWindow::on_mail_button_clicked()
{
    Smtp* smtp = new Smtp("nooblolsaibot1@gmail.com", "haboubax", "smtp.gmail.com", 465);
    if(smtp->sendMail("nooblolsaibot1@gmail.com","oussema.benjabli@esprit.tn" , "YAAAY","MAILING T5DM"))
        QMessageBox::information(nullptr,QObject::tr("mail"),"séntmail wéll doné siré");
}




void MainWindow::on_TabDestinations_tabBarClicked(int index)
{
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
        x[i] = i/50.0 - 1; // x goes from -1 to 1
        y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x,y,0);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(-1, 1);
    ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->replot();
}
void MainWindow::on_pushButton_clicked()
{
    statistique * e = new statistique();
    setWindowModality(Qt::WindowModal);
    e->show();
}

void MainWindow::on_Code_destination_ajouthotel_currentIndexChanged(const QString &arg1)
{
    tmpdestination.setCode(ui->Code_destination_ajouthotel->currentText().toInt());
    tmpdestination.chercher();
    ui->affichage_nomDestHotel->setText(QString::number(tmpdestination.getCode()));
}
