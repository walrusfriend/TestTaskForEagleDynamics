#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_startInterceptorVelocity(0.0),
      m_startTargetVelocity(0.0),
      m_startDistance(0.0),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startSimulation()
{
    // Clear all vectors in output map
    output["t"].clear();
    output["V"].clear();
    output["V_target"].clear();
    output["n"].clear();
    output["n_target"].clear();
    output["x"].clear();
    output["x_target"].clear();
    output["z"].clear();
    output["z_target"].clear();
    output["distance"].clear();

    dataValidationCheck();

    // Create interceptor and target objects
    interceptor.reset(new Interceptor(m_startInterceptorVelocity));
    target.reset(new Target(m_startTargetVelocity, m_startDistance));

    // Aim the velocity vector ot the missile and the target at each other
    double phi = atan((target->z - interceptor->z) / (target->x - interceptor->x));
    interceptor->psi = phi;
    target->psi = g_pi + phi;

    // setting the initial values
    output["t"].push_back(0);
    output["V"].push_back(interceptor->V);
    output["V_target"].push_back(target->V);
    output["n"].push_back(interceptor->n);
    output["n_target"].push_back(target->n);
    output["x"].push_back(interceptor->x);
    output["x_target"].push_back(target->x);
    output["z"].push_back(interceptor->z);
    output["z_target"].push_back(target->z);
    output["distance"].push_back(m_startDistance);

    //   Calculations
    solver.reset(new Solver);
    solver->integrationEuler(output, *interceptor, *target);

    // Output
    figure.reset(new Figure(output));
    figure->show();

}

void MainWindow::dataValidationCheck()
{
    double tmp;
    bool isOk;

    tmp = ui->le_interceptorVelocity->text().toDouble(&isOk);
    if (isOk)
        m_startInterceptorVelocity = tmp;
    else
        std::cerr << "Incorrect value!" << std::endl;

    tmp = ui->le_targetVelocity->text().toDouble(&isOk);
    if (isOk)
        m_startTargetVelocity = tmp;
    else
        std::cerr << "Incorrect value!" << std::endl;

    tmp = ui->le_initialDistance->text().toDouble();
    if (isOk)
        m_startDistance      = tmp;
    else
        std::cerr << "Incorrect value!" << std::endl;
}

