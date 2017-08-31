#include <iostream>
#include "poligono.h"
#include "poligono.hpp"
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

poligono cargarPoligono(string val, list<poligono> &poligonosMemoria);
string* tokenizador(string val);
void listapoligonos(list<poligono> &poligonosMemoria);
void descargarmemoria(list<poligono> &poligonosMemoria, string nombre_objeto);
bool buscarPoligono(list<poligono> listIn, string nombreIn);
bool guardarPoligono(string nombreObjeto, string nombreArchivo, list<poligono> listIn);
poligono buscarPoligono2(list<poligono> listIn, string nombreIn);


int main()
{
	int on = 1;
	list<poligono> poligonosMemoria;
	list<poligono>::iterator itLPoli;
	poligono cargado;
	string lineIn,lineIn2, obj;
	bool encontrado=false;
	while(on)
	{
		int eleccion = 0;
		cout << "=======Componente 1=======" << endl;
		cout << "1. Cargar poligono a memoria" << endl;
		cout << "2. Listar poligonos en memoria" << endl;
		cout << "3. Envolver objeto" << endl;
		cout << "4. Envolver objetos en memoria" << endl;
		cout << "5. Descargar memoria" << endl;
		cout << "6. Guardar objetos" << endl;
		cout << "7. Terminar programa" << endl;
		cout << "======= Ingrese su eleccion: ";
		cin>>eleccion;
		switch(eleccion)
		{
		case 1:
			encontrado = false;
			cout << "Ingrese nombre de archivo: ";
			cin>>lineIn;
			cargado.inicializarPoligono();
			cargado=cargarPoligono(lineIn, poligonosMemoria);
			if(cargado.getNombre()=="0a")
			{
				cout<<"No se cargó ningun poligono"<<endl;
			}
			else if(cargado.getNombre()!="0a" && !poligonosMemoria.empty())
			{
				for(itLPoli=poligonosMemoria.begin(); itLPoli!=poligonosMemoria.end(); itLPoli++)
				{
					if(cargado.getNombre()==itLPoli->getNombre())
					{
						encontrado = true;
					}
				}
			}
			if(encontrado)
				cout<<"Este poligono ya ha sido cargado anteriormente"<<endl;
			else if(!encontrado)
			{
				poligonosMemoria.push_front(cargado);
				cout<<"Poligono cargado correctamente"<<endl;
			}
			break;
		case 2:
			listapoligonos(poligonosMemoria);
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			cout << "Ingrese nombre del objeto a descargar: ";
			cin>>obj;
			descargarmemoria(poligonosMemoria,obj);
			break;
		case 6:
			cout << "ingrese nombre del objeto" << endl;
			cin>>lineIn;
			cout << "ingrese nombre de archivo donde desea guardarlo" << endl;
			cin>>lineIn2;
			guardarPoligono(lineIn, lineIn2, poligonosMemoria);
			break;
		case 7:
			on = 0;
			break;
		}
	}
	return 0;
}
poligono cargarPoligono(string val, list<poligono> &poligonosMemoria)
{
	poligono pOut;
	pOut.inicializarPoligono();
	string* str;
	string line;
	ifstream myfile(val.c_str());
	vertice vAux;
	cara cAux;
	int countE = 0;
	int countE2 = 0;
	if (myfile.is_open())
	{
		getline (myfile,line);
		cout<<"nombre: "<< line<<endl;
		pOut.setNombre(line);
		getline (myfile,line);
		cout<<"cantidad de vertices: "<< line<<endl;
		pOut.setCantidadVertices(atoi(line.c_str()));
		bool terminado = false;
		while (getline (myfile,line))
		{
			string strAcumX;
			string strAcumY;
			string strAcumZ;
			if(line[0] == '-'&& line[1] == '1' && line.size() == 2){
				cout<<"-1 encontrado!"<<endl;
				break;
			}
			cout<<"linea antes de tokenizar: "<< line<<endl;
			strAcumX += line[0];
			for(int i = 0; i < line.size(); i++){
				if(line[i+1] == ' '){
					vAux.x = atoi(strAcumX.c_str());
					cout<<"x1: "<< strAcumX<<endl;
					strAcumY += line[i+2];
					for(int j = i+2; j <line.size(); j++){
						if(line[j+1] == ' '){
							vAux.y = atoi(strAcumY.c_str());
							cout<<"y1: "<< strAcumY<<endl;
							strAcumZ += line[j+2];
							for(int k = j+2; k <line.size(); k++){
								if(line[k+1] == NULL || line[k+1] == ' '){
									countE++;
									vAux.z = atoi(strAcumZ.c_str());
									cout<<"Z1: "<< strAcumZ<<endl;
									pOut.insertarVertice(vAux);
									if(line[k+1] == NULL){
										terminado = true;
										break;
									}
									i = k;
									strAcumX.clear();
									strAcumY.clear();
									strAcumZ.clear();
									break;
								}else
									strAcumZ += line[k+1];
							}
								break;
						}else
							strAcumY += line[j+1];
					}
					if(terminado)
						break;
			}
				else
					strAcumX += line[i+1];
			}
			if(countE == pOut.getCantidadVertices())
				break;
		}
		while (getline (myfile,line))
		{
			string strAcumX2;
			string strAcumY2;
			string strAcumZ2;
			if(line[0] == '-'&& line[1] == '1' && line.size() == 2){
				cout<<"-1 encontrado!"<<endl;
				break;
			}
			string cara;
			int contCara = 0;
			for(int i = 0; i < line.size(); i++){
				cara+= line[i];
				contCara ++;
				if(line[i+1]== ' ')
					break;
			}
			cAux.tamanoCara = atoi(cara.c_str());
			cout<<"linea2 antes de tokenizar: "<< line<<endl;
			cout<< "tamanio cara: "<< cAux.tamanoCara<<endl;
			strAcumX2 += line[contCara];
			for(int i = 1; i <=line.size(); i++){
				if(line[i+1] == ' '){
					cAux.jEsimoV.x = atoi(strAcumX2.c_str());
					cout<<"x2: "<< strAcumX2<<endl;
					strAcumY2 += line[i+2];
					for(int j = i+2; j <=line.size(); j++){
						if(line[j+1] == ' '){
							cAux.jEsimoV.y = atoi(strAcumY2.c_str());
							cout<<"y2: "<< strAcumY2<<endl;
							strAcumZ2 += line[j+2];
							for(int k = j+2; k <=line.size(); k++){
								if(line[k+1] == NULL || line[k+1] == ' ' ){
									cAux.jEsimoV.z = atoi(strAcumZ2.c_str());
									cout<<"z2: "<< strAcumZ2<<endl;
									pOut.insertarCara(cAux);
									break;
								}else
									strAcumZ2 += line[k+1];
							}
							break;
						}else
							strAcumY2 += line[j+1];
					}
					break;
				}else
					strAcumX2 += line[i+1];
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";
	return pOut;
}
bool buscarPoligono(list<poligono> listIn, string nombreIn){
for(list<poligono>::iterator buscaItera = listIn.begin(); buscaItera != listIn.end();buscaItera++)
	if((*buscaItera).getNombre() == nombreIn)
		return true;

	return false;
}
poligono buscarPoligono2(list<poligono> listIn, string nombreIn){
	poligono aux;
	aux.inicializarPoligono();
	for(list<poligono>::iterator buscaItera = listIn.begin(); buscaItera != listIn.end();buscaItera++)
		if((*buscaItera).getNombre() == nombreIn)
			return (*buscaItera);
	return aux;
}
bool guardarPoligono(string nombreObjeto, string nombreArchivo, list<poligono> listIn){
	poligono pAux;
	list<vertice> listaVAux;
	list<cara> listaCAux;
	if(buscarPoligono(listIn, nombreObjeto)){
		pAux = buscarPoligono2(listIn, nombreObjeto);
		ofstream myfile;
		myfile.open (nombreArchivo.c_str());
		myfile << pAux.getNombre()<<"\n";
		myfile << pAux.getCantidadVertices()<<"\n";
		listaVAux = pAux.getListaVertices();
		listaCAux = pAux.getlistaCaras();
		for(list<vertice>::iterator buscaIteraV = listaVAux.begin(); buscaIteraV != listaVAux.end();buscaIteraV++)
			myfile <<(*buscaIteraV).x<<" " <<(*buscaIteraV).y<<" " <<(*buscaIteraV).z<<"\n";
		for(list<cara>::iterator buscaIteraC = listaCAux.begin(); buscaIteraC != listaCAux.end();buscaIteraC++)
			myfile <<(*buscaIteraC).tamanoCara<<" " <<(*buscaIteraC).jEsimoV.x<<" " <<(*buscaIteraC).jEsimoV.y<<" "<<(*buscaIteraC).jEsimoV.z<<"\n";
		myfile <<"-1"<<"\n";
		myfile.close();
		return true;
	}
	else{
		cout<<"No se encontro el nombre en memoria"<<endl;
		return false;
	}
}
void listapoligonos(list<poligono> &poligonosMemoria)
{
	list<poligono>::iterator itPoli;
	if(poligonosMemoria.size()==0){
		cout<<"No hay objetos cargados en memoria\n";
		return;
	}
	cout<<"=======Listado de poligonos======="<<endl;
	for(itPoli=poligonosMemoria.begin(); itPoli!=poligonosMemoria.end(); itPoli++)
	{
		cout<<"Nombre: "<<itPoli->getNombre()<<" Cantidad de vertices: "<<itPoli->getCantidadVertices()<<" Cantidad de caras: "<<itPoli->getCantidadCaras()<<endl;
		/*<<" Cantidad de aristas: "<<itPoli->getCantidadAristas() TODO: imprimir cantidad de aristas*/
	}
	cout<<"=================================="<<endl;
}
void descargarmemoria(list<poligono> &poligonosMemoria, string nombre_objeto)
{
	list<poligono>::iterator itPoli;
	bool borrado = false;
	for(itPoli=poligonosMemoria.begin(); itPoli!=poligonosMemoria.end(); itPoli++)
	{
		if(nombre_objeto==itPoli->getNombre())
		{
			poligonosMemoria.erase(itPoli);
			borrado = true;
		}
	}
	if(borrado)
		cout<<"El objeto fue descargado exitosamente."<<endl;
	else
		cout<<"El objeto no fue encontrado para su descarga."<<endl;
}
