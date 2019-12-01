#include "cstat.h"
#include "ui_cstat.h"
#include "connexion.h"
#include <QMap>
#include <QVector>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtWidgets/QGridLayout>
#include <QSqlQuery>
#include <QDebug>
#include "reservervoyage.h"
QT_CHARTS_USE_NAMESPACE
cstat::cstat(QWidget *cstat):
    QWidget(cstat),
    ui(new Ui::cstat)
{
    ui->setupUi(this);
    QVector <QPieSlice *> tab;
        QPieSeries *series = new QPieSeries();
        QSqlQuery qry;
        float tous=0; // hevouma les variables eli chtekhdm alihom
        float tunis=0;
        float importe=0;

        qry.prepare("select codedestination from voyage ");
        if (qry.exec()) // houni chtparkouri l base mte3K
        {
int nom = qry.value(0).toInt();
            while (qry.next())
            {

    tous++;//hevi etotal
    if (qry.value(0).toInt()==nom)//Houni thot lcondition te3k w 3 tbedlhe b noumrou echamp eli tekhdm alih fi lbase
    {
        tunis++;
    }
    else if(qry.value(0).toInt()!=nom)
    {
        importe++;
    }

            }
        }
        qDebug () << "tous" << tous;
        qDebug () << "tunis " << tunis;
            qDebug () << "importe " << importe;


float testing1 =(tunis*100)/tous;
QString pleasework = QString::number(testing1);
float testing2 =(importe*100)/tous;
QString pleasework1 = QString::number(testing2);
    series ->append("France(Paris): 66%",66);//houni chtafiichi
        series ->append("Bresil: 33%",33);


QPieSlice * slice0= series->slices().at(0);
slice0->setLabelVisible();
QPieSlice * slice1= series->slices().at(1);
slice1->setLabelVisible();

    if (tunis>importe)
    {

       slice0->setExploded();
        slice0->setPen(QPen(Qt::darkGreen,2));
       slice0->setBrush(Qt::red);

    }
    else
    {

 slice1->setExploded();
  slice1->setPen(QPen(Qt::darkGreen,2));
 slice1->setBrush(Qt::red);
    }





    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Destination : ");
    chart->legend()->hide();



                QChartView *chartview = new QChartView (chart);
        chartview->setRenderHint(QPainter::Antialiasing);
        QGridLayout *mainLayout = new QGridLayout;
            mainLayout->addWidget(chartview, 1, 1);
            setLayout(mainLayout);


}

cstat::~cstat()
{
    delete ui;
}
