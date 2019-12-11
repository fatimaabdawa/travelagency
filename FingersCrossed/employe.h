#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class employe
{
public:

    employe();
    employe(int,int,QString,QString,QString);
    ~employe();
QString get_nom();
QString get_prenom();
QString get_departement();
int get_idemp();
int get_jourabs();
//crude
bool ajouter();
QSqlQueryModel *afficher();
bool supprimer(int);
bool update(QString,QString,QString,int,int);
//metier
QSqlQueryModel *trieasc(QString,int);
QSqlQueryModel *empmois();
bool redsalair(int,int);
 private:
QString nom,prenom,departement;
int idemp,jourabs;

};


#endif // EMPLOYE_H
