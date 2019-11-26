#include "GestionTrama.h"
#include <string>
using namespace std;
unsigned char* DaFormatoData(unsigned char* data){
	unsigned char *data_ordenada;
	data_ordenada = new unsigned char [4];
	data_ordenada[0] = data[2];
	data_ordenada[1] = data[3];
	data_ordenada[2] = data[0];
	data_ordenada[3] = data[1];

	return data_ordenada;
}

string PreparaTrama(string ID, unsigned char* datos){ //Junta el id y la trama de datos para enviarla en el formato 123#3433
	string TramaPreparada;
	datos = DaFormatoData(datos);
	TramaPreparada = ID + "#"+string((const char*)datos);
	return TramaPreparada;
}
