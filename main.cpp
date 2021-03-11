#include <ctime>
#include <iostream>

#include <QApplication>

#include "mainwindow.h"

// set initial global values and constants
const double g_g = 9.8066;
const double g_pi = 3.1415;
    // The atmospheric parameters are taken for an altitude of 1000 m
const double g_rho = 1.1117;  // density, kg/m3
const double g_a   = 336.4;   // sound velocity, m/s

int main(int argc, char *argv[])
{
    // set the seed for random generator
    srand(time(0));

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
