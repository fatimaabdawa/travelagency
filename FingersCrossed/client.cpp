#include "client.h"

client::client()
{
numeropasseport=0;
}

client::client(QString nom,QString prenom,int numeropasseport,QString mail,QString pays,int age,int points)
{
    this->nom=nom;
    this->prenom=prenom;
    this->numeropasseport=numeropasseport;
    this->mail=mail;
    this->pays=pays;
    this->age=age;
    this->points=points;
}
QString client:: getnom()
{return nom;}
QString client::getprenom()
{return prenom;}
QString client::getmail()
{return mail;}
int client::getnumeropasseport()
{return numeropasseport;}
int client::getpoints()
{return points;}
QString client::getpays()
{return  pays;}
int client::getage()
{return  age;}

bool client::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(numeropasseport);
    QString res2 = QString::number(points);
    QString res3 = QString::number(age);
    query.prepare("INSERT INTO client (nom, prenom, numeropasseport, mail, pays, age, points) VALUES (:nom, :prenom, :numeropasseport, :mail, :pays, :age, :points)");
    query.bindValue(":nom" , nom);
    query.bindValue(":prenom" , prenom);
    query.bindValue(":numeropasseport" , res);
    query.bindValue(":mail" , mail);
    query.bindValue(":pays" , pays);
    query.bindValue(":age" , res3);
    query.bindValue(":points" , res2);
    return query.exec();

}
QSqlQueryModel * client::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from client");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("N.Passeport"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Mail"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Pays"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("Points"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("Age"));
    return model;
}
bool client::supprimer(int numpass)
{
    QSqlQuery query;
    QString res= QString::number(numpass);
    query.prepare("Delete from client where numeropasseport= :numeropasseport ");
    query.bindValue(":numeropasseport",res);
    return query.exec();
}
bool client::modifier(int numpass,QString nom,QString prenom,QString mail,QString pays,int age)
{
    QSqlQuery query;
    QString res= QString::number(numpass);
    QString res2= QString::number(age);
    query.prepare("UPDATE client set nom=:nom , prenom= :prenom , mail=:mail , pays=:pays , age=:age where numeropasseport=:numeropasseport ");
    query.bindValue(":numeropasseport" , res);
    query.bindValue(":nom" , nom);
    query.bindValue(":prenom" , prenom);
    query.bindValue(":mail" , mail);
    query.bindValue(":pays" , pays);
    query.bindValue(":age" , res2);
    return query.exec();
}
void client::recherche (){
QSqlQuery query;
query.prepare("SELECT nom,prenom,mail,pays,age from client where numeropasseport=:numpass");
query.bindValue(":numpass",numeropasseport);
query.exec();
while(query.next())//parcour
{
nom = query.value(0).toString();
prenom = query.value(1).toString();
mail = query.value(2).toString();
pays = query.value(3).toString();
age = query.value(4).toInt();
}
}

QSqlQueryModel * client::afficher2(QString nom)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QSqlQuery query;
    nom='%'+nom+'%';
    query.prepare("SELECT * from client where nom like :nom or prenom like :nom or pays like :nom or mail like :nom order by numeropasseport");
    query.bindValue(":nom",nom);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("N.Passeport"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Mail"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Pays"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("Points"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("Age"));
    return model;
}

QSqlQueryModel *client::GetNumpassModel()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery *query=new QSqlQuery();
    query->prepare("select numeropasseport from client");
    query->exec();
    model->setQuery(*query);
    return model;
}

QSqlQuery client::fctq()
{
   QSqlQuery q("select AVG(age) from client where pays = 'tunisie'");
   return q;


}
QSqlQuery client::fctq2()
{
   QSqlQuery q("select AVG(age) from client where pays != 'tunisie'");
   return q;


}

bool client::fctqverifmail(QString mail)
{
    QSqlQuery q;
    q.prepare("select mail from client where mail =:mail");
    q.bindValue(":mail",mail);
    q.exec();
    return q.first();
}

bool client::fctqverinp(int np)
{
    QSqlQuery q;
    q.prepare("select numeropasseport from client where numeropasseport =:np");
    q.bindValue(":np",np);
    q.exec();
    return q.first();
}
