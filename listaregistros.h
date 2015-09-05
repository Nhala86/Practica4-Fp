#ifndef LISTAREGISTROS_H
#define LISTAREGISTROS_H

using namespace std;

// Declaro la constante del maximo de registros que puede tener la lista de registros

const int MAX_REGS = 10;

// Defino la estructura que tiene un registro: una identificacion de correo y un boleano encargado de decir: 0 si ha sido leido el mensaje o 1 si no ha sido leido

typedef struct{
	string idcorreo;
	bool leido;
}tRegistro;

// Declaro la estructura que contiene la lista del registro con la longitud maxima del registro permitidos y un contador

typedef struct{
	tRegistro registros [MAX_REGS];
	int contador;
}tListaRegistros;

/**
** Inicializo el contador 
**/

void inicializar (tListaRegistros & registros);

/**
** Dado un flujo de archivo de entrada (ya abierto), lee los datos que corresponden a una lista de registros y la devuelve
**/

void cargar (tListaRegistros & registros, ifstream & archivo);

/**
** Dado un flujo de archivo de salida (ya abierto), guarda los datos de la lista de registro
**/

void guardar (const tListaRegistros & registros, ofstream & archivo);

/**
** Dado un registro lo inserta al final de la lista. Si la lista está llena devuelve false, en otro caso devuelve true
** Se ejecutará cuando un usuario envíe un correo, se insertará el registro correspondiente en la lista de registros que representa su bandeja de salida 
** También en las listas de registros que representan las bandejas de entrada de cada uno de los destinatarios del correo
**/

bool insertar (tListaRegistros & registros, tRegistro registro);

/**
** Dado un identificador de correo, busca el registro correspondiente y si lo encuentra lo elimina de la lista
** Si no lo encuentra, devuelve false, en otro caso devuelve true
** Este subprograma representa la acción de un usuario del borrado de un determinado correo de una de sus bandejas
**/

bool borrar (tListaRegistros & registros, string id);

/**
** Dado un identificador de correo, busca el correspondiente registro y pone el indicador de leído a true
** La operación devuelve un booleano indicando si se encontró o no el registro
**/

bool correoLeido (tListaRegistros & registros, string id);

/**
** Dado un identificador de correo y la lista, devuelve, si dicho identificador existe en la lista, su posición, y si no existe devuelve -1
**/

int buscar (const tListaRegistros & registros, string id);

/**
** Metodo que lee del archivo cada idcorreo y lo carga en el registro, a la vez pone 0 si lo ha leido y 1 si no lo ha leido
**/

void cargarRegistro (tRegistro & registro, ifstream & archivo);

#endif
