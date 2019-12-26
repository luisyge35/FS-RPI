#include "mainwindow.h"
#include "regulador.h"
#include "adc_max127_i2c.h"
#include <structs_hilos.h>
#include <vc.h>
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    // Objetos necesarios para el control
    ADC_MAX127_I2C ADC(0x28);
    regulador speed_reg(3,1,4,0.010);
    regulador position_reg(2,0,0,0);

    // Variables compartidas
    VC variables_compartidas;

    // Estructuras para los hilos
    struct s_reg control;
    struct s_machine state_machine;
    struct s_pantalla GUI;

    control.adc          = &ADC;
    control.speed_reg    = &speed_reg;
    control.position_reg = &position_reg;
    control.varc         = &variables_compartidas;

    state_machine.varc   = &variables_compartidas;

    GUI.varc         = &variables_compartidas;
    GUI.reg_speed    = &speed_reg;
    GUI.reg_position = &position_reg;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
