#include<iostream>
#include<fstream>
#include<string>

using namespace std;

#include"listacorreos.h"


void inicializar(tListaCorreos & correos){
	correos.contador = 0;
}

bool cargar(tListaCorreos & correos, string dominio){
	bool esCargar;
	ifstream archivo;
	inicializar(correos);
	string ficheroCorreo = dominio + "_" + mailCorreo;
	archivo.open(ficheroCorreo);
	if (archivo.is_open()){
		tCorreo correo;
		while (cargar (correo, archivo)){
			insertar(correos, correo);
		}
		archivo.close();
		esCargar = true;
	}
	else{
		cout << "No se ha podido cargar el archivo";
		esCargar = false;
	}
	return esCargar;
}

void guardar (const tListaCorreos & correos, string dominio){
	ofstream archivo;
	string ficheroCorreo = dominio + "_" + mailCorreo;
	archivo.open(ficheroCorreo);
	if (archivo.is_open()){
		for(int i = 0; i < correos.contador; i++){
			guardar(correos.listaMail[i], archivo);
		}
		archivo << "XXX" << endl;
		archivo.close();
	}
	else{
		cout << "No sé puedo guardar el archivo";
	}
}

bool insertar(tListaCorreos & correos, const tCorreo & correo){
	bool esInsertado = false;
	if (correos.contador < MAX_CORREOS){
		correos.listaMail[correos.contador] = correo;
		correos.contador++;
		esInsertado = true;
	}
	return esInsertado;
}

bool borrar(tListaCorreos &correos, string id){
	bool borrado = false;
	int posicion;
	buscar(correos, id , posicion);
	if(posicion != -1){	//Si existe se proce a borrar el registro de la lista
				for (posicion; posicion < correos.contador; posicion++){
			correos.listaMail[posicion] = correos.listaMail[posicion + 1]; //Se desplazan los registros desde esa posicion a la derecha
		}
		correos.contador--;
		borrado = true;
	}
return borrado;
}


bool buscar (const tListaCorreos & correos, string id, int & pos){
	int ini = 0, fin = correos.contador - 1, mitad;
	bool encontrado = false;
	while ((ini <= fin) && !encontrado){
		mitad = (ini + fin) / 2;
		if(id < correos.listaMail[mitad].identificador){
			fin = mitad - 1;
		}
		else if(correos.listaMail[mitad].identificador < id){
			ini = mitad + 1;
		}
		else
			encontrado = true;
	}
	if (encontrado) pos = mitad;
	else pos = ini;
	return encontrado;
}

void ordenar_AF(tListaCorreos & correos){
	int i = 0;
	bool esOrdenar = false;
	while ((i < correos.contador) && esOrdenar){
		esOrdenar = false;
		for (int j = correos.contador - 1; j > i; j--){
			if (correos.listaMail[j] < correos.listaMail[j - 1]){
				tCorreo tmp;
				tmp = correos.listaMail[j];
				correos.listaMail[j] = correos.listaMail[j - 1];
				correos.listaMail[j - 1] = tmp;
				esOrdenar = true;
			}
		}
		if (esOrdenar) i++;
	}
}
