#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QPixmap>
#include <QMediaPlayer>
#include "Arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();
    int Authentification(QString,QString);



signals :
    void adminSignal();
    void habibSignal();
    void MohamedSignal();
    void OussemaSignal();
    void salahSignal();
    void fatimaSignal();
    void skanderSignal();
private slots:
    //void update_label();

    void on_connecter_clicked();
    void on_showpassword_clicked(bool checked);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::login *ui;
    QMediaPlayer pl;
    Arduino A;
    QByteArray data;
};
#endif // LOGIN_H
