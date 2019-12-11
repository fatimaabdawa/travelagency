#ifndef STATCLIENT_H
#define STATCLIENT_H

#include <QWidget>

namespace Ui {
class statclient;
}

class statclient : public QWidget
{
    Q_OBJECT

public:
    explicit statclient(QWidget *parent = nullptr);
    ~statclient();
    void  makePolt();

private:
    Ui::statclient *ui;
};

#endif // STATCLIENT_H
