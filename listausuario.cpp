#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#include"listausuario.h"

void inicializar (tListaUsuarios & usuarios){
	usuarios.contador = 0;
}

bool cargar (tListaUsuarios & usuarios, string dominio){
	bool ok = false;
	ifstream archivo;
	inicializar(usuarios);
	string nombreFichero = dominio + "_" + listaUsuarios;
	archivo.open(nombreFichero);
	if (archivo.is_open()){
		tUsuario usuario;
		while (cargar(usuario, archivo)){
			if(aniadir (usuarios, usuario)){
				ok = true;
			}
			/*else{
				cout << "Lista de usuarios llena. No se pueden registrar mas usuarios" << endl;
			}*/
		}
		
	}
	else{
		cout << "No se ha podido cargar el archivo de usuarios" << endl;
	}
	archivo.close();
	return ok;
}

void guardar (const tListaUsuarios & usuarios, string dominio){
	ofstream archivo;
	string nombreFichero = dominio + "_" + listaUsuarios;
	archivo.open(nombreFichero);
	if (archivo.is_open()){
//				cout << usuarios.contador;system("pause");
		for(int i = 0; i < usuarios.contador; i++){
			guardar(usuarios.usuario[i], archivo);
		}
		archivo << "XXX";
		archivo.close();
	}
	else{
		cout << " No se puede guardar el archivo";
	}
}

bool aniadir (tListaUsuarios & usuarios, const tUsuario & usuario){
	bool esAniadir = false;
	if(usuarios.contador < MAX_USUARIOS){
		usuarios.usuario[usuarios.contador] = usuario;
		usuarios.contador++;
		ordenar (usuarios);
		esAniadir = true;
	}
	return esAniadir;
}

bool buscarUsuario (const tListaUsuarios & usuarios, string id, int & posicion){
	int ini = 0, fin = usuarios.contador - 1, mitad;
	bool encontrado = false;
	while ((ini <= fin) && !encontrado){
		mitad = (ini + fin) / 2;
		if(id < usuarios.usuario[mitad].nombre){
			fin = mitad - 1;
		}
		else if(usuarios.usuario[mitad].nombre < id){
			ini = mitad + 1;
		}
		else
			encontrado = true;
	}
	if (encontrado) posicion = mitad;
	else posicion = ini;
	return encontrado;
}

void ordenar (tListaUsuarios & usuarios){
	tUsuario nuevo;
	int posicion = 0;
	nuevo = usuarios.usuario[usuarios.contador - 1];
	while ((posicion < usuarios.contador -1) && !(usuarios.usuario[posicion].nombre > nuevo.nombre)){
		posicion ++;
	}
	for (int j = usuarios.contador - 1; j > posicion; j--){
		usuarios.usuario[j] = usuarios.usuario[j - 1];
	}
	usuarios.usuario[posicion] = nuevo;
}
