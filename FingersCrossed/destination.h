#ifndef DESTINATION_H
#define DESTINATION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDialog>
#include <QString>
#include <QSqlQueryModel>

class destination
{
public:
    //CONSTRUCTORS
    destination();
    destination(QString,QString,int,int);
    //GETTERS
    QString getNom(){return nom;}
    int getCode(){return  code;}
    QString getDescription(){return description;}
    int getPromo(){return promo;}
    //SETTERS
    void setNom(QString nom){this->nom=nom;}
    void setCode(int code){this->code=code;}
    void setDescription(QString description){this->description=description;}
    void setPromo(int promo){this->promo=promo;}
    //CRUD
    bool ajouter();
    bool supprimer(int);
    bool modifier(QString ,QString ,int ,int);
   QSqlQueryModel * afficher();
   //GET MODEL FOR CODES - EXTRA
   QSqlQueryModel * ModelCodeDestinations();
  //SEARCH AND DESTROY
   QSqlQueryModel * recherche(QString,int);
   void chercher();
private :
    QString nom,description;
    int code,promo;

};

#endif // DESTINATION_H
