    #include "reservervoyage.h"
#include "smtp.h"
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
    query.prepare("INSERT INTO voyage(refvoyage,datedepart,datearrivee,typebillet,classe,datedereservation,codedestination,numeropasseport,nomdestination)Values(oussema_refvoyage.nextval,:datedepart,:datearrivee,:typebillet,:classe,:datedereservation,:destination,:numeropasseport,:nomdestination)");
   // query.bindValue(":refvoyage",refvoyage);
    query.bindValue(":numeropasseport",numeropasseport);
    query.bindValue(":typebillet",typebillet);
    query.bindValue(":classe",classe);
    query.bindValue(":datedepart",datedepart);
    query.bindValue(":datearrivee",datearrivee);
    query.bindValue(":datedereservation",datederesevation);
    query.bindValue(":destination",codedestination);
    query.bindValue(":nomdestination",nomdestination);
    return  query.exec();
}

QSqlQueryModel *reservervoyage::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from voyage");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("refvoyage"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("datedepart"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("datearrivee"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("typebillet"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("classe"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("datedereservation"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Code destination"));
    return model;
}

bool reservervoyage::supprimer(int refvoyage)
{
    QSqlQuery query;
    QString res=QString :: number (refvoyage);
    query.prepare("Delete from voyage where refvoyage = :refvoyage");
    query.bindValue(":refvoyage",res);
    return query.exec();
}
bool reservervoyage::rech(int x)
{
    QSqlQuery query;
    query.prepare("select * from voyage where refvoyage=:x;");
    query.bindValue(":x", x);
    return query.exec();
}


bool reservervoyage::modifier()
{
    QSqlQuery query;
    query.prepare("update voyage set datedepart=:datedepart,datearrivee=:datearrivee,typebillet=:typebillet,classe=:classe,datedereservation=:datedereservation where refvoyage =:refvoyage;");
    query.bindValue(":refvoyage", refvoyage);
    query.bindValue(":datedepart", datedepart);
    query.bindValue(":datearrivee", datearrivee);
    query.bindValue(":typebillet", typebillet);
    query.bindValue(":classe", classe);
    query.bindValue(":datedereservation", datederesevation);

    return query.exec();
}
QSqlQueryModel * reservervoyage::chercher(QString valeur)
{

    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare(QString("select * from voyage WHERE CODEDESTINATION like :valeur"));
valeur='%'+valeur+'%';
    query.bindValue(":valeur",valeur);
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

QSqlQueryModel * reservervoyage::trie_refvoyage()
{ QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM voyage ORDER BY refvoyage;"));
    query.exec();
    model->setQuery(query);
    return model;
}
QSqlQueryModel * reservervoyage::trie_destination()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM voyage ORDER BY codedestination;"));
    query.exec();
    model->setQuery(query);
    return model;
}

void reservervoyage::cher()
{
    QSqlQuery query;
    query.prepare("select * from voyage where refvoyage =: refvoyage");
    query.bindValue(":refvoyage",refvoyage);
    query.exec();

    datedepart = query.value(1).toString();
    datearrivee = query.value(2).toString();
    typebillet = query.value(3).toString();
    classe = query.value(4).toString();
    datederesevation = query.value(5).toString();
    codedestination = query.value(6).toInt();
    numeropasseport = query.value(7).toInt();
}

QSqlQueryModel * get_code_destination()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery * query = new QSqlQuery();
    query->prepare("select code from destination");
    query->exec();
    model->setQuery(*query);
    return model;
}

QSqlQueryModel * reservervoyage::get_ref_ajoutes()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery * query = new QSqlQuery();
    query->prepare("select refvoyage from voyage");
    query->exec();
    model->setQuery(*query);
    return model;
}

QString reservervoyage::getNomDestinationFromtable(int code)
{
    QSqlQuery query;
    QString name="";
    query.prepare("select nom  from destination where code=:code");
    query.bindValue(":code",code);
    query.exec();
    while(query.next())
    {
        name=query.value(0).toString();
    }
    return name;
}

QString reservervoyage::retourMailClient()
{
    QString mail;
    QSqlQuery query;
    query.prepare("select mail from client where numeropasseport=:numeropasseport");
    query.bindValue(":numeropasseport",numeropasseport);
    query.exec();
    while(query.next())
    {
        mail=query.value(0).toString();
    }
    return mail;
}

void reservervoyage::mailing(QString receiver)
{
    QString contenu="Cher monsieur/madame votre reservation de voyage vers "+nomdestination+" est confirmée";
    QString objet = "Confirmation de votre reservation de voyage.";

    Smtp* smtp = new Smtp("nooblolsaibot1@gmail.com", "haboubax", "smtp.gmail.com", 465);
    if(smtp->sendMail("nooblolsaibot1@gmail.com",receiver,objet,contenu))
        QMessageBox::information(nullptr,QObject::tr("mail"),"Votre mail a été envoyé.");
}
