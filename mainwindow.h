#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "reserverhotel.h"
#include "reservervoyage.h"
#include <QMainWindow>
#include <QMediaPlayer>
#include "notification.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

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

    void on_stat_bushonputt_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_music_button_clicked();

    void on_mute_button_clicked();

    void on_chercher_trier_rv_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void sendMail();
    void mailSent(QString status);

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


private:
    Ui::MainWindow *ui;
    reservervoyage tmpreservoyage;
    reserverhotel tmpajouth;
    reserverhotel tmpreshotel;
    reservervoyage tmpmodifvoyage;
    QMediaPlayer *player = new QMediaPlayer();
    notification ok;
};
#endif // MAINWINDOW_H
