#include "reservervoyage.h"

reservervoyage::reservervoyage(){}

reservervoyage::reservervoyage(int refvoyage,QString typebillet,QString classe,QString datedepart,QString datearrivee,QString datereservation,int codedestination,int numeropasseport)
{
    this->refvoyage=refvoyage;
    this->typebillet=typebillet;
    this->classe=classe;
    this->datedepart=datedepart;
    this->datearrivee=datearrivee;
    this->codedestination=codedestination;
    this->datederesevation=datereservation;
    this->numeropasseport=numeropasseport;
}
bool reservervoyage:: ajouter()
{
    QSqlQuery query;
    QString res=QString::number(refvoyage);
    query.prepare("INSERT INTO reservervoyage(refvoyage,datedepart,datearrivee,typebillet,classe,datedereservation,destination)Values(:refvoyage,:datedepart,:datearrivee,:typebillet,:classe,:datedereservation,:destination)");
    query.bindValue(":refvoyage",res);
    query.bindValue(":typebillet",typebillet);
    query.bindValue(":classe",classe);
    query.bindValue(":datedepart",datedepart);
    query.bindValue(":datearrivee",datearrivee);
    query.bindValue(":datedereservation",datederesevation);
    query.bindValue(":destination",codedestination);
    return  query.exec();
}

QSqlQueryModel *reservervoyage::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from reservervoyage");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("refvoyage"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("datedepart"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("datearrivee"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("typebillet"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("classe"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("datedereservation"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("destination"));
    return model;
}

bool reservervoyage::supprimer(int refvoyage)
{
    QSqlQuery query;
    QString res=QString :: number (refvoyage);
    query.prepare("Delete from reservervoyage where REFvoyage = :refvoyage");
    query.bindValue(":refvoyage",res);
    /*if(res!=refvoyage)
    { QMessageBox::information(nullptr,QObject::tr("suppression"),"reference introuvable!");
    }*/
    return query.exec();
}
bool reservervoyage::rech(int x)
{
    QSqlQuery query;
    query.prepare("select * from voyage where refvoyage=:x;");
    query.bindValue(":x", x);
    return query.exec();
}


bool reservervoyage::modifier(int a,QString b,QString c,QString d,QString e,QString f,QString g)
{
    QSqlQuery query;
    query.prepare("update reservervoyage set datedepart=:datedepart,datearrivee=:datearrivee,typebillet=:typebillet,classe=:classe,datedereservation=:datedereservation,destination=:destination where refvoyage =:refvoyage;");
    query.bindValue(":refvoyage", a);
    query.bindValue(":datedepart", b);
    query.bindValue(":datearrivee", c);
    query.bindValue(":typebillet", d);
    query.bindValue(":classe", e);
    query.bindValue(":datedereservation", f);
    query.bindValue(":destination", g);

    return query.exec();
}
QSqlQueryModel * reservervoyage::chercher(int ref)
{

    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare(QString("select * from reservervoyage WHERE refvoyage=:ref"));

    query.bindValue(":ref",ref);

    query.exec();
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("refvoyage"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("datedepart"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("datearrivee"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("typebillet"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("classe"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("datedereservation"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("destination"));


    return model;
}
QSqlQueryModel * reservervoyage::chercher(QString destination)
{

    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare(QString("select * from reservervoyage WHERE destination=:destination"));

    query.bindValue(":destination",destination);

    query.exec();
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("refvoyage"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("datedepart"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("datearrivee"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("typebillet"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("classe"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("datedereservation"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("destiantion"));


    return model;
}
QSqlQueryModel * reservervoyage::trie_refvoyage()
{ QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM reservervoyage ORDER BY refvoyage;"));
    query.exec();
    model->setQuery(query);
    return model;
}
QSqlQueryModel * reservervoyage::trie_destination()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM reservervoyage ORDER BY destination;"));
    query.exec();
    model->setQuery(query);
    return model;
}
