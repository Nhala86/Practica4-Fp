#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;

#include"gestor.h"

bool arrancar (tGestor & gestor, string dominio){
	inicializar (gestor, DOMINIO);
	return (cargar(gestor.usuarios, dominio) && cargar (gestor.correos, dominio));
}

void apagar(const tGestor & gestor){
	system("cls");
	cout << "Cerrando gestor de correo " << gestor.dominio << endl;
	guardar (gestor.usuarios, gestor.dominio);
	guardar (gestor.correos, gestor.dominio);
}

bool crearCuenta(tGestor & gestor){
	tUsuario usuario;
	bool ok = false;
	int posicion;
	string id, contrasenia;
	cout << "Selecciona tu id: ";
	cin >> id;
	cin.sync();
	id = id + "@" + gestor.dominio;
	while(buscarUsuario (gestor.usuarios,id, posicion)){
		cout << "Id de usuario no disponible" << endl;
		cout << "Escoja otra Id: ";
		cin >> id;
		cin.sync();
		id = id + "@" + gestor.dominio;
	}
	cout << "Selecciona una contrasenia: ";
	cin >> contrasenia;
	cin.sync();
	inicializar (usuario, id, contrasenia);
	if (aniadir (gestor.usuarios, usuario)){
		ok = true;
		cout << "Se creo correctamente su cuenta" << endl;
	    cout << "Iniciando sesion en " << gestor.dominio << endl;
		buscarUsuario (gestor.usuarios, id, gestor.usuarioActivo);
	}
	else cout << "No se puede aniadir a la lista";	
	system("pause");
	return ok;
}

bool iniciarSesion (tGestor & gestor){
	system("cls");
	bool ok = false;
	int posicion;
	string id, contrasenia;
	cout << "Bienvenido a tu correo " << gestor.dominio << endl;
	cout << "Introduce tu direccion de correo: ";
	cin >> id;
	cin.sync();
	if (buscarUsuario (gestor.usuarios, id, posicion)){
		cout << "Introduce tu contrasenia: ";
		cin >> contrasenia;
		if (validarContrasenia (gestor.usuarios.usuario[posicion], contrasenia)){
			gestor.usuarioActivo = posicion;
			cout << "Iniciando sesion" << gestor.usuarios.usuario[posicion].nombre << endl;
			ok = true;
		}
		else cout << "No se pudo iniciar sesion" << endl;
	}
	else {
		cout << "Usuario no existente" << endl;
	}
	system("pause");
	system("cls");
	return ok;
}

void leerCorreo(tGestor & gestor, tListaRegistros & listaReg){
	tCorreo respuestaMail;
	string fila, cabecera;
	int correo, opcion, posicion;
	cout << "Cual correo deseas leer (escribe el numero del correo): ";
	cin >> correo;
	system("cls");
	if (correo > 0 && correo <= listaReg.contador){
		buscar (gestor.correos, listaReg.registros[correo-1].idcorreo, posicion);
		mostrarCorreo (gestor.correos.listaMail[posicion]);
		correoLeido (listaReg, listaReg.registros[correo-1].idcorreo);
		lineaDeSeparacion ();
		cout << "Selecciona una opcion:" << endl;
		cout << "   " << "1.- Contestar correo" << endl;
		cout << "   " << "0.- Volver a la bandeja" << endl;
		lineaDeSeparacion ();
		do{
		cout << "Opcion: ";
		cin >> opcion;

			if (opcion == 1){
				correoContestacion (gestor.correos.listaMail[posicion], respuestaMail, gestor.correos.listaMail[posicion].destinatario);
				enviarCorreo (gestor, respuestaMail);
			}
		}while (opcion != 0 && opcion > 1 && opcion < 0);
	}
}

void enviarCorreo (tGestor & gestor, const tCorreo & correo){
	tRegistro registro;
	int posicion;

	if (buscarUsuario (gestor.usuarios, correo.destinatario, posicion)){
			registro.idcorreo = correo.identificador;
			registro.leido = true;
		if (insertar (gestor.usuarios.usuario[gestor.usuarioActivo].enviados, registro)){
			registro.leido = false;
			if (insertar (gestor.usuarios.usuario[posicion].recibidos, registro)){
					if (insertar(gestor.correos, correo)){
						cout << "Correo enviado" << endl;
					}
					else {
					cout << "ERROR: La lista de correos no admite nuevos correos" << endl;
				}
			}
			else {
				cout << "ERROR: La bandeja del destinatario esta llena" << endl;
			}
		}
		else{
			cout << "ERROR: la bandeja del emisor esta llena" << endl;
		}
	}
	else{
		cout << "ERROR: Destinatario no existe" << endl;
	}
}

void borrarCorreo(tGestor & gestor, tListaRegistros & listaReg){
	int opcion;
	string id;
	int contador = 0;
	bool ok = false;
	
	cout << "Selecciona el numero del correo que deseas borrar: ";
	cin >> opcion;	
	if (opcion > 0 && opcion <= listaReg.contador){
		id = listaReg.registros[opcion - 1].idcorreo;
		if (borrar (listaReg, id)){
			cout << "El mensaje se ha eliminado correctamente" << endl;	
			while(contador < gestor.usuarios.contador && !ok){
				if((buscar(gestor.usuarios.usuario[contador].recibidos, id) != - 1) || (buscar(gestor.usuarios.usuario[contador].enviados, id) != - 1)){
					ok = true;
				}
				contador++;
			}
			if(!ok && borrar(gestor.correos, id)){
				cout << "Se ha borrado el mensaje de la base de datos" << endl;
			}
		}		
	}
	else{
		cout << "El correo seleccionado no existe" << endl;
	}
	system("pause");
}

void lecturaRapida(tGestor & gestor, tListaRegistros & listaReg){
	system("cls");
	int posicion;
	tListaCorreos aux;
	aux = gestor.correos;
	ordenar_AF (aux);
	for (int i = 0; i < listaReg.contador; i++){
		if (!listaReg.registros[i].leido){
			buscar (aux, listaReg.registros[i].idcorreo, posicion);
			mostrarCorreo (aux.listaMail[posicion]);
			lineaDeSeparacion ();
			listaReg.registros[i].leido = true;
		}
	}
	system("pause");
}

void inicializar (tGestor & gestor, string dominio){
	gestor.dominio = dominio;
}

void gestionarSesion(tGestor & gestor){
	tCorreo nuevoCorreo;
	bool esEntrada = true;
	int opcion;
	do{
		mostrarInterFazUsuario(gestor,esEntrada);
		cin >> opcion;
		if (opcion == 1){
			if (!esEntrada){
				leerCorreo (gestor, gestor.usuarios.usuario[gestor.usuarioActivo].enviados);
			}
			else{
				leerCorreo (gestor, gestor.usuarios.usuario[gestor.usuarioActivo].recibidos);
			}
		}
		else if (opcion == 2){
			system("cls");
			correoNuevo (nuevoCorreo, gestor.usuarios.usuario[gestor.usuarioActivo].nombre);
			enviarCorreo(gestor, nuevoCorreo);
			system ("pause");
		}
		else if (opcion == 3){
			if(!esEntrada){
				borrarCorreo (gestor, gestor.usuarios.usuario[gestor.usuarioActivo].enviados);
			}
			else{
				borrarCorreo (gestor, gestor.usuarios.usuario[gestor.usuarioActivo].recibidos);
			}
		}
		else if (opcion == 4){
			esEntrada = !esEntrada;
		}
		else if (opcion == 5){
			lecturaRapida (gestor, gestor.usuarios.usuario[gestor.usuarioActivo].recibidos);
		}
	} while (opcion != 0);
	system ("cls");
}

void mostrarInterFazUsuario (tGestor & gestor, bool esEntrada){
	system ("cls");
	cout << "Sesion de  " << gestor.usuarios.usuario[gestor.usuarioActivo].nombre << endl;
	for(int i = 0; i < 30; i++){
		cout << "-";
	}
	cout << "Bandeja de ";
	if (esEntrada){
		cout << "entrada";
		lineasDeCabecera ();
	}
	else{
		cout << "salida-";
		lineasDeCabecera ();
	}
	lineaDeSeparacion ();
	if (!esEntrada){
		cout << "L" << setw(2) << "N" << setw(15) << "DESTINATARIO" << setw(25) << "ASUNTO" << setw(30) << "FECHA" << endl;
	}
	else cout << "L" << setw(2) << "N" << setw(10) << "EMISOR" << setw(30) << "ASUNTO" << setw(30) << "FECHA" << endl;
	lineaDeSeparacion ();
	verBandeja (gestor,esEntrada);
	lineaDeSeparacion ();
	mostrarMenu(esEntrada);
}

void verBandeja (const tGestor & gestor, bool esEntrada){
	int posicion;
	tUsuario usuario = gestor.usuarios.usuario[gestor.usuarioActivo];
	if (!esEntrada){
		for (int i = 0; i < usuario.enviados.contador; i++){
			if (buscar (gestor.correos, usuario.enviados.registros[i].idcorreo, posicion)){
				cout << " " << setw(2) << i + 1 << " " << gestor.correos.listaMail[posicion].destinatario << setw(25) << gestor.correos.listaMail[posicion].asunto << setw(30) << mostrarSoloDia (gestor.correos.listaMail[posicion].fecha) << endl;
			}
		}
	}
	else{
		for (int i = 0; i < usuario.recibidos.contador; i++){
			if (!usuario.recibidos.registros[i].leido){
				cout << "*";
			}
			else {
				cout << " ";
			}
			if (buscar (gestor.correos, usuario.recibidos.registros[i].idcorreo, posicion)){
				cout << setw(2) << i + 1 << " " << gestor.correos.listaMail[posicion].emisor << setw(25) << gestor.correos.listaMail[posicion].asunto << setw(30) << mostrarSoloDia (gestor.correos.listaMail[posicion].fecha) << endl;
			}
		}
	}
}

void mostrarMenu (bool esEntrada){
	cout << endl;
	cout << "Selecciona una opcion: " << endl;
	cout << "" << endl;
	cout << "1.- Leer correo" << endl;
	cout << "2.- Enviar correo" << endl;
	cout << "3.- Eliminar correo" << endl;
	cout << "4.- Ver bandeja de ";
	if (esEntrada) cout << "salida" << endl;
	else cout << "entrada" << endl;
	cout << "5.- Lectura rapida de correos no leidos" << endl;
	cout << "0.- Cerrar Sesion Activa" << endl;
	lineaDeSeparacion ();
	cout << "Opcion: ";
}

void lineaDeSeparacion (){
	for (int i = 0; i < 80; i++){
		cout << "-";
	}
}

void lineasDeCabecera (){
	for(int i = 0; i < 32; i++){
		cout << "-";
	}
}
