#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCore/QTimer>

QT_CHARTS_BEGIN_NAMESPACE
class QValueAxis;
class QLineSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Chart: public QChart
{
    Q_OBJECT
public:
    Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    void refresh();
    void append(double ratio);
virtual ~Chart();

private:
    QTimer m_timer;
    QLineSeries *m_series;
    QStringList m_titles;
//    QValueAxis *m_axisX;
//    QValueAxis *m_axisY;
    QValueAxis *m_axis;
    QList<double> data;
};

#endif // CHART_H
