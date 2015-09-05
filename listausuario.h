#ifndef LISTAUSUARIO_H
#define LISTAUSUARIO_H

using namespace std;

#include"usuario.h"

 // Declaro las constantes para el maximo de usuarios y el nombre de .txt
 
const string listaUsuarios = "Usuarios.txt";
const int MAX_USUARIOS = 50;

// Declaro la estructura que tiene la lista de usuarios

typedef struct {
	tUsuario usuario [MAX_USUARIOS];
	int contador;
}tListaUsuarios;

/**
** Inicializo la lista
**/

void inicializar (tListaUsuarios & usuarios);

/**
** Implementa la carga de la lista de usuarios desde el fichero de usuarios de nombre <NombreDominio>_usuarios.txt
**/

bool cargar (tListaUsuarios & usuarios, string dominio);

/**
** Implementa el guardado de la lista de usuarios en el fichero de usuarios de nombre <NombreDominio>_usuarios.txt
**/

void guardar (const tListaUsuarios & usuarios, string dominio);

/**
** Añade un usuario en la posición de la lista que le corresponde, si hay sitio para ello
** Además devuelve un booleano indicando si la operación tuvo éxito o no
**/

bool aniadir (tListaUsuarios & usuarios, const tUsuario & usuario);

/**
** Dado un identificador de usuario y la lista, devuelve, si dicho identificador existe en la lista, su posición y el valor true
** Si no existe en la lista, la posición que le correspondería y el valor false
**/

bool buscarUsuario (const tListaUsuarios & usuarios, string id, int & posicion);

/**
** Ordena los usuarios segun su posicion
**/

void ordenar (tListaUsuarios & usuarios);

#endif