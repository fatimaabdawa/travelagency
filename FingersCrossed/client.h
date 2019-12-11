#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class client
{
public:
    bool fctqverifmail(QString);
    bool fctqverinp(int np);

    QSqlQuery fctq();
    QSqlQuery fctq2();
    client();
    client(QString,QString,int,QString,QString,int,int=0);
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher2(QString);
   QSqlQueryModel *GetNumpassModel();

    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QString,int);
    void recherche();
    QString getnom();
    QString getprenom();
    QString getmail();
    QString getpays();
    int getage();
    int getnumeropasseport();
    int getpoints();
    void set_numpasseport(int numeropasseport){
        this->numeropasseport=numeropasseport;
    }
private:
    QString nom,prenom,mail,pays;
    int numeropasseport,points,age;
};

#endif // CLIENT_H
