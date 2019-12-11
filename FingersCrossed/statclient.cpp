#include "statclient.h"
#include "ui_statclient.h"
#include "QSqlQuery"
#include "client.h"
#include "qcustomplot.h"
#include"QSqlRecord"

statclient::statclient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statclient)
{
    ui->setupUi(this);
    this->setWindowTitle("Statistiques");
    makePolt();
}

statclient::~statclient()
{
    delete ui;
}

void statclient::makePolt()
{
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->customPlot->setBackground(QBrush(gradient));
    QCPBars *regen = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    regen->setAntialiased(false);
    regen->setStackingGap(1);
    regen->setName("Moyenne des ages");

    regen->setPen(QPen(QColor(250, 170, 20).lighter(150)));
    regen->setBrush(QColor(250,170,20));


    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 ;
    labels << "Tunisie" << "Autres Pays" ;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTicks(false);
    ui->customPlot->xAxis->setTickLength(0, 4);
    ui->customPlot->xAxis->setRange(0, 8);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0,50);
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> regenData;

    client c;
    QSqlQuery query1=c.fctq();
    while (query1.next()) {
        int  nbr_faute;
                           int  nbr_fautee = query1.value(0).toInt();
                           QSqlQuery query2=c.fctq2();
                           while (query2.next()) {
                                                  nbr_faute = query2.value(0).toInt();
                                                  break;
                                                    }
                           regenData<< nbr_fautee<< nbr_faute;
                           break;
                             }
    regen->setData(ticks, regenData);

    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);


}
