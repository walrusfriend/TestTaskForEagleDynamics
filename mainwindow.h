#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>

#include "interceptor.h"
#include "target.h"
#include "solver.h"
#include "figure.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern const double g_pi;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void startSimulation();

private:
    double m_startInterceptorVelocity;
    double m_startTargetVelocity;
    double m_startDistance;

    std::map<std::string, std::vector<double>> output;

    QScopedPointer<Interceptor> interceptor;
    QScopedPointer<Target> target;
    QScopedPointer<Solver> solver;
    QScopedPointer<Figure> figure;

    Ui::MainWindow *ui;

    void dataValidationCheck();
};
#endif // MAINWINDOW_H
