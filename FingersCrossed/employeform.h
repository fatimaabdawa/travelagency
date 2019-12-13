#ifndef EMPLOYEFORM_H
#define EMPLOYEFORM_H
#include <QMainWindow>
#include "contrat.h"
#include <QSound>


namespace Ui {
class employeform;
}

class employeform : public QMainWindow
{
    Q_OBJECT

public:
    explicit employeform(QWidget *parent = nullptr);
    ~employeform();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_seeker_line_textChanged(const QString &arg1);

    void on_ascendingsearch_clicked();

    void on_descendingsearch_clicked();

private:
    Ui::employeform *ui;
    employe tmpemploye;
        contrat tmpcontrat;
        QSound *son;
        int etat = 0;
        QString valeur="";
};

#endif // EMPLOYEFORM_H
