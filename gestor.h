#ifndef GESTOR_H
#define GESTOR_H

using namespace std;

#include"listacorreos.h"
#include"listaregistros.h"
#include"listausuario.h"

// Declaro la constante del dominio

const string DOMINIO = "fdimail.com";

// Declaro la estructura del tGestor, que contiene un gestor
typedef struct{
	string dominio;
	int usuarioActivo;
	tListaCorreos correos;
	tListaUsuarios usuarios;
} tGestor;

/**
** Inicializa el gestor e intenta arrancarlo cargando la información del dominio que se le pasa como parámetro
** Para ello inicializará y cargará la lista de usuarios y de correos de dicho dominio
** Si tiene éxito en todas las operaciones devuelve true y si alguna falla devuelve false
**/

bool arrancar (tGestor & gestor, string dominio);

/**
** Esta operación apaga el gestor y guarda para ello las listas de usuarios y de correos del dominio que se encontrase activo en ese momento
**/

void apagar(const tGestor & gestor);

/**
** Lee los datos de usuario necesarios para crear una cuenta (id y contraseña)
** Si el id de usuario no existe y hay espacio en la lista de usuarios, crea la cuenta del usuario y lo registra como usuario activo en el gestor
** Devuelve un booleano indicando si la operación tuvo éxito
**/

bool crearCuenta(tGestor & gestor);

/**
** Lee los datos de usuario necesarios para validar la cuenta (id y contraseña)
** Si el usuario existe y la contraseña coincide, registra al usuario como usuario activo
** Devuelve un booleano indicando si la operación tuvo éxito
**/

bool iniciarSesion (tGestor & gestor);

/**
** Solicita el correo que el usuario quiere leer (es el número con el que el correo es mostrado en la bandeja), valida que existe y lo marca como leído
** Busca el correo en la lista de correos y si lo encuentra lo muestra en la pantalla de lectura del correo
**/

void leerCorreo(tGestor & gestor, tListaRegistros & listaReg);

/**
** Implementa el envío del correo en la aplicación. Para ello el correo recibido como parámetro es insertado en la lista de correo
** Si ha habido éxito, se inserta el registro en la lista de registros enviados del emisor
** y se intenta insertar igualmente un registro de dicho correo en la lista de registros recibidos del destinatario del correo
** Si el destinatario no existe o si su bandeja de entrada está llena, entonces se mostrará un mensaje de error
**/

void enviarCorreo (tGestor & gestor, const tCorreo & correo);

/**
** Implementa el borrado del correo de una bandeja de un determinado usuario
** Para ello, solicita el correo que el usuario quiere borrar, valida que existe y si es así, procede a borrarlo
**/

void borrarCorreo(tGestor & gestor, tListaRegistros & listaReg);

/**
** Implementa la lectura rápida de correos sin leer
** El resultado es que muestra en una pantalla todos los correos sin leer ordenados por asunto (ignorando todos los “Re: ”) y por fecha
** Al finalizar su ejecución los correos sin leer quedarán marcados como leídos
**/

void lecturaRapida(tGestor & gestor, tListaRegistros & listaReg);

/**
** Inicializo en la lista la posicion dominio con el dominio "fdimail.com"
**/

void inicializar (tGestor & gestor, string dominio);

 /**
** Funcion encargada del menu de la sesion. Es llamada por el main
**/

void gestionarSesion(tGestor & gestor);

/**
** Muestra las opciones del menu por pantalla
**/

void mostrarMenu (bool esEntrada);

/**
** Funcion encargada de colocar la cabecera de las bandejas de salida y entrada
** Ademas es la encargada de cambiar de una bandeja a otra
**/

void mostrarInterFazUsuario(tGestor & gestor, bool esEntrada);

/**
** Funciones que controlan las rallitas que debe colocarse en las cabeceras
**/

void lineaDeSeparacion ();

void lineasDeCabecera ();

/**
** Es la funcion de colocar cada correo que llega adecuadamente para mostrarla en pantalla; debajo de cada apartado de la cabecera su correspondiente parte del correo; Emisor, Asunto y Fecha
**/

void verBandeja (const tGestor & gestor, bool esEntrada);

#endif
