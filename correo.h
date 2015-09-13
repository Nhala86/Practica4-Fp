#ifndef CORREO_H
#define CORREO_H

using namespace std;

// Declaro el tipo de fecha que va en formato UNIX

typedef time_t tFecha;

// Declaro la estructura que contiene un correo

typedef struct{
	string emisor;
	string destinatario;
	string asunto;
	string contenido;
	tFecha fecha;
	string identificador;
}tCorreo;

/**
** Recibe un identificador de emisor y devuelve un correo con todos sus datos rellenos
**/

void correoNuevo(tCorreo & correo, string emisor);

/**
** Le pide al usuario por pantalla que escriba el contenido del mensaje y lo muestra por pantalla
**/

void contenidoCorreo (string & contenido);

/**
** Le pide al usuario que escriba el asunto de su mensaje y lo muestra por pantalla
**/
void asuntoCorreo (string & asunto);

/**
** Le pide al usuario que escriba la direccion del destinatario del mensaje y lo muestra por pantalla
**/

void destinatarioCorreo (string & destinatario);

/**
** Funcion encargada de leer cada linea del contenido correctamente
** Es llamada por la funcion contenidoCorreo para poder leer el mensaje
**/

void leerContenido (string & texto, ifstream & archivo);

/**
** Recibe un identificador de emisor y el correo original que se va a contestar, y devuelve un correo con todos sus datos rellenos
**/

void correoContestacion(const tCorreo & correoOriginal, tCorreo & correo, string emisor);

/**
** Devuelve un string con el contenido completo del correo para poderlo mostrar por consola
**/

string aCadena (const tCorreo & correo);

/**
** Devuelve un string que contiene la información que se mostrará en la bandeja de entrada/salida: emisor, asunto y fecha sin hora
**/

string obtenerCabecera(const tCorreo & correo);

/**
** Dado un flujo de archivo de entrada (ya abierto), lee los datos que corresponden a un correo y lo devuelve
** Devuelve false sólo si el correo cargado no es válido
**/

bool cargar(tCorreo & correo, ifstream & archivo);

/**
** Dado un flujo de archivo de salida (ya abierto), escribe en el flujo los datos que corresponden a un correo
**/

void guardar(const tCorreo & correo, ofstream & archivo);

/**
** String que devuelve la fecha con la hora (forma UNIX)
**/

string mostrarFecha(tFecha fecha);

/**
** String que devuelve la fecha sin la hora (forma UNIX)
**/

string mostrarSoloDia(tFecha fecha);

/**
** Muestra la cabecera del mensaje y el contenido, funcion utilizada para la opcion "Lectura Rapida"
**/

void mostrarCorreo (tCorreo correo);

/**
** Elimina los "RE: " de los mensajes para poder ser ordenados solo por el asunto
**/

void eliminarRe (tCorreo & correo);

/**
** Se encarga de decir si un mensaje es menor a otro teniendo encuenta primero el asunto y despues la fecha en caso de que el asunto sea el mismo
** LLama a eliminarRe para poder ordenar los mensajes
**/

bool operator< (const tCorreo & correo1, const tCorreo & correo2);

#endif
