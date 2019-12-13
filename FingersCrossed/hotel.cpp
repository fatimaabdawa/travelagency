#include "hotel.h"

hotel::hotel()
{

}

hotel::hotel(int idhotel,QString nom,QString adresse,int etoiles,int coutparnuit)
{
    this->idhotel=idhotel;
    this->nom=nom;
    this->etoiles=etoiles;
    this->coutparnuit=coutparnuit;
    this->adresse=adresse;
}

QSqlQueryModel * hotel::afficherH()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from hotel");
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("idhotel"));
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("etoiles"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("coutparnuit"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CodeDestination"));
    return model ;
}
QSqlQueryModel * hotel::ModelidhotelHotel()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery();
    query->prepare("select idhotel from hotel");
    query->exec();
    model->setQuery(*query);
    return model;
}

bool hotel::ajouterH()
{
    QSqlQuery query;
    QString res=QString::number(idhotel);
    query.prepare("INSERT INTO hotel(nom,adresse, etoiles,idhotel ,coutparnuit, codedestination ) VALUES (:nom , :adresse, :etoiles ,HABIB.INCREMENT_IDHOTEL.NEXTVAL,:coutparnuit,:codedestination)");
    query.bindValue(":nom",nom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":etoiles", etoiles);
    query.bindValue(":coutparnuit", coutparnuit);
    query.bindValue(":codedestination", codedestination);

    return query.exec();
}

bool hotel::supprimer()
{
    QSqlQuery query;
    QString res=QString::number(idhotel);
    query.prepare("Delete from hotel where idhotel = :idhotel ");
    query.bindValue(":idhotel",res);
    return query.exec();
}

bool hotel::modifier()
{
    QSqlQuery query;
    QString yep=QString::number(idhotel);
    query.prepare("update hotel set adresse=:adresse,nom=:nom,etoiles=:etoiles,coutparnuit=:coutparnuit where idhotel='"+yep+"'");
    query.bindValue(":nom",nom);
    query.bindValue(":idhotel",idhotel);
    query.bindValue(":adresse",adresse);
    query.bindValue(":etoiles",etoiles);
    query.bindValue(":coutparnuit",coutparnuit);
    return  query.exec();
}

QSqlQueryModel * hotel:: recherche(QString valeur,int etat)
{
    QSqlQueryModel * model=new QSqlQueryModel();

    QSqlQuery query;
    if(etat==1)
    { query.prepare("SELECT * FROM hotel WHERE NOM LIKE :valeur OR adresse like :valeur order by NOM");}
    else
    { query.prepare("SELECT * FROM hotel WHERE NOM LIKE :valeur OR adresse like :valeur  order by NOM desc");}
    valeur="%"+valeur+"%";
    query.bindValue(":valeur",valeur);
    query.exec();
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("etoiles"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id hotel"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("coutparnuit"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CodeDestination"));
    return model;

}

void hotel:: chercher()
{    QSqlQuery query1;
     query1.prepare("SELECT * FROM hotel WHERE idhotel=:idhotel");
      query1.bindValue(":idhotel",idhotel);
       query1.exec();
        while(query1.next())
        {
            nom = query1.value(0).toString();
            adresse = query1.value(1).toString();
            etoiles = query1.value(2).toInt();
            coutparnuit = query1.value(4).toInt();
            codedestination = query1.value(5).toInt();
        }
}

void hotel::pkeor(QString q, int iq)
{

    QString iqq = QString::number(iq);
    QSqlQuery query;
    query.prepare("select * from hotel where nom= '"+q+"' or adresse = '"+q+"' or etoiles = '"+iqq+"' or idhotel ='"+iqq+"' or coutparnuit = '"+iqq+"'");
    query.bindValue(":iqq",iq);
    query.bindValue(":q",q);
    query.exec();
        while(query.next())
    {
            nom = query.value(0).toString();
            adresse = query.value(1).toString();
            etoiles = query.value(2).toInt();
            idhotel = query.value(3).toInt();
            coutparnuit = query.value(4).toString().toInt();
    }

}
