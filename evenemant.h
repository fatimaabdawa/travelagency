#ifndef EVENEMANT_H
#define EVENEMANT_H
#include <QSqlQueryModel>

class evenemant
{

public:
    evenemant();
    evenemant(QString,QString,QString,QString,QString);
    QString get_id();
    QString get_dateD();
    QString get_dateF();
    QString get_nom();
    QString get_lieu();
    void setid(QString);
    void setdateD(QString);
    void setdateF(QString);
    void setnom(QString);
    void setlieu(QString);
QSqlQueryModel * afficher();
void chercher();
bool supprimer(QString);
bool ajouter();
bool modifier();
QSqlQueryModel * stats();
QSqlQueryModel* afficher_list();
private:
QString id,dateD,dateF,nom,lieu;

};

#endif // EVENEMANT_H
