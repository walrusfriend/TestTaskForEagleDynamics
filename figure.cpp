#include <QtWidgets/QGraphicsScene>
#include <QtCharts/QChart>

#include "figure.h"

Figure::Figure(std::map<std::string, std::vector<double>> &output,
               QWidget *parent) :
    QGraphicsView(new QGraphicsScene, parent)
{
    // Transform data
    QSplineSeries *interceptor_path = new QSplineSeries;
    QSplineSeries *target_path = new QSplineSeries;
    QSplineSeries *damageRing = new QSplineSeries;

    for (int i = 0; i < output["x"].size(); ++i) {
        interceptor_path->append(output["x"][i], output["z"][i]);
        target_path->append(output["x_target"][i], output["z_target"][i]);
    }
    damageRing->append(target_path->pointsVector().back().x() + 15,
                       target_path->pointsVector().back().y());
    damageRing->append(target_path->pointsVector().back().x(),
                       target_path->pointsVector().back().y() - 15);
    damageRing->append(target_path->pointsVector().back().x() - 15,
                       target_path->pointsVector().back().y());
    damageRing->append(target_path->pointsVector().back().x(),
                       target_path->pointsVector().back().y() + 15);
    damageRing->append(target_path->pointsVector().back().x() + 15,
                       target_path->pointsVector().back().y());


    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    chart = new QChart;
    chart->setMinimumSize(640, 480);
    chart->setTitle("Flight path");

    interceptor_path->setName("Interceptor");
    target_path->setName("Target");
    damageRing->setName("Damage area");

    chart->addSeries(interceptor_path);
    chart->addSeries(target_path);
    chart->addSeries(damageRing);

    chart->createDefaultAxes();

    chart->axes(Qt::Horizontal, interceptor_path).back()->setTitleText("Xg");
    chart->axes(Qt::Vertical, interceptor_path).back()->setTitleText("Zg");

    scene()->addItem(chart);
}
