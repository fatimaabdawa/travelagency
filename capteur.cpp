#include "capteur.h"
#include "ui_capteur.h"

capteur::capteur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::capteur)
{
    ui->setupUi(this);
    int ret=a.connect_arduino();//lancer la cnx arduino
    switch(ret)
    {
    case(0):qDebug()<<"arduino is available and connected to:"<<a.getarduino_port_name();
        break;
    case(1):qDebug()<<"arduino is available but not connected to:"<<a.getarduino_port_name();
        break;
    case(-1):qDebug()<<"arduino is not available";
    }
    QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

}

void capteur::update_label()
{
    data=a.read_from_arduino();
    if (data=="1")
        ui->lineEdit_3->setText("ON");
    else if(data=="0")
        ui->lineEdit_3->setText("OFF");
}

capteur::~capteur()
{
    delete ui;
}

void capteur::on_pushButton_clicked()
{
   a.write_to_arduino("1");
   if(a.getserial()->waitForReadyRead(10))
      data=a.read_from_arduino();
      qDebug() << "data : " << data;
}

/*void capteur::on_OFF_pushbutton_clicked()
{
 a.write_to_arduino("0");
 if(a.getserial()->waitForReadyRead(10))
    data=a.read_from_arduino();
    qDebug() << "data : " << data;
}*/
