#ifndef LOGIN_H
#define LOGIN_H
#include<QtSql>
#include<QtDebug>
#include<QFileInfo>
#include <QDialog>
#include"prromtion.h"
#include"evenemant.h"
#include"mainwindow.h"
#include <Qsound>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::login *ui;
     QSqlDatabase db;

};

#endif // LOGIN_H
