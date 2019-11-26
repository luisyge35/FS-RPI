#include <iostream>
#include <pthread.h>
#include <string>

#include "cansend.h"
#include "i2com.h"

#define TS 100E6 //100ms

using namespace std;

//-------------DECLARACIÓN DE VARIABLE GLOBAL
uint16_t dato;
string id = "002";
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



string PreparaTrama(string ID, string datos){ //Junta el id y la trama de datos para enviarla en el formato 123#3433
	string TramaPreparada;
	TramaPreparada = ID + "#"+datos;
	return TramaPreparada;
}

void *HiloCan(void *)
{
	struct timespec inicio, siguiente, intervalo;
	intervalo.tv_nsec = TS;
	clock_gettime(CLOCK_REALTIME, &siguiente);
	inicio = siguiente;
	while (1)
	{
		siguiente = siguiente + intervalo;
		pthread_mutex_lock(&cerrojo);
		try{
			trama_para_enviar_string = PreparaTrama(id,"1233");
			trama_para_enviar_uchar = (char*)trama_para_enviar_string.data();
			Can->Write(trama_para_enviar_uchar); //El id tiene que tener 3 cifras y los datos 4
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
	static unsigned char read_value;
	try{
		read_value = i2com->read_bus(2); //reads 2 bytes
	}
	catch(char const* e){
		cout << e<< '\n';
	}

	pthread_mutex_lock(&cerrojo);
	trama_para_enviar_string = PreparaTrama(id,"1234");
	pthread_mutex_unlock(&cerrojo);
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
	/*
	try{
			i2com = new I2com((char *)"/dev/i2c-1",40);//Confirmar la dirección
	}
	catch(char const* e){
		cout <<  e<< '\n';
	}
	*/

	pthread_t h_can, h_i2c;

	if (pthread_mutex_init(&cerrojo, NULL) == -1)
		throw("Error al crear el mutex");

	pthread_create(&h_can, NULL, HiloCan, 0);
	//pthread_create(&h_i2c, NULL, HiloI2c, 0);

	pthread_join(h_can, nullptr);
	//pthread_join(h_i2c, nullptr);

	return 0;
}
