#ifndef PRROMTION_H
#define PRROMTION_H
#include <QSqlQueryModel>

class prromtion
{
public:
    prromtion();
    prromtion(int,QString,QString,int);
    int get_id();
    QString get_Ddebut();
    QString get_Dfin();
    int get_pourcentage();

     bool ajouter();
QSqlQueryModel * afficher();
bool supprimer(int);
bool modifier(int id, QString Ddebut, QString Dfin, int pourcentage);
 private:
     QString Ddebut,Dfin;
     int id,pourcentage;


};

#endif // PRROMTION_H
