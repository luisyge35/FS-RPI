#include <iostream>
#include <pthread.h>
#include <string>

#include "cansend.h"
#include "i2com.h"
#include "GestionTrama.h"

#define TS 100E6 //100ms CAMBIAR A E6S
using namespace std;

//-------------DECLARACIÓN DE VARIABLE GLOBAL
const string ID_INVERSOR = "002";
uint16_t dato;
int id;
pthread_mutex_t cerrojo;
Ccan * Can;
I2com * i2com;
string trama_para_enviar_string;
char* trama_para_enviar_uchar;


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
	intervalo.tv_sec =1;
	clock_gettime(CLOCK_REALTIME, &siguiente);
	inicio = siguiente;
	while (1)
	{
		siguiente = siguiente + intervalo;
		pthread_mutex_lock(&cerrojo);
		try{
			trama_para_enviar_uchar = (char*)trama_para_enviar_string.data();
			Can->Write(trama_para_enviar_uchar);
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
	while(1){
		static unsigned char* read_value;
		try{
			read_value = i2com->read_bus(2); //reads 2 bytes
		}
		catch(char const* e){
			cout << e<< '\n';
		}
		pthread_mutex_lock(&cerrojo);
		trama_para_enviar_string = PreparaTrama(ID_INVERSOR,read_value);
		pthread_mutex_unlock(&cerrojo);
	}
}

int main()
{

	try{
			Can = new Ccan(true,(char *)"vcan0");
	}
	catch(char const* e){
		cout <<  e<< '\n';
	}
	i2com = new I2com(true,(char *)"/dev/i2c-1",40);//Confirmar la dirección
	try{
			i2com->VirtualConnect((char *)"/dev/i2c-1",40);
	}
	catch(char const* e){
		cout <<  e<< '\n';
	}

	pthread_t h_can, h_i2c;

	if (pthread_mutex_init(&cerrojo, NULL) == -1)
		throw("Error al crear el mutex");

	pthread_create(&h_can, NULL, HiloCan, 0);
	pthread_create(&h_i2c, NULL, HiloI2c, 0);

	pthread_join(h_can, nullptr);
	pthread_join(h_i2c, nullptr);

	return 0;
}
