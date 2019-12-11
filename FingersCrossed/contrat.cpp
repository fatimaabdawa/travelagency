#include "contrat.h"
contrat::contrat()
{

}
contrat::~contrat(){};
QDate contrat:: get_datedebut(){return date_debut;}
QDate contrat::get_datefin(){return date_fin;}
int contrat::get_salaire(){return salaire;}
int contrat::get_ref(){return ref;}
int contrat::get_idemp(){return idemp;}
contrat::contrat(QDate date_debut , QDate date_fin, int ref, int idemp,  int salaire)
{
this->ref=ref;
this->idemp=idemp;
this->salaire=salaire;
this->date_fin= date_fin;
this->date_debut= date_debut;
}
bool contrat::ajouter()
{
    QSqlQuery query;
    query.prepare("insert into contrat(ref,idemp,salaire,datedebut,datefin)values(HABIB.SALAH_REF.nextval,HABIB.SALAH_IDEMP.CURRVAL,:salaire,:date_debut,:date_fin)");
    //query.bindValue(":ref",ref);
    query.bindValue(":idemp",idemp);
    query.bindValue(":salaire",salaire);
    query.bindValue(":date_debut",date_debut);
    query.bindValue(":date_fin",date_fin);
return query.exec();
}

bool contrat::supprimer(int idemp)
{
    QSqlQuery query;
   QString res=QString::number(idemp);
   query.prepare("delete from contrat where idemp= :idemp ");
   query.bindValue(":idemp",res);
   return query.exec();
}
bool contrat::update(int salaire,QDate date_fin, int idemp)
{
    QSqlQuery query;
    QString res=QString::number(idemp);
    query.prepare("update contrat set salaire=:salaire,datefin=:date_fin where idemp='"+res+"'");
    query.bindValue(":salaire",salaire);
    query.bindValue(":datefin",date_fin);
    return  query.exec();
}
