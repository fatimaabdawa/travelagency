#ifndef RESERVERreservervoyage_H
#define RESERVERreservervoyage_H
#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QDate>


class reservervoyage
{
public:
    reservervoyage();
    reservervoyage(int, QString, QString,QString,QString,QString,int,int);
    QString get_typebillet(){return typebillet;}
    QString get_classe(){return classe;}
    QString get_datedeaprt(){return datedepart;}
    QString get_datearrivee(){return datearrivee;}
    QString get_datereservation(){return datederesevation;}
    int get_refvoyage(){return refvoyage;}
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    void set_typebillet(QString typebillet){this->typebillet=typebillet;}
    void set_classe(QString classe ){this->classe=classe;}
    void set_refvoyage(int refvoyage){this->refvoyage=refvoyage;}
    void set_datedeaprt(QString datedepart){this->datedepart=datedepart;}
    void set_datearrivee(QString datearrivee){this->datearrivee=datearrivee;}
    void set_datederesevation(QString datederesevation){this->datederesevation=datederesevation;}
    void set_codedestination(int codedestination){this->codedestination=codedestination;}
    void set_numeropasseport(int numeropasseport){this->numeropasseport=numeropasseport;}
    bool rech(int x);
    bool modifier(int a,QString b,QString c,QString d,QString e,QString f,QString g);
    QSqlQueryModel *chercher(int ref);
    QSqlQueryModel *chercher(QString destination);
    QSqlQueryModel * trie_refvoyage();
    QSqlQueryModel * trie_destination();
private:
    int refvoyage;
    QString typebillet,classe;
    QString datedepart,datearrivee,datederesevation;
    int codedestination,numeropasseport;
};
#endif // RESERVERreservervoyage_H
