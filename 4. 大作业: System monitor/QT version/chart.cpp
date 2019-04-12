#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axis(new QValueAxis)
    {
    m_series = new QLineSeries(this);
    QPen pen(Qt::green);
    pen.setWidth(3);
    m_series->setPen(pen);
    m_series->append(0, 0);

    addSeries(m_series);
    createDefaultAxes();
    setAxisX(m_axis, m_series);
    m_axis->setTickCount(6);
    axisX()->setRange(60, 0);
    axisY()->setRange(0.0, 100.0);

    // 以下为Chart类的自定义设置
    setAnimationOptions(QChart::NoAnimation);   // 默认关闭动画效果
    this->legend()->hide();     // 默认不显示图例
}

Chart::~Chart()
{

}

void Chart::append(double ratio)
{
    // 先判断一下数据有效性，小心驶得万年船
    if(ratio >= 0 && ratio <= 100)
        data << ratio;
}

void Chart::refresh()
{
    // 图表中最多容纳60个数据
    while(data.size() > 60)
        data.removeFirst();
    if(isVisible())
    {
        m_series->clear();
        int size = data.size();
        for(int i = size - 1; i >= 0; --i){
            m_series->append(60 - (size - 1 - i), data.at(i));  // 目的是为了让图像从右向左移动
        }
    }
}
