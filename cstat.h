#ifndef cstat_H
#define cstat_H

#include <QWidget>
#include <QMap>
#include <QVector>
namespace Ui {
class cstat;
}

class cstat : public QWidget
{
    Q_OBJECT

public:
    explicit cstat(QWidget *parent = nullptr);
    ~cstat();

private:
    Ui::cstat *ui;
};


#endif // cstat_H
