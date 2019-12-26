#include "regulador.h"

void regulador::Desplazar_Tabla(float *tabla,int n,float new_item){
    int i;
         for (i=n-1;i>0;i--){
             tabla[i]=tabla[i-1];
         }
    tabla[0] = new_item;
}

float regulador::Calcular_Salida(float error){
    // Cerramos mutex por si acaso
    pthread_mutex_lock(&mutt_regulador);
    // Actualizamos las tablas de error y de accion de control
    Desplazar_Tabla(ek,2,error);
    Desplazar_Tabla(uk,2,0);
    // Calculamos los parametros de PID
    float Proportional = Kp * ek[0];
    float Integral     = ik[0] + (Ki*Tm/Ti) * ek[1];
    // Calculamos la salida
    uk[0] = (Proportional + Integral) + 50;
    // Actualizamos el el valor de la tabla de la accion integral
    Desplazar_Tabla(ik,2,Integral);
    pthread_mutex_unlock(&mutt_regulador);
    return uk[0];
}


float regulador::get_Ti(){
    float aux;
    pthread_mutex_lock(&mutt_regulador);
    aux = Ti;
    pthread_mutex_unlock(&mutt_regulador);
    return aux;
}

void regulador::set_Ti(float new_Ti){
    pthread_mutex_lock(&mutt_regulador);
    Ti = new_Ti;
    pthread_mutex_unlock(&mutt_regulador);
}


float regulador::get_Kp(){
    float aux;
    pthread_mutex_lock(&mutt_regulador);
    aux = Kp;
    pthread_mutex_unlock(&mutt_regulador);
    return aux;
}

void regulador::set_Kp(float new_Kp){
    pthread_mutex_lock(&mutt_regulador);
    Kp = new_Kp;
    pthread_mutex_unlock(&mutt_regulador);
}

float regulador::get_Ki(){
    float aux;
    pthread_mutex_lock(&mutt_regulador);
    aux = Ki;
    pthread_mutex_unlock(&mutt_regulador);
    return aux;
}

void regulador::set_Ki(float new_Ki){
    pthread_mutex_lock(&mutt_regulador);
    Ki = new_Ki;
    pthread_mutex_unlock(&mutt_regulador);
}

float regulador::get_Tm(){
    float aux;
    pthread_mutex_lock(&mutt_regulador);
    aux = Tm;
    pthread_mutex_unlock(&mutt_regulador);
    return aux;
}

void regulador::set_Tm(float new_Tm){
    pthread_mutex_lock(&mutt_regulador);
    Tm = new_Tm;
    pthread_mutex_unlock(&mutt_regulador);
}
