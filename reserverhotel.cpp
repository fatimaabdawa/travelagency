#include "reserverhotel.h"

reserverhotel::reserverhotel(int idhotel, int duree, QString nom, QString datedepart, QString datearrivee, QString datereservation, int numeropasseport)
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
    query->prepare("INSERT INTO RESERVERHOTEL(nomhotel,idhotel,datedepart,dateretour,datereservation,duree,numeropasseport,nomclient)Values(:nom,:idhotel,:datedepart,:dateretour,:datereservation,:duree,:numeropasseport,:nomclient)");
    query->bindValue(":nom",nom);
    query->bindValue(":idhotel",res);
    query->bindValue(":datedepart",datedepart);
    query->bindValue(":dateretour",datearrivee);
    query->bindValue(":datereservation",datereservation);
    query->bindValue(":duree",duree);
    query->bindValue(":numeropasseport",numeropasseport);
    query->bindValue(":nomclient",nomclient);
    return  query->exec();
}
QSqlQueryModel *reserverhotel::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from RESERVERHOTEL");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Nom hotel"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("idhotel"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("datedepart"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("dateretour"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("datereservation"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("duree"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Numero Passeport"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Nom Client"));

    return model;
}
bool reserverhotel::supprimer()
{
    QSqlQuery query;
    QString res=QString :: number (numeropasseport);
    query.prepare("Delete from reserverhotel where numeropasseport= :idhotel ");
    query.bindValue(":idhotel",res);
    return query.exec();
}

//MODels
QSqlQueryModel * reserverhotel::CodeModelHotel()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery();
    query->prepare("select idhotel from hotel");
    query->exec();
    model->setQuery(*query);
    return model;
}
QSqlQueryModel * reserverhotel::NumeroPasseportModelHotel()
{
    QSqlQuery *query=new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    query->prepare("select numeropasseport from client  where numeropasseport not in (select numeropasseport from reserverhotel)");
    query->exec();
    model->setQuery(*query);
    return model;
}

bool reserverhotel::modifier()
{
    QSqlQuery query;
    QString res = QString::number(numeropasseport);
    query.prepare("update reserverhotel set  duree=:duree,datedepart=:datedepart, dateretour=:dateretour, datereservation =:datereservation where numeropasseport ='"+res+"'");
    query.bindValue(":datereservation",datereservation);
    query.bindValue(":dateretour",datearrivee);
    query.bindValue(":datedepart",datedepart);
    query.bindValue(":numeropasseport",res);
    query.bindValue(":duree",duree);
    return query.exec();
}

QSqlQueryModel * reserverhotel::IdHotelReserverHotel()
{
    QSqlQuery *query=new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    query->prepare("select idhotel from reserverhotel");
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

QString reserverhotel::RetourNomHotel( QString id)
{
    QSqlQuery query;
    QString name="";
    query.prepare("select nom from hotel where idhotel=:idhotel");
    query.bindValue(":idhotel",id);
    query.exec();
    while(query.next()){
    name=query.value(0).toString();
    }
    return name;
}

void reserverhotel:: chercher()
{    QSqlQuery query1;
     query1.prepare("SELECT * from reserverhotel where idhotel :=idhotel");
      query1.bindValue(":idhotel", idhotel);
       query1.exec();
        while(query1.next())
        {
            nom = query1.value(0).toString();
            datedepart = query1.value(2).toString();
            datearrivee = query1.value(3).toString();
            datereservation = query1.value(4).toString();
            duree = query1.value(5).toInt();
            numeropasseport = query1.value(6).toInt();
        }
}

QSqlQueryModel * reserverhotel::CodeDestinationModel()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery * query = new QSqlQuery();
    query->prepare("select code from destination");
    query->exec();
    model->setQuery(*query);
    return model;
}


QString reserverhotel::retourNomClient(int numeropass)
{
    QSqlQuery query;
    QString name="";
    query.prepare("select nom from client where numeropasseport=:numeropasseport");
    query.bindValue(":numeropasseport",numeropass);
    query.exec();
    while(query.next()){
    name=query.value(0).toString();
    }
    return name;
}
