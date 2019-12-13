#include "destination.h"
#include <QTime>
destination::destination()
{
    this->nom="";
    this->promo=0;
    this->description="";
    this->code=0;
}

destination::destination(QString description,QString nom,int code, int promo)
{
    this->description=description;
    this->nom=nom;
    this->promo=promo;
    this->code=code;
}


bool destination::ajouter()
{
    QSqlQuery query(QSqlDatabase::database());
    QString res=QString::number(code);
    query.prepare("INSERT INTO destination(nom, code , description , promo) VALUES ( :nom, id.nextval , :description, :promo)");
    query.bindValue(":nom", nom);
    //query.bindValue(":code",code);
    query.bindValue(":description", description);
    query.bindValue(":promo", promo);
    return query.exec();
}


QSqlQueryModel *destination::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from destination");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Description"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("Code"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Promo"));
    return model ;
}

QSqlQueryModel * destination::ModelCodeDestinations()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery();
    query->prepare("select code from destination");
    query->exec();
    model->setQuery(*query);
    return model;
}

bool destination::supprimer(int code)
{
    QSqlQuery query;
    QString res=QString::number(code);
    query.prepare("Delete from destination where code = :code ");
    query.bindValue(":code",res);
    return query.exec();
}

bool destination::modifier( QString description,QString nom, int code, int promo)
{
    QSqlQuery query;
    QString yep=QString::number(code);
    query.prepare("update destination set nom=:nom,description=:description,promo=:promo where code='"+yep+"'");
    query.bindValue(":nom",nom);
    query.bindValue(":description",description);
    query.bindValue(":promo",promo);
    return  query.exec();
}

QSqlQueryModel * destination:: recherche(QString valeur,int etat)
{
    QSqlQueryModel * model=new QSqlQueryModel();

    QSqlQuery query;
    if(etat==1)
    { query.prepare("SELECT * FROM DESTINATION WHERE NOM LIKE :valeur OR DESCRIPTION LIKE :valeur order by NOM");}
    else
    { query.prepare("SELECT * FROM DESTINATION WHERE NOM LIKE :valeur OR DESCRIPTION LIKE :valeur order by NOM desc");}
    valeur="%"+valeur+"%";
    query.bindValue(":valeur",valeur);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Code"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Promo"));
    return model;
}

void destination:: chercher(int rd)
{    QSqlQuery query1;
     QString r = QString::number(rd);
     query1.prepare("SELECT * FROM destination WHERE code='"+r+"'");
     query1.bindValue(":code",r);
     query1.exec();
     while(query1.next())
        {
            nom = query1.value(0).toString();
            description = query1.value(1).toString();
            promo = query1.value(3).toString().toInt();
        }
}


void destination::pkeor(QString q, int iq)
{
    //or description =:q or code = :q or promo = :q
    QSqlQuery query;
    QString iqq = QString::number(iq);
    query.prepare("select * from destination where nom = '"+q+"' or description = '"+q+"' or promo = '"+iqq+"' or code = '"+iqq+"' ");
    query.bindValue(":iqq",iq);
    query.bindValue(":q",q);
    query.exec();
        while(query.next())
    {
            nom = query.value(0).toString();
            description = query.value(1).toString();
            code = query.value(2).toInt();
            promo = query.value(3).toString().toInt();
    }

}

QString destination::retourneFirstPromoDestination()
{
    QString namem;
    QSqlQuery query;
    query.prepare("select nom from destination where promo = '1' ");
    query.exec();
    while(query.next())
    {
        namem = query.value(0).toString();
    }
       //std::string plo = namem.toStdString();

    return namem;
}
