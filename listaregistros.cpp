#include<iostream>
#include<fstream>
#include<string>

using namespace std;

#include"listaregistros.h"

void inicializar (tListaRegistros & registros){
	registros.contador = 0;
}

void cargar (tListaRegistros & registros, ifstream & archivo){
	tRegistro registro;
	int elementos;
	inicializar (registros);
	archivo >> elementos;
	if (elementos != 0){
		for (int i = 0; i < elementos; i++){
			cargarRegistro(registro, archivo);
			insertar(registros, registro);
		}
	}
}

void guardar (const tListaRegistros & registros, ofstream & archivo){
	for (int i = 0; i < registros.contador; i++){
		archivo << registros.registros[i].idcorreo << " " << registros.registros[i].leido << endl;
	}
}

bool insertar (tListaRegistros & registros, tRegistro registro){
	bool esInsertar = false;
	if (registros.contador < MAX_REGS){
		int posicion =	buscar(registros, registro.idcorreo);
		if(posicion != -1){
			registros.registros[registros.contador] = registro;
			registros.contador++;
			esInsertar = true;
		}
	}
	return esInsertar;
}

bool borrar (tListaRegistros & registros, string id){
	bool esBorrar = false;
	int pos = buscar(registros, id);
	if (pos != -1){
		for (pos; pos < registros.contador; pos++){
			registros.registros[pos] = registros.registros[pos + 1];
		}
		registros.contador--;
		esBorrar = true;
	}
	return esBorrar;
}

bool correoLeido (tListaRegistros & registros, string id){
	bool esLeido = false;
	int pos = buscar(registros, id);	
	if (pos != -1){
		registros.registros[pos].leido = true;
		esLeido = true;
	}
	return esLeido;
}

int buscar (const tListaRegistros & registros, string id){
	int ini = 0, fin = registros.contador - 1, mitad, pos;
	bool encontrado = false;
	while ((ini <= fin) && !encontrado){
		mitad = (ini + fin) / 2;
		if(id < registros.registros[mitad].idcorreo){
			fin = mitad - 1;
		}
		else if(registros.registros[mitad].idcorreo < id){
			ini = mitad + 1;
		}
		else encontrado = true;
	}
	if (encontrado) pos = mitad;
	else pos = - 1;
	return encontrado;
}

void cargarRegistro (tRegistro & registro, ifstream & archivo){
	archivo >> registro.idcorreo;
	archivo >> registro.leido;
}
