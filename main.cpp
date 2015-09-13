/**
** Practica 4
** Lidia Garcia Perez, DNI: 02270177P
** Grupo 1º G
**/

// El programa no elimina los asteriscos de no leido, despues de leerlos


#include<iostream>
#include<windows.h>
#include<fstream>
#include<string>

using namespace std;

#include"gestor.h"

// Declaro la funcion del primer menu que se le mostrara por pantalla al usuario

int menu(int & opcion);

/**
** Comienza el programa Principal
**/

int main(){
	tGestor gestor;
	int opcion;

	if (!arrancar (gestor, DOMINIO)){
		cout << "Se inician listas vacias" << endl;
		system("pause");
		system ("cls");
	}
	do{
		opcion = menu(opcion);
		system ("cls");
		switch (opcion){
			case 1: if (iniciarSesion (gestor)){ // Al iniciar sesion cargara el correo del usuario correspondiente, si el usuario no existe le devolvera un mensaje de "Usuario no existente"
						gestionarSesion (gestor);

					}
				break;
			case 2: if (crearCuenta (gestor)){ // Creará una cuenta nueva de usuario, si ni tiene una
						gestionarSesion(gestor);
					}
				break;
		}
	} while (opcion != 0); // si la opcion es 0; guardara en cada archivo .txt la informacion correspondiente a cada archivo para poderlo cargar la proxima vez
	apagar (gestor); // Guarda en los archivo .txt correspondientes y cierra el programa
	system ("pause");
	return 0;
}
/**
** Funcion que muestra por pantalla las opciones del menu
** Si la opcion pulsada por el usuario es mayor de 2, el programa vuelve a pedir la opcion hasta que sea correcta
**/

int menu (int & opcion){

	do {
		cout << " Selecciona una opcion: " << endl;
		cout << " 1.- Acceder a tu cuenta de correo " << endl;
		cout << " 2.- Crear una nueva cuenta de correo " << endl;
		cout << " 0.- Salir del programa " << endl;
		cout << " Opcion: ";
		cin >> opcion;
		cin.sync();
	} while (opcion < 0 || opcion > 2);

	return opcion;
}
