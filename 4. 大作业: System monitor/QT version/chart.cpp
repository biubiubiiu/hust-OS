#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QChart(QChart::ChartTypeCartesian, parent, wFlags),
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
    axisX()->setRange(0, 60);
    axisY()->setRange(0.0, 100.0);
    axisX()->setLabelsVisible(false);
    axisY()->setLabelsVisible(false);

    // 以下为Chart类的自定义设置
    setAnimationOptions(QChart::NoAnimation); // 默认关闭动画效果
    legend()->hide();                   // 默认不显示图例
    setMargins(QMargins(0, 0, 0, 0));
    setBackgroundRoundness(0);
    setPos(0, 0);
    setTheme(QChart::ChartThemeQt);
}

Chart::~Chart()
{
}

void Chart::append(double ratio)
{
    // 先判断一下数据有效性，免得出事
    if (ratio >= 0 && ratio <= 100)
        data << ratio;
}

void Chart::refresh()
{
    // 维持数表中不超过60个数据
    while (data.size() > 60)
        data.removeFirst();
    // 更新坐标
    m_series->clear();
    int size = data.size();
    for (int i = size - 1; i >= 0; --i)
    {
        m_series->append(60 - (size - 1 - i), data.at(i)); // 目的是为了让图像从右向左移动
    }
}
