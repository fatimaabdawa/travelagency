#include "employeform.h"
#include "ui_employeform.h"
#include "employe.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QDateEdit>
#include<QUuid>
#include <time.h>
#include"contrat.h"
#include<QPrinter>
#include<QPrintDialog>
#include<QTextDocument>
#include<QTextStream>
employeform::employeform(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::employeform)
{
    ui->setupUi(this);
    ui->tabemploye->setModel(tmpemploye.afficher());
}

employeform::~employeform()
{
    delete ui;
}

void employeform::on_pushButton_clicked()
{
    QDate date_debut= ui->dateEdit_4->date();
    QDate date_fin=ui->dateEdit_5->date();
    int salaire=ui->lineEdit_20->text().toInt();
    int ref=ui->lineEdit_21->text().toInt();
    int jourabs=0;
    int idemp=ui->lineEdit_3->text().toInt();
    QString nom=ui->lineEdit->text();
    QString prenom=ui->lineEdit_2->text();
    QString departement=ui->departement_box->currentText();
    employe e(idemp,jourabs,nom,prenom,departement);
    contrat c(date_debut,date_fin,ref,idemp,salaire);
    if((e.ajouter())&&(c.ajouter()))
    {


        ui->tabemploye->setModel(tmpemploye.afficher());


        QMessageBox::information(nullptr,QObject::tr("Ajout"),"Ajout effectué");

    }
    else QMessageBox::information(nullptr,QObject::tr("Ajout"),"ajout impossible");
}


void employeform::on_pushButton_2_clicked()
{
    int idemp =ui-> lineEdit_5->text().toInt();
    bool test=tmpemploye.supprimer(idemp);
    if(test)
    {ui->tabemploye->setModel(tmpemploye.afficher());

        QMessageBox::information(nullptr,QObject::tr("suppression"),"employé supprimé");
    }

}

void employeform::on_pushButton_3_clicked()
{
    int idemp =ui-> lineEdit_5->text().toInt();
    int jourabs=ui->lineEdit_7->text().toInt();
    QString nom=ui->lineEdit_8->text();
    QString prenom=ui->lineEdit_9->text();
    QString departement=ui->lineEdit_10->text();
    QDate date_fin=ui->dateEdit->date();
    int salaire=ui->lineEdit_6->text().toInt();
    contrat c;
    employe e;

    bool y= ((e.update(nom,prenom,departement,jourabs,idemp))or (c.update(salaire,date_fin,idemp)));

    if(y)

    {ui->tabemploye->setModel(tmpemploye.afficher());

        QMessageBox::information(nullptr,QObject::tr("modification employe"),"modification fait");
    }
    else{
        QMessageBox::information(nullptr,QObject::tr("modification employe"),"modification pas fait");
    }
}
void employeform::on_pushButton_4_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tabemploye->model()->rowCount();
    const int columnCount = ui->tabemploye->model()->columnCount();
    QString TT = QDate::currentDate().toString("dd/mm/yyyy");
    out <<"<html>\n"
          "<head>\n"
          "<meta Content=\"Text/html; charset=Windows-1251\">\n"
       << "<title>ERP - COMmANDE LIST<title>\n "
       << "</head>\n"
          "<body bgcolor=#ffffff link=#5000A0>\n"
          "<h1 style=\"text-align: center;\"><strong> ******LISTE DES EMPLOYEES ****** "+TT+"</strong></h1>"
                                                                                            "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                                                                                            "</br> </br>";
    // headers
    out << "<thead><tr bgcolor=#d6e5ff>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tabemploye->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tabemploye->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tabemploye->isColumnHidden(column)) {
                QString data =ui->tabemploye->model()->data(ui->tabemploye->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
            "</body>\n"
            "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;

}


void employeform::on_pushButton_5_clicked()
{

    ui->tableView->setModel(tmpemploye.empmois());
}

void employeform::on_seeker_line_textChanged(const QString &arg1)
{
  valeur = arg1;
  ui->tabemploye->setModel(tmpemploye.trieasc(valeur,etat));
}

void employeform::on_ascendingsearch_clicked()
{
    etat = 1;
   ui->tabemploye->setModel(tmpemploye.trieasc(valeur,etat));
}

void employeform::on_descendingsearch_clicked()
{
    etat=0;
      ui->tabemploye->setModel(tmpemploye.trieasc(valeur,etat));
}
