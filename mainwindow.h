#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>

#include "main.h"
#include "rocket.h"
#include "target.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void startSimulation();

private:
    double m_startRocketVelocity;
    double m_startTargetVelocity;
    double m_startDistinace;

    std::map<std::string, std::vector<double>> output;

    QScopedPointer<Rocket> rocket;
    QScopedPointer<Target> target;

    Ui::MainWindow *ui;

    void integrationEuler(std::map<std::string, std::vector<double>>&, Rocket&, Target&);
};
#endif // MAINWINDOW_H
