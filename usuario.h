#ifndef USUARIO_H
#define USUARIO_H

using namespace std;

#include"listaregistros.h"

// Declaro la constante centinela para la finalizacion del la lectura de los archivos

const string CENTINELA = "XXX";

// Declaro la estructura que contiene un usuario

typedef struct {
	string nombre;
	string contrasenia;
	tListaRegistros recibidos;
	tListaRegistros enviados;
}tUsuario;

/**
** Dado un flujo de archivo (ya abierto), se carga un usuario de fichero
**/

bool cargar(tUsuario & usuario, ifstream & archivo);

/**
** Dado un flujo de archivo (ya abierto), se guarda un usuario en fichero
**/

void guardar(const tUsuario & usuario, ofstream & archivo);

/**
** Recibe un identificador de usuario y una contraseña y los asigna al usuario
**/

void inicializar(tUsuario & usuario, string id, string contrasenia);

/**
** Recibe una contraseña y un usuario y devuelve si la contraseña es correcta o no
**/

bool validarContrasenia(const tUsuario & usuario, string contrasenia);

#endif
