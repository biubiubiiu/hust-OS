#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axis(new QValueAxis)
    {
    QObject::connect(&m_timer, &QTimer::timeout, this, &Chart::handleTimeout);
    m_timer.setInterval(1000);

    m_series = new QSplineSeries(this);
    QPen pen(Qt::green);
    pen.setWidth(3);
    m_series->setPen(pen);
    m_series->append(0, 0);

    addSeries(m_series);
    createDefaultAxes();
    setAxisX(m_axis, m_series);
//    m_axis->setTickCount(6);
    axisX()->setRange(0, 60);
    axisY()->setRange(0.0, 100.0);

    m_timer.start();
}

Chart::~Chart()
{

}

void Chart::setFunc(double (*f)(void))
{
    this->newData = f;
}

void Chart::handleTimeout()
{
    data << newData();
    while(data.size() > 60)
        data.removeFirst();
    if(isVisible())
    {
        m_series->clear();
        for(int i = 0;i<data.size();++i){
            m_series->append(i, data.at(i));
        }
    }
}
