#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "destination.h"
#include "hotel.h"
#include <QMainWindow>
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


    void on_ajouter_destination_clicked();

    void on_SupprimerDestination_clicked();

    void on_ajouter_hotel_clicked();

    void on_supprimer_hotel_clicked();


    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_Modifier_clicked();

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_ModifierHotel_clicked();

    void on_trierChercher_2_textChanged(const QString &arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_trierChercher_textChanged(const QString &arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_mail_button_clicked();



    void on_TabDestinations_tabBarClicked(int index);

    void on_pushButton_clicked();

    void on_Code_destination_ajouthotel_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    destination tmpdestination;
    hotel tmphotel;
    QString valeur="";
    int etat=0;
    notification ok;
};
#endif // MAINWINDOW_H
