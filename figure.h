#ifndef FIGURE_H
#define FIGURE_H

#include <QtWidgets/QGraphicsView>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QSplineSeries>

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Figure : public QGraphicsView
{
    Q_OBJECT

public:
    Figure(std::map<std::string, std::vector<double>> &output, QWidget *parent = 0);

private:
    QSplineSeries *interceptor_path;
    QSplineSeries *target_path;
    QChart *chart;
};

#endif // FIGURE_H
