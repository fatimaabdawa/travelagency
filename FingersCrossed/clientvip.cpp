#include "clientvip.h"

clientvip::clientvip()
{
numeropasseport=0;
}
clientvip::clientvip(QString nom,QString prenom,int numeropasseport,QString mail,QString profession,QString pays,int age,int points)
{
    this->nom=nom;
    this->prenom=prenom;
    this->numeropasseport=numeropasseport;
    this->mail=mail;
    this->profession=profession;
    this->pays=pays;
    this->age=age;
    this->points=points;
}
QString clientvip:: getnom()
{return nom;}
QString clientvip::getprenom()
{return prenom;}
QString clientvip::getmail()
{return mail;}
int clientvip::getnumeropasseport()
{return numeropasseport;}
QString clientvip::getprofession()
{return profession;}
int clientvip::getpoints()
{return points;}
QString clientvip::getpays()
{return  pays;}
int clientvip::getage()
{return  age;}

bool clientvip::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(numeropasseport);
    QString res2 = QString::number(points);
    QString res3 = QString::number(age);
    query.prepare("INSERT INTO clientvip (nom, prenom, numeropasseport, mail, profession, pays, age, points) VALUES (:nom, :prenom, :numeropasseport, :mail, :profession, :pays, :age, :points)");
    query.bindValue(":nom" , nom);
    query.bindValue(":prenom" , prenom);
    query.bindValue(":numeropasseport" , res);
    query.bindValue(":mail" , mail);
    query.bindValue(":profession" , profession);
    query.bindValue(":pays" , pays);
    query.bindValue(":age" , res3);
    query.bindValue(":points" , res2);
    return query.exec();

}
QSqlQueryModel * clientvip::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from clientvip");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("N.Passeport"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Mail"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Profession"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("Points"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("Pays"));
    model->setHeaderData(7,Qt::Horizontal, QObject::tr("Age"));
    return model;
}
bool clientvip::supprimer(int numpass)
{
    QSqlQuery query;
    QString res= QString::number(numpass);
    query.prepare("Delete from clientvip where numeropasseport= :numeropasseport ");
    query.bindValue(":numeropasseport",res);
    return query.exec();
}
bool clientvip::modifier(int numpass,QString nom,QString prenom,QString mail,QString profession,QString pays,int age)
{
    QSqlQuery query;
    QString res= QString::number(numpass);
    QString res2= QString::number(age);
    query.prepare("UPDATE clientvip set nom=:nom , prenom= :prenom , mail=:mail , profession=:profession , pays=:pays , age=:age where numeropasseport=:numeropasseport ");
    query.bindValue(":numeropasseport" , res);
    query.bindValue(":nom" , nom);
    query.bindValue(":prenom" , prenom);
    query.bindValue(":mail" , mail);
    query.bindValue(":profession" , profession);
    query.bindValue(":pays" , pays);
    query.bindValue(":age" , res2);
    return query.exec();
}
void clientvip::recherche (){
QSqlQuery query;
query.prepare("SELECT nom,prenom,mail,profession,pays,age from clientvip where numeropasseport=:numpass");
query.bindValue(":numpass",numeropasseport);
query.exec();
while(query.next())//parcour
{
nom = query.value(0).toString();
prenom = query.value(1).toString();
mail = query.value(2).toString();
profession = query.value(3).toString();
pays = query.value(4).toString();
age = query.value(5).toInt();
}
}

QSqlQueryModel * clientvip::afficher2(QString nom)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QSqlQuery query;
    nom='%'+nom+'%';
    query.prepare("SELECT * from clientvip where nom like :nom or prenom like :nom or pays like :nom or profession like :nom or mail like :nom order by numeropasseport");
    query.bindValue(":nom",nom);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("N.Passeport"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Mail"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Profession"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("Points"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("Pays"));
    model->setHeaderData(7,Qt::Horizontal, QObject::tr("Age"));
    return model;
}

QSqlQueryModel * clientvip::GetNumpassModel()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery *query=new QSqlQuery();
    query->prepare("select numeropasseport from clientvip");
    query->exec();
    model->setQuery(*query);
    return model;
}

bool clientvip::fctqverifmail(QString mail)
{
    QSqlQuery q;
    q.prepare("select mail from clientvip where mail =:mail");
    q.bindValue(":mail",mail);
    q.exec();
    return q.first();
}

bool clientvip::fctqverinp(int np)
{
    QSqlQuery q;
    q.prepare("select numeropasseport from clientvip where numeropasseport =:np");
    q.bindValue(":np",np);
    q.exec();
    return q.first();
}
