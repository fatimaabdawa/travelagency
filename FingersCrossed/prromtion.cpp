#include "prromtion.h"
#include <QDebug>
#include<QString>
#include <QSqlQuery>
#include<QSqlQueryModel>
prromtion::prromtion()
{
    id=0;
   Ddebut="";
   Dfin="";
   pourcentage=0;

}
prromtion::prromtion(int id,QString Ddebut,QString Dfin,int pourcentage)
{
  this->id=id;
  this->Ddebut=Ddebut;
  this->Dfin=Dfin;
  this->pourcentage=pourcentage;

}
int prromtion::get_id(){return  id;}
QString prromtion::get_Ddebut()
{
    return  Ddebut;
}

QString prromtion::get_Dfin(){return Dfin;}
int prromtion::get_pourcentage(){return  pourcentage;}

bool prromtion::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO PROMOTION (ID,DATEDEBUT,DATEFIN,POURCENTAGE)" "VALUES(:id,:Ddebut,:Dfin,:pourcentage)");
query.bindValue(":id",id);
query.bindValue(":Ddebut",Ddebut);
query.bindValue(":Dfin",Dfin);
query.bindValue(":pourcentage",pourcentage);
return    query.exec();
}
 QSqlQueryModel * prromtion::afficher()
 { QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from promotion");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATEDEBUT "));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATEFIN"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("POURCENTAGE"));

         return model;
 }
bool prromtion::supprimer(int idd)
{ QSqlQuery query;
    QString res= QString::number(idd);
    query.prepare("Delete from promotion where ID = :id ");
    query.bindValue(":id", res);
    return    query.exec();
}
bool prromtion::modifier(int id, QString Ddebut, QString Dfin, int pourcentage)
{
    QSqlQuery query;
    query.prepare("update promotion set DATEDEBUT=:DATEDEBUT,DATEFIN=:DATEFIN,POURCENTAGE=:POURCENTAGE where ID=:ID ");
    query.bindValue(":ID",id);
    query.bindValue(":DATEDEBUT",Ddebut);
    query.bindValue(":DATEFIN",Dfin);
    query.bindValue(":POURCENTAGE",pourcentage);



   return query.exec();




}
