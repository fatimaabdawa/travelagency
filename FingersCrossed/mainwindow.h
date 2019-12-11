#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "destination.h"
#include "hotel.h"
#include <QMainWindow>
#include "notification.h"
#include <QMediaPlayer>
#include <QtMultimedia>

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

    void on_pushButton_clicked();

    void on_Code_destination_ajouthotel_currentIndexChanged();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_music_button_clicked();

    void on_mute_button_clicked();

private:
    Ui::MainWindow *ui;
    destination tmpdestination;
    hotel tmphotel;
    QString valeur="";
    int etat=0;
    notification ok;
    QMediaPlayer *player = new QMediaPlayer();
};
#endif // MAINWINDOW_H
