#ifndef FORMCLIENT_H
#define FORMCLIENT_H
#include "client.h"
#include "clientvip.h"
#include <QWidget>

namespace Ui {
class Formclient;
}

class Formclient : public QWidget
{
    Q_OBJECT

public:
    explicit Formclient(QWidget *parent = nullptr);
    ~Formclient();
    void sendMail();
    void mailSent(QString status);
    void browse();

private:
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

    Ui::Formclient *ui;

    client tmpclient;
    clientvip tmpclientvip;
};

#endif // FORMCLIENT_H
