#ifndef INTEGRATEDONE_H
#define INTEGRATEDONE_H


#include <QMainWindow>
#include "destination.h"
#include "hotel.h"
#include <QMainWindow>
#include "notification.h"
#include <QMediaPlayer>
#include <QtMultimedia>
#include "reserverhotel.h"
#include "reservervoyage.h"
#include<prromtion.h>
#include<evenemant.h>
#include "statistique.h"
#include "statclient.h"
#include "client.h"
#include "clientvip.h"
namespace Ui {
class integratedone;
}

class integratedone : public QMainWindow
{
    Q_OBJECT

public:
    explicit integratedone(QWidget *parent = nullptr);
    ~integratedone();
    //MOHAMED
    void sendMail();
    void mailSent(QString status);
    void browse();
    //OUSSEMA


private slots:

   // WHOLE IN ONE.

    void on_intdestinations_clicked();

    void on_intreservations_clicked();

    void on_intemployes_clicked();

    void on_intclients_clicked();

    void on_intevents_clicked();

    //MOHAMED

   // void showTime(); UNUSED.

    void on_pushButton_ajouterclient_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_comboBoxmodifclient_activated(const QString &arg1);

    void on_pushButton_modifclient_clicked();

    void on_pushButton_suppclient_clicked();

    void on_rechercheclient_textChanged(const QString &arg1);

    void on_pushButton_ajouterclientvip_clicked();

    void on_tabWidget_2_currentChanged(int index);

    void on_comboBoxmodifclientvip_activated(const QString &arg1);

    void on_pushButton_modifclientvip_clicked();

    void on_pushButton_suppclientvip_clicked();

    void on_rechercheclientvip_2_textChanged(const QString &arg1);

    void on_sendBtn_clicked();

    void on_exitBtn_clicked();

    void on_statbutton_clicked();

    void on_rechercheclient_3_textChanged(const QString &arg1);

    void on_rechercheclient_2_textChanged(const QString &arg1);

    //OUSSEMA

    void on_numeropasseport_rv_ajout_currentTextChanged(const QString &arg1);

    void on_datereservation_rv_ajout_userDateChanged(const QDate &date);

    void on_datedepart_rv_ajout_userDateChanged(const QDate &date);

    void on_datearrivee_rv_ajout_userDateChanged(const QDate &date);


    void on_reservervoyage_ajout_clicked();

    void on_typebillet_rv_ajout_currentTextChanged(const QString &arg1);

    void on_classe_rv_ajout_currentTextChanged(const QString &arg1);

    void on_datereservation_rv_modif_userDateChanged(const QDate &date);

    void on_datedepart_rv_modif_userDateChanged(const QDate &date);

    void on_datearrivee_rv_modif_userDateChanged(const QDate &date);

    void on_rv_modifier_clicked();

    void on_supprimer_rv_clicked();

    void on_Ajout_rhotel_clicked();

    void on_datereservation_ajout_userDateChanged(const QDate &date);

    void on_datearrivee_ajout_userDateChanged(const QDate &date);

    void on_datedepart_ajout_userDateChanged(const QDate &date);

    void on_horizontalSlider_sliderMoved(int position);

    void on_music_button_clicked();

    void on_mute_button_clicked();

    void on_chercher_trier_rv_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_supprimer_rhotel_clicked();

    void on_modifier_rhotel_clicked();

    void on_rh_dater_modifier_userDateChanged(const QDate &date);

    void on_rh_datea_modifier_userDateChanged(const QDate &date);

    void on_rh_dated_modifier_userDateChanged(const QDate &date);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_idhotel_combobox_currentIndexChanged(const QString &arg1);

    void on_numeropasseport_combobox_currentIndexChanged(const QString &arg1);

    void on_codedestination_rv_ajout_currentIndexChanged(const QString &arg1);

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    //YOUR HUMBLE SERVANT

    void on_ajouter_destination_clicked();

    void on_SupprimerDestination_clicked();

    void on_ajouter_hotel_clicked();

    void on_supprimer_hotel_clicked();

    void on_comboBox_currentIndexChanged();

    void on_Modifier_clicked();

    void on_comboBox_2_currentIndexChanged();

    void on_ModifierHotel_clicked();

    void on_trierChercher_2_textChanged(const QString &arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_trierChercher_textChanged(const QString &arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_Code_destination_ajouthotel_currentIndexChanged();

    //FATIMA

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
    Ui::integratedone *ui;

    //MOHAMED

    client tmpclient;
    clientvip tmpclientvip;

    //OUSSEMA

    reservervoyage tmpreservoyage;
    reserverhotel tmpajouth;
    reserverhotel tmpreshotel;
    reservervoyage tmpmodifvoyage;

    //YOUR HUMBLE SERVANT

    destination tmpdestination;
    hotel tmphotel;
    QString valeur="";
    int etat=0;
    notification ok;
    QMediaPlayer *player = new QMediaPlayer();

    //FATIMA

    prromtion tmpprromotion;
    evenemant tmpevenemant;
};

#endif // INTEGRATEDONE_H
