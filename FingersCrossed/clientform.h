#ifndef CLIENTFORM_H
#define CLIENTFORM_H

#include <QMainWindow>
#include "client.h"
#include "clientvip.h"

namespace Ui {
class Clientform;
}

class Clientform : public QMainWindow
{
    Q_OBJECT

public:
    explicit Clientform(QWidget *parent = nullptr);
    ~Clientform();
    void sendMail();
    void mailSent(QString status);
    void browse();

private slots:
    void showTime();
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

private :
    Ui::Clientform *ui;

    client tmpclient;
    clientvip tmpclientvip;
};

#endif // CLIENTFORM_H
