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
	int pos;
	if(usuarios.contador < MAX_USUARIOS){		
		buscarUsuario(usuarios, usuario.nombre, pos);
		for(int i = usuarios.contador; i> pos; i--)
			usuarios.usuario[i] = usuarios.usuario[i -1];
		usuarios.usuario[pos] = usuario;
		usuarios.contador++;
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
