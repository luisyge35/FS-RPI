#ifndef VC_H
#define VC_H
#include <pthread.h>
#include <fdt.h>
#include <time.h>
#include <semaphore.h>

enum modes{
    Speed_Control,
    Position_Control,
    Emergency
};


class VC{
public:
    VC(float ref = 1.0,modes = Speed_Control){
        referencia = ref;

        // ESTABLECIMIENTO DE PROTOCOLO DE TECHO DE PRIORIDAD INMEDIATO
        pthread_mutexattr_init(&mutexattr_prioceiling);
        pthread_mutexattr_setprotocol(&mutexattr_prioceiling, PTHREAD_PRIO_PROTECT);
        high_prio = sched_get_priority_max(SCHED_RR);
        pthread_mutexattr_setprioceiling(&mutexattr_prioceiling,high_prio);
        pthread_mutex_init(&mut,&mutexattr_prioceiling);   // Inicio el mutex
        ///////////////////////////////////////////////////////////////////

    }


    float get_ref();
    void set_ref(float ref);



private:
    modes mode;
    float referencia;
    pthread_mutex_t mut;
    pthread_mutexattr_t  mutexattr_prioceiling;
    int high_prio;
};
#endif // VC_H
