#ifndef STRUCTS_H
#define STRUCTS_H
#include <fdt.h>
#include <vc.h>
#include <regulador.h>
#include <adc_max127_i2c.h>

// Estructuras de parametros de los hilos

// Regulador
struct s_reg{
    regulador *speed_reg;
    regulador *position_reg;
    VC *varc;
    ADC_MAX127_I2C *adc;   
};

// Maquina de estados
struct s_machine{
    VC *varc;
};

// Pantalla
struct s_pantalla{
    VC *varc;
    regulador *reg_speed;
    regulador *reg_position;
};
#endif // STRUCTS_H
