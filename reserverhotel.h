#ifndef RESERVERHOTEL_H
#define RESERVERHOTEL_H



#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QDate>


class reserverhotel
{
public:
    reserverhotel();


    ~reserverhotel();
    reserverhotel(int, int, QString, QDate, QDate, QDate, int);

    QString get_nom(){return nom;}
    QDate get_datedeaprt(){return datedepart;}
    QDate get_datearrivee(){return datearrivee;}
    QDate get_datereservation(){return datereservation;}
    int get_idhotel(){return idhotel;}
    int get_duree(){return duree;}
    void set_nom(QString nom){this->nom=nom;}
    void set_datedeaprt(QDate datedepart){this->datedepart=datedepart;}
    void set_datearrivee(QDate datearrivee){this->datearrivee=datearrivee;}
    void set_datederesevation(QDate datereservation){this->datereservation=datereservation;}
    void set_duree(int duree){this->duree=duree;}
    void set_idhotel(int idhotel){this->idhotel=idhotel;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int, int);
    bool modifier(int,QString,QDate,QDate,QDate,int);
    QSqlQueryModel * CodeModelHotel();
    QSqlQueryModel * NumeroPasseportModelHotel();
    QSqlQueryModel * IdHotelReserverHotel();
    QSqlQueryModel * NumeroPassePortReserverHotel();


private:

    int duree,idhotel,numeropasseport;
    QString nom;
    QDate datedepart,datearrivee,datereservation;


};

#endif // RESERVERHOTEL_H
