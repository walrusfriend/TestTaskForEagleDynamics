#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_startRocketVelocity(0.0),
      m_startTargetVelocity(0.0),
      m_startDistinace(0.0),
      ui(new Ui::MainWindow)
{
    // setting the output
    output["t"];
    output["V"];
    output["V_target"];
    output["n"];
    output["n_target"];
    output["x"];
    output["x_target"];
    output["z"];
    output["z_target"];
    output["distance"];

    // create rocket and target objects
    rocket.reset(new Rocket(m_startRocketVelocity));
    target.reset(new Target(m_startTargetVelocity));

    // set initial values and constants
    const double g = 9.8066;
        // The atmospheric parameters are taken for an altitude of 1000 m
    const double rho = 1.1117;  // density, kg/m3
    const double a   = 336.4;   // sound velocity, m/s

    // calculations
    integrationEuler(output, *rocket, *target);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startSimulation()
{
    double tmp;
    bool isOk;

    tmp = ui->le_rocketVelocity->text().toDouble(&isOk);
    if (isOk)
        m_startRocketVelocity = tmp;
    else
        qDebug() << "Incorrect value!";

    tmp = ui->le_targetVelocity->text().toDouble(&isOk);
    if (isOk)
        m_startTargetVelocity = tmp;
    else
        qDebug() << "Incorrect value!";

    tmp = ui->le_initialDistance->text().toDouble();
    if (isOk)
        m_startDistinace      = tmp;
    else
        qDebug() << "Incorrect value!";
}

void MainWindow::integrationEuler(std::map<std::string, std::vector<double>>& output,
                                  Rocket &rocket,
                                  Target &target)
{
    qDebug() << "We're in the calcualtion part";
}

