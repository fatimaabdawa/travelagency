#include "reserverhotel.h"

reserverhotel::reserverhotel(int idhotel, int duree, QString nom, QDate datedepart, QDate datearrivee, QDate datereservation, int numeropasseport)
{
    this->idhotel=idhotel;
    this->duree=duree;
    this->nom=nom;
    this->datedepart=datedepart;
    this->datearrivee=datearrivee;
    this->datereservation=datereservation;
    this->numeropasseport=numeropasseport;

}

reserverhotel::reserverhotel() //CONSTRUCTOR
{

}
reserverhotel::~reserverhotel() // DESTRUCTOR
{

}

bool reserverhotel:: ajouter()
{
    QSqlQuery *query=new QSqlQuery();
    QString res=QString::number(idhotel);
    query->prepare("INSERT INTO RESERVERHOTEL(nom,idhotel,datedepart,dateretour,datereservation,duree,numeropasseport)Values(:nom,:idhotel,:datedepart,:dateretour,:datereservation,:duree,:numeropasseport)");
    query->bindValue(":nom",nom);
    query->bindValue(":idhotel",res);
    query->bindValue(":datedepart",datedepart);
    query->bindValue(":dateretour",datearrivee);
    query->bindValue(":datereservation",datereservation);
    query->bindValue(":duree",duree);
    query->bindValue(":numeropasseport",numeropasseport);
    return  query->exec();
}
QSqlQueryModel *reserverhotel::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from RESERVERHOTEL");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("idhotel"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("datedepart"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("dateretour"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("datereservation"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("duree"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Numero Passeport"));
    return model;
}
bool reserverhotel::supprimer(int idhotel, int numeropasseport)
{
    QSqlQuery query;
    QString res=QString :: number (idhotel);
    QString res1=QString :: number (numeropasseport);
    query.prepare("Delete from reserverhotel where idhotel= :idhotel and numeropasseport=:numeropasseport");
    query.bindValue(":idhotel",res);
    query.bindValue(":numeropasseport",res1);
    return query.exec();
}

 //MODels
QSqlQueryModel * reserverhotel::CodeModelHotel()
{
    QSqlQueryModel * model = new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery();
        query->prepare("select nom from hotel");
        query->exec();
        model->setQuery(*query);
        return model;
}
QSqlQueryModel * reserverhotel::NumeroPasseportModelHotel()
{
    QSqlQuery *query=new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    query->prepare("select numeropasseport from client");
    query->exec();
    model->setQuery(*query);
    return model;
}

bool reserverhotel::modifier(int idhotel,QString nom,QDate datedepart,QDate datereservation,QDate datearrivee,int duree)
{

}

QSqlQueryModel * reserverhotel::IdHotelReserverHotel()
{
    QSqlQuery *query=new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    query->prepare("select nom from reserverhotel");
    query->exec();
    model->setQuery(*query);
    return model;
}

QSqlQueryModel * reserverhotel::NumeroPassePortReserverHotel()
{
    QSqlQuery *query=new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    query->prepare("select numeropasseport from reserverhotel");
    query->exec();
    model->setQuery(*query);
    return model;
}
