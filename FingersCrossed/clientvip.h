#ifndef CLIENTVIP_H
#define CLIENTVIP_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class clientvip
{
public:
    bool fctqverifmail(QString);
    bool fctqverinp(int np);
    clientvip();
    clientvip(QString,QString,int,QString,QString,QString,int,int=0);
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher2(QString);

    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QString,QString,int);
    void recherche ();
    QString getnom();
    QString getprenom();
    QString getmail();
    QString getprofession();
    QString getpays();
    int getage();
    int getnumeropasseport();
    int getpoints();
    QSqlQueryModel * GetNumpassModel();
    void set_numpasseport(int numeropasseport){
        this->numeropasseport=numeropasseport;
    }


private:
    QString nom,prenom,mail,profession,pays;
    int numeropasseport,points,age;
};

#endif // CLIENTVIP_H
