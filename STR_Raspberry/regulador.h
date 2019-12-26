#ifndef REGULADOR_H
#define REGULADOR_H
//#include <conversorad.h>
//#include <sensor.h>
#include "fdt.h"
#include "pthread.h"

class regulador
{
public:
    regulador(float K_p,float K_i,float T_i,float T_m){
        Kp = K_p;
        Ki = K_i;
        Ti = T_i;
        Tm = T_m;
        for(int i = 0;i<2;i++){
            uk[i] = 0;
            ek[i] = 0;
            ik[i] = 0;
        }
    }

      //~regulador();

     // Getters y setters para las variables del regulador, acceso protegido por mutex
     void set_Kp(float);
     float get_Kp();
     void set_Ki(float);
     float get_Ki();
     void set_Ti(float);
     float get_Ti();
     float get_Tm();
     void set_Tm(float);

     // Calculo de la accion de control a partir de un error dado.
     // La salida ya es directamente el duty que le tenemos que meter al pwm
     float Calcular_Salida(float error);

private:
     float Kp,Ki,Ti,Tm;
     float uk[2],ek[2],ik[2];
     pthread_mutex_t mutt_regulador;
     void Desplazar_Tabla(float *tabla,int n,float new_item);
};

#endif // REGULADOR_H
