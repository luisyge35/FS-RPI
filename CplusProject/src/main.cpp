#include <iostream>
#include <pthread.h>

#include "cansend.h"
#include "lib.h"

#define TS 100E6 //100ms

using namespace std;

//-------------DECLARACIÓN DE VARIABLE GLOBAL
uint16_t dato;
uint16_t id;
pthread_mutex_t cerrojo;
Ccan * Can;



struct timespec operator+(struct timespec t1, struct timespec t2)
{
	struct timespec suma;
	suma.tv_sec = t1.tv_sec + t2.tv_sec;	// calcula segundos
	suma.tv_nsec = t1.tv_nsec + t2.tv_nsec; // calcula nsegundos
	if (suma.tv_nsec >= 1E9)				// ver si tenemos un segundo completo
	{
		suma.tv_sec++;		 // añadir 1 a la cuenta de segundos
		suma.tv_nsec -= 1E9; // calcular los ns que quedan
	}
	return suma;
}

void *HiloCan(void *)
{
	struct timespec inicio, siguiente, intervalo;
	intervalo.tv_nsec = TS;
	clock_gettime(CLOCK_REALTIME, &siguiente);
	inicio = siguiente;
	while (1)
	{
		id = 1;
		dato = 0;
		char  trama[]="0x1#1212";
		//strcat(trama,"0x1#1212");
		siguiente = siguiente + intervalo;
		pthread_mutex_lock(&cerrojo);
		try{
			Can->Write(trama);
		}
		catch(char const* e){
			cout << e<< '\n';
		}
		pthread_mutex_unlock(&cerrojo);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &siguiente, nullptr);
	}
}

void *HiloI2c(void *)
{
	//TODO
	return nullptr;
}

int main()
{

	try{
			Can = new Ccan((char *)"vcan0");
	}
	catch(char const* e){
		cout <<  e<< '\n';
	}

	pthread_t h_can, h_i2c;

	if (pthread_mutex_init(&cerrojo, NULL) == -1)
		throw("Error al crear el mutex");

	pthread_create(&h_can, NULL, HiloCan, 0);
	pthread_create(&h_i2c, NULL, HiloI2c, 0);
	cout << "hi" << '\n';
	pthread_join(h_can, nullptr);
	pthread_join(h_i2c, nullptr);

	return 0;
}
