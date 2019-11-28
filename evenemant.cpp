#include "evenemant.h"
#include <QDebug>
#include<QString>
#include <QSqlQuery>
#include<QSqlQueryModel>
evenemant::evenemant()
{
    id="";
   dateD="";
   dateF="";
   nom="";
   lieu="";

}
evenemant::evenemant(QString id,QString dateD,QString dateF,QString nom,QString lieu )
{
    this->id=id;
  this->dateD=dateD;
  this->dateF=dateF;
  this->nom=nom;
  this->lieu=lieu;

}

QString evenemant::get_id()
{
    return id;
}
QString evenemant::get_dateD()
{
    return  dateD;
}

QString evenemant::get_dateF(){return dateF;}
QString evenemant::get_nom(){return nom;}
QString evenemant::get_lieu(){return lieu;}
void evenemant::setdateD(QString dateD)
{
    this->dateD=dateD;
}
void evenemant::setdateF(QString dateF)
{
    this->dateF=dateF;
}
void evenemant::setnom(QString nom)
{
    this->nom=nom;
}
void evenemant::setlieu(QString lieu)
{
    this->lieu=lieu;
}
void evenemant::setid(QString id)
{
    this->id=id;
}

void evenemant::chercher()
{
    QSqlQuery query1;
    query1.prepare("SELECT DATEDEBIT,DATEFIN,NOM,LIEU FROM EVENEMENT WHERE ID=:ID");
    query1.bindValue(":ID",id);
    query1.exec();
    while(query1.next())
    {

    dateD = query1.value(0).toString();
    dateF = query1.value(1).toString();
    nom = query1.value(2).toString();
   lieu = query1.value(3).toString();

    }
 }




bool evenemant::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO EVENEMENT (ID,DATEDEBIT,DATEFIN,NOM,LIEU)"
              "VALUES(:id,:dateD,:dateF,:nom,:lieu)");
query.bindValue(":id",id);
query.bindValue(":dateD",dateD);
query.bindValue(":dateF",dateF);
query.bindValue(":nom",nom);
query.bindValue(":lieu",lieu);
return query.exec();
}

QSqlQueryModel * evenemant::afficher()
{ QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from evenement");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATEDEBIT "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATEFIN"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("LIEU"));
     return model;
}


bool evenemant::modifier()
{
     QSqlQuery query;
     query.prepare("update evenement set DATEDEBIT=:DATEDEBIT,DATEFIN=:DATEFIN,NOM=:NOM,LIEU=:LIEU where ID=:ID ");
     query.bindValue(":ID",id);
     query.bindValue(":DATEDEBIT",dateD);
     query.bindValue(":DATEFIN",dateF);
     query.bindValue(":NOM",nom);
     query.bindValue(":LIEU",lieu);


    return query.exec();



}

QSqlQueryModel * evenemant::stats()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT NOM, LIEU,((NOM*100)/(select SUM(NOM) from evenement) from evenement");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("lieu"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("stats"));

        return model;
}


QSqlQueryModel * evenemant::afficher_list()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select id from evenement");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("id"));
return model;
}

bool evenemant::supprimer(QString id)
{
    QSqlQuery query;
    query.prepare("delete from evenement where ID = :id ");
    query.bindValue(":id",id);
    return query.exec();

}


