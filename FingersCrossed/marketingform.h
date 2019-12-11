#ifndef MARKETINGFORM_H
#define MARKETINGFORM_H
#include<prromtion.h>
#include<evenemant.h>
#include <QMainWindow>
#include"login.h"
#include"smtp.h"

namespace Ui {
class marketingform;
}

class marketingform : public QMainWindow
{
    Q_OBJECT

public:
    explicit marketingform(QWidget *parent = nullptr);
    ~marketingform();

private slots:

    void sendMail();

    void mailSent(QString);

    void on_pushButton_6_clicked();

    void refresh();

    void on_pushButton_5_clicked();

    void on_comboBox_supprimer_activated(const QString &arg1);

    void on_consulter_stat_clicked();

    void on_pushbouton_print_clicked();

    void on_comboBox_2_activated(const QString &arg1);

    void on_supprimer_clicked();

    void on_dateDebut_userDateChanged(const QDate &date);

    void on_datefin_userDateChanged(const QDate &date);

    void on_dated_userDateChanged(const QDate &date);

    void on_datef_userDateChanged(const QDate &date);

    void on_modifier_clicked_clicked();

    void on_facebook_clicked();

    void on_TRI_clicked();

    void on_lineEdit_chercher_textChanged(const QString &arg1);

    void on_youtube_clicked();

    void on_pushButton_7_clicked();

    void on_ajouterpro_clicked();

    void on_modifierpro_clicked();

    void on_supprimerpro_2_clicked();

    void on_ajouterevent_clicked();

    void on_comboBox_5_activated(const QString &arg1);

private:
    Ui::marketingform *ui;
    prromtion tmpprromotion;
    evenemant tmpevenemant;
    QString password="esprit19",user="fatima";

};

#endif // MARKETINGFORM_H
