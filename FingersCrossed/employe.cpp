#include "employe.h"
#include<QApplication>

employe::~employe()
{

}
employe::employe()
{
idemp=0;
nom="";
prenom="";
jourabs=0;
}
employe::employe(int idemp,int joursabs, QString nom, QString prenom,QString departement)
{
    this->idemp=idemp;
    this->nom=nom;
    this->prenom=prenom;
    this->departement=departement;
    this->jourabs=joursabs;
}
QString employe::get_nom(){return nom;}
QString employe::get_prenom(){return prenom;}
QString employe ::get_departement(){return departement;}
int employe::get_idemp(){return idemp;}
int employe::get_jourabs(){return jourabs;}
bool employe::ajouter()
{
    QSqlQuery query;
   // QString res=QString::number(idemp);
    query.prepare("insert into employe(nom,idemp,prenom,departement,joursabsc)values(:nom,HABIB.SALAH_IDEMP.nextval,:prenom,:departement,:joursabs)");
    //query.bindValue(":idemp",idemp);
    query.bindValue(":joursabs",jourabs);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":departement",departement);
    return query.exec();
}
QSqlQueryModel *employe::afficher()
{QSqlQueryModel * model=new QSqlQueryModel;
model->setQuery("select * from employe JOIN contrat ON employe.idemp= contrat.idemp ");
model->setHeaderData(1,Qt::Horizontal,QObject::tr("id employe"));
model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("departement"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("jours abscences"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("ref contrat"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("id employe"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("salaire/mois"));
model->setHeaderData(8,Qt::Horizontal,QObject::tr("date debut"));
model->setHeaderData(9,Qt::Horizontal,QObject::tr("date fin"));
        return model;
}

 bool employe::supprimer(int idemp)
{
     QSqlQuery query;
    QString res=QString::number(idemp);
    query.prepare("delete from employe where idemp= :idemp ");
    query.bindValue(":idemp",res);
    return query.exec();
}



bool employe::update(QString nom, QString prenom, QString departement, int jourabs,int idemp)
{
QSqlQuery query;
QString yep=QString::number(idemp);
query.prepare("update employe set nom=:nom,prenom=:prenom,departement=:departement,joursabsc=:joursabs where idemp='"+yep+"'");
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":departement",departement);
query.bindValue(":joursabs",jourabs);
return query.exec();
}
QSqlQueryModel *employe::trieasc(QString valeur, int etat)
{

    QSqlQueryModel * model=new QSqlQueryModel();

    QSqlQuery query;
    if(etat==1)
    { query.prepare("SELECT * FROM employe JOIN contrat ON  employe.idemp = contrat.idemp WHERE NOM LIKE :valeur OR departement LIKE :valeur order by NOM");}
    else
    { query.prepare("SELECT * FROM employe JOIN contrat ON  employe.idemp = contrat.idemp WHERE NOM LIKE :valeur OR departement LIKE :valeur order by NOM");}
    valeur="%"+valeur+"%";
    query.bindValue(":valeur",valeur);
    query.exec();
   model->setQuery(query);
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDemp"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("Departement"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("Joursabsc"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("Ref"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("id employe"));
   model->setHeaderData(7,Qt::Horizontal,QObject::tr("salaire/mois"));
   model->setHeaderData(8,Qt::Horizontal,QObject::tr("date debut"));
   model->setHeaderData(9,Qt::Horizontal,QObject::tr("date fin"));
    return model;



   /*
    *
    *
    *
 QSqlQueryModel *model=new QSqlQueryModel ;
 QSqlQuery query;

   query.prepare("SELECT *FROM employe order by joursabsc ");
   model->setQuery(query);
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("idemp"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("departement"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("jours abscence"));
   return model;
   */

}
QSqlQueryModel *employe::empmois()
{
    QSqlQueryModel *model=new QSqlQueryModel ;
    QSqlQuery query;
    query.prepare("select count(idemp)as nombre,departement from employe group by departement");
    query.exec();
    model->setQuery(query);
    return model;
}

QSqlQueryModel *employe::salaireavg()
{
    QSqlQueryModel *model=new QSqlQueryModel ;
    QSqlQuery query;
    query.prepare("select avg(salaire) as salaire_moyen from contrat");
    query.exec();
    model->setQuery(query);
    return model;
}
