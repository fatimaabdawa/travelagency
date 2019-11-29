#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "reserverhotel.h"
#include "reservervoyage.h"
#include <QMainWindow>

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
    void on_idhotel_combobox_currentIndexChanged(const QString &arg1);

    void on_Ajout_rhotel_clicked();

    void on_numeropasseport_combobox_currentIndexChanged(const QString &arg1);

    void on_supprimer_rhotel_clicked();

    void on_reservervoyage_ajout_clicked();

    void on_codedestination_rv_ajout_currentIndexChanged(const QString &arg1);

    void on_modifier_rhotel_clicked();

    void on_datereservation_ajout_userDateChanged(const QDate &date);

    void on_idhotel_supprimer_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    reservervoyage tmpreservoyage;
    reserverhotel tmpajouth;
    reserverhotel tmpreshotel;
};
#endif // MAINWINDOW_H
