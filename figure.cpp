#include <QtWidgets/QGraphicsScene>
#include <QtCharts/QChart>
#include <QtCharts/QSplineSeries>

#include "figure.h"

Figure::Figure(std::map<std::string, std::vector<double>> &output,
               QWidget *parent) :
    QGraphicsView(new QGraphicsScene, parent)
{
    // Transform data
    QSplineSeries *interceptor_path = new QSplineSeries;
    QSplineSeries *target_path = new QSplineSeries;

    for (int i = 0; i < output["x"].size(); ++i) {
        interceptor_path->append(output["x"][i], output["z"][i]);
        target_path->append(output["x_target"][i], output["z_target"][i]);
    }

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    chart = new QChart;
    chart->setMinimumSize(640, 480);
    chart->setTitle("Flight path");

    interceptor_path->setName("Interceptor");
    target_path->setName("Target");

    chart->addSeries(interceptor_path);
    chart->addSeries(target_path);

    chart->createDefaultAxes();

    scene()->addItem(chart);
}
