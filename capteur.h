#ifndef CAPTEUR_H
#define CAPTEUR_H
#include"arduino.h"

#include <QDialog>

namespace Ui {
class capteur;
}

class capteur : public QDialog
{
    Q_OBJECT

public:
    explicit capteur(QWidget *parent = nullptr);
    ~capteur();

private slots:
    void update_label() ;
    void on_pushButton_clicked();

    void on_OFF_pushbutton_clicked();

private:
    Ui::capteur *ui;
    QByteArray data;
    arduino a;
};

#endif // CAPTEUR_H

