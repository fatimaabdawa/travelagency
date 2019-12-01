#ifndef RESERVERHOTEL_H
#define RESERVERHOTEL_H



#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QString>


class reserverhotel
{
public:
    reserverhotel();


    ~reserverhotel();
    reserverhotel(int, int, QString, QString, QString, QString, int);

    QString get_nom(){return nom;}
    QString get_datedeaprt(){return datedepart;}
    QString get_datearrivee(){return datearrivee;}
    QString get_datereservation(){return datereservation;}
    QString get_nomclient(){return nomclient;}
    int get_idhotel(){return idhotel;}
    int get_duree(){return duree;}
    int get_numeropasseport(){return numeropasseport;}
    void set_nomclient(QString nomclient){this->nomclient=nomclient;}
    void set_nom(QString nom){this->nom=nom;}
    void set_numeropasseport(int numeropasseport){this->numeropasseport=numeropasseport;}
    void set_datedeaprt(QString datedepart){this->datedepart=datedepart;}
    void set_datearrivee(QString datearrivee){this->datearrivee=datearrivee;}
    void set_datederesevation(QString datereservation){this->datereservation=datereservation;}
    void set_duree(int duree){this->duree=duree;}
    void set_idhotel(int idhotel){this->idhotel=idhotel;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer();
    void chercher();
    bool modifier();
    QSqlQueryModel * CodeModelHotel();
    QSqlQueryModel * NumeroPasseportModelHotel();
    QSqlQueryModel * IdHotelReserverHotel();
    QSqlQueryModel * NumeroPassePortReserverHotel();
    QSqlQueryModel * CodeDestinationModel();
    QString RetourNomHotel(QString);
    QString retourNomClient(int);

private:

    int duree,idhotel,numeropasseport;
    QString nom,nomclient;
    QString datedepart,datearrivee,datereservation;


};

#endif // RESERVERHOTEL_H
