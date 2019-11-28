#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<prromtion.h>
#include<evenemant.h>
#include <QMainWindow>
#include"login.h"
#include"smtp.h"

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

    void sendMail();
      void mailSent(QString);


    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();
    void refresh();



    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_comboBox_supprimer_activated(const QString &arg1);

    void on_consulter_stat_clicked();

    void on_pushbouton_print_clicked();

    void on_comboBox_2_activated(const QString &arg1);

    void on_comboBox_activated(const QString &arg1);

    void on_supprimer_clicked();

    void on_dateDebut_userDateChanged(const QDate &date);

    void on_datefin_userDateChanged(const QDate &date);

    void on_dated_userDateChanged(const QDate &date);

    void on_datef_userDateChanged(const QDate &date);

    void on_modifier_clicked_clicked();

    void on_comboBox_4_activated(const QString &arg1);

    void on_comboBox_3_activated(const QString &arg1);

    void on_dateEdit_debut_userDateChanged(const QDate &date);

    void on_dateEdit_fin_userDateChanged(const QDate &date);

    void on_dateEdit_modifprodebut_userDateChanged(const QDate &date);

    void on_dateEdit_modifprofin_userDateChanged(const QDate &date);

private:
    Ui::MainWindow *ui;
prromtion tmpprromotion;
evenemant tmpevenemant;

};
#endif // MAINWINDOW_H
