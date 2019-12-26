#include "vc.h"
float VC::get_ref(){
    float aux;
    pthread_mutex_lock(&mut);
    aux = referencia;
    pthread_mutex_unlock(&mut);
    return aux;
}

void VC::set_ref(float ref){
    pthread_mutex_lock(&mut);
    referencia = ref;
    pthread_mutex_unlock(&mut);
}
