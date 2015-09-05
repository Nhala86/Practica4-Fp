#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<sstream>
using namespace std;

#include"correo.h"



void correoNuevo(tCorreo & correo, string emisor){
	correo.fecha = time(0);
	correo.emisor = emisor;
	correo.identificador = correo.emisor + "_" + to_string(correo.fecha);
	destinatarioCorreo (correo.destinatario);
	asuntoCorreo (correo.asunto);
	contenidoCorreo (correo.contenido);
}

void contenidoCorreo (string & contenido){
	stringstream flujo;
	string linea;
	cout << "Escribe el mensaje (escribe XXX para terminar); " << endl;
	do{
		getline(cin, linea);
		if (linea != "XXX"){
			flujo << linea << endl;
		} 			
	}while (linea != "XXX");
	contenido = flujo.str();	
}

void asuntoCorreo (string & asunto){
	cout << "Escribe el asunto: ";
	getline (cin, asunto);
	cin.sync();
}

void destinatarioCorreo (string & destinatario){
	cout << "Introduce la direccion de mail del destinatario: ";
	cin >> destinatario;
	cin.sync();
}

void leerContenido (string & texto, ifstream & archivo){
	texto = "";
	string linea = "";
	getline(archivo, linea);
	while (linea != "X"){
		texto += linea + "\n";
		getline(archivo, linea);
	}
}

void correoContestacion(const tCorreo & correoOriginal, tCorreo & correo, string emisor){
	string contestacion;
	correo.fecha = time(0);
	correo.emisor = emisor;
	correo.identificador = correo.emisor + "_" + to_string (correo.fecha);
	correo.destinatario = correoOriginal.emisor;
	correo.asunto = "Re: " + correoOriginal.asunto;
	contenidoCorreo(contestacion);
	correo.contenido = contestacion;
	for (int i = 0; i < 80; i++){
		correo.contenido += "-";
	}
	correo.contenido += obtenerCabecera(correoOriginal);
	correo.contenido += correoOriginal.contenido;
}

string aCadena (const tCorreo & correo){
	return correo.contenido;
}

string obtenerCabecera(const tCorreo & correo){
	string informacion;
	informacion = "Correo de: " + correo.emisor + " ";
	informacion += mostrarFecha(correo.fecha) + "\n";
	informacion += "Para: " + correo.destinatario + "\n";
	informacion += "Asunto: " + correo.asunto + "\n" + "\n";
	
	return informacion;
}

bool cargar(tCorreo & correo, ifstream & archivo){
	bool esCargar = true;
	string contenido, fecha;
	archivo >> correo.identificador;
	if (correo.identificador != "XXX"){
		archivo >> correo.fecha;
		getline(archivo, fecha);
		getline(archivo, correo.emisor);
		getline(archivo, correo.destinatario);
		getline(archivo, correo.asunto);
		leerContenido(correo.contenido, archivo);
	}
	else{
		esCargar = false;
	}
	return esCargar;
}

void guardar(const tCorreo & correo, ofstream & archivo){
	archivo << correo.identificador << endl;
	archivo << correo.fecha << endl;
	archivo << correo.emisor << endl;
	archivo << correo.destinatario << endl;
	archivo << correo.asunto << endl;
	archivo << correo.contenido << endl;
	archivo << "X" << endl;	
}

string mostrarFecha(tFecha fecha){
	stringstream resultado;
	tm ltm;
	localtime_s(&ltm, &fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon <<"/"<< ltm.tm_mday;
	resultado<<" ("<<ltm.tm_hour<< ":" <<ltm.tm_min<< ":" << ltm.tm_sec << ")";
	return resultado.str();
}

string mostrarSoloDia(tFecha fecha){
	stringstream resultado;
	tm ltm;
	localtime_s(&ltm, &fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon <<"/"<< ltm.tm_mday;
	return resultado.str();
}

void mostrarCorreo (tCorreo correo){
	string fila, inicio;
	inicio = obtenerCabecera (correo);
	fila = aCadena (correo);	
	cout << inicio << fila << endl;
}

void eliminarRe (tCorreo & correo){
	string auxiliar = correo.asunto;
	if (auxiliar.substr(0,4) == "Re: "){
		auxiliar.erase (0,4);
		correo.asunto = auxiliar;
	}	
}

bool operator< (const tCorreo & correo1, const tCorreo & correo2){
	tCorreo auxMail1 = correo1;
	tCorreo auxMail2 = correo2;
	bool esOperator = true;
	eliminarRe (auxMail1);
	eliminarRe (auxMail2);
	if (auxMail2.asunto == auxMail1.asunto){
		if (auxMail2.fecha < auxMail1.fecha){
			esOperator = false;
		}
	}
	else if (auxMail2.asunto < auxMail1.asunto){
		esOperator = false;
	}
	return esOperator;
}
