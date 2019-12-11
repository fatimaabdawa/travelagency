#ifndef CONTRAT_H
#define CONTRAT_H
#include "employe.h"
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
class contrat
{
public:
    contrat();
    ~contrat();
    contrat(QDate ,QDate ,int,int,int);
    QDate get_datedebut();
    QDate get_datefin();
    int get_salaire();
    int get_ref();
    int get_idemp();
//crude
   bool ajouter();
   bool update(int,QDate,int);
   bool supprimer(int);
//autre
   QSqlQueryModel *rechercher();
private:
   QDate date_debut,date_fin;
   int salaire,ref,idemp;
};

#endif // CONTRAT_H
