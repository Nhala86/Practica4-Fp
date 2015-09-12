#ifndef LISTACORREOS_H
#define LISTACORREOS_H

using namespace std;

#include"correo.h"

// Declaro las constantes del maximo de correos que puede tener la lista de correos y el nombre del .txt

const int MAX_CORREOS = 50;
const string mailCorreo = "ListaCorreo.txt";

/**
** Creo la estructura que tiene la lista de correos, con tantas posiciones como indica la constante
** LLama a tCorreo, ya que cada posicion tiene un tipo correo
** Ademas tiene un contador
**/
typedef struct{
	tCorreo listaMail[MAX_CORREOS];
	int contador;
}tListaCorreos;

/**
** Inicializo la lista
**/

void inicializar(tListaCorreos & correos);

/**
** Implementa la carga de la lista de correos desde el fichero de correos de nombre <NombreDominio>_correos.txt
**/

bool cargar(tListaCorreos & correos, string dominio);

/**
** Implementa el guardado de la lista de correos en el fichero de correos de nombre <NombreDominio>_ correos.txt
** Guarda en fichero la lista de correos
**/

void guardar (const tListaCorreos & correos, string dominio);

/**
** Dado un correo, si hay espacio en la lista, lo coloca en la posición correspondiente de acuerdo con su identificador y devuelve true
** Si no lo ha podido colocar devuelve false
**/

bool insertar(tListaCorreos & correos, const tCorreo & correo);




bool borrar(tListaCorreos &correos, string id);

/**
** Dado un identificador de correo y la lista, devuelve, si dicho identificador existe en la lista, su posición y el valor true
** Si no existe en la lista, la posición que le correspondería y el valor false
**/

bool buscar (const tListaCorreos & correos, string id, int & pos);

/**
** Dada una lista de correos la devuelve ordenada por asunto y fecha
** Como es una clave de ordenación doble, habrá que redefinir el operador de comparación en el módulo que corresponda
**/

void ordenar_AF(tListaCorreos & correos);

#endif
