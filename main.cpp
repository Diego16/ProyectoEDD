#include <iostream>
#include "poligono.h"
#include "poligono.hpp"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cmath>
using namespace std;

poligono cargarPoligono(string val, list<poligono> &poligonosMemoria);
string* tokenizador(string val);
void listapoligonos(list<poligono> &poligonosMemoria);
void descargarmemoria(list<poligono> &poligonosMemoria, string nombre_objeto);
bool buscarPoligono(list<poligono> listIn, string nombreIn);
bool guardarPoligono(string nombreObjeto, string nombreArchivo, list<poligono> listIn);
poligono buscarPoligono2(list<poligono> listIn, string nombreIn);
poligono envolvente(string nombreObjeto, list<poligono> listIn);


int main()
{
	bool on = true;
	list<poligono> poligonosMemoria;
	list<poligono> envolventes;
	list<poligono>::iterator itLPoli;
	poligono cargado;
	char* code;
	char* file;
	string lineIn,lineIn2, obj, com;
	bool encontrado=false;
	while(on)
	{
		cout<<endl<<"Ingrese el comando"<<endl<<"$";
		getline(cin,com);
		char* cadena=strdup(com.c_str());
		file=strtok(cadena," ");
		code=file;
		file=strtok(nullptr," ");
		//cout<<"============"<<file<<"+++++++++"<<code<<endl;
		cout<<"=========="<<poligonosMemoria.size()<<endl;
		if(strcmp(code,"cargar")==0)
		{
			string lineIn=file;
			encontrado = false;
			cargado.inicializarPoligono();
			cargado=cargarPoligono(lineIn, poligonosMemoria);
			if(cargado.getNombre()=="0a")
			{
				cout<<"No se cargó ningun poligono"<<endl;
			}
			else if(cargado.getNombre()!="0a" && !poligonosMemoria.empty())
			{
				encontrado = buscarPoligono(poligonosMemoria,cargado.getNombre());
			}
			if(encontrado)
				cout<<"Este poligono ya ha sido cargado anteriormente"<<endl;
			else if(!encontrado)
			{
				poligonosMemoria.push_front(cargado);
				cout<<"Poligono cargado correctamente"<<endl;
			}
		}
		if(strcmp(code,"listado")==0)
			cout<<"=========="<<poligonosMemoria.size()<<endl;
			listapoligonos(poligonosMemoria);
		if(strcmp(code,"envolvente")==0)
			envolventes.push_front(envolvente(lineIn, poligonosMemoria));
		if(strcmp(code,"descargar")==0)
			descargarmemoria(poligonosMemoria,lineIn);
		if(strcmp(code,"guardar")==0)
			guardarPoligono(lineIn, lineIn2, poligonosMemoria);
		if (strcmp(code,"ayuda")==0){
			if(file==nullptr){
				cout<<endl<<"Comandos disponibles: "<<endl<<"   cargar"<<endl<<"   listado"<<endl<<"   envolvente"<<endl<<"   descargar"<<endl<<"   guardar"<<"   v_cercanos"<<endl<<"   salir"<<endl;
			}
			else{
				if(strcmp(file,"")==0)
					cout<<""<<endl;
				if(strcmp(file,"")==0)
					cout<<""<<endl;
				if(strcmp(file,"")==0)
					cout<<""<<endl;
				if(strcmp(file,"salir")==0)
					cout<<"Termina la ejecucion de la aplicacion."<<endl;
			}
		}
		if(strcmp(code,"salir")==0)
			on = false;
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
		cout<<"Nombre: "<< line<<endl;
		pOut.setNombre(line);
		getline (myfile,line);
		cout<<"Cantidad de vertices: "<< line<<endl;
		pOut.setCantidadVertices(atoi(line.c_str()));
		bool terminado = false;
		while (getline (myfile,line))
		{
			string strAcumX;
			string strAcumY;
			string strAcumZ;
			if(line[0] == '-'&& line[1] == '1' && line.size() == 2)
			{
				break;
			}
			strAcumX += line[0];
			for(int i = 0; i < line.size(); i++)
			{
				if(line[i+1] == ' ')
				{
					vAux.x = stof(strAcumX.c_str());
					strAcumY += line[i+2];
					for(int j = i+2; j <line.size(); j++)
					{
						if(line[j+1] == ' '){
							vAux.y = stof(strAcumY.c_str());
							strAcumZ += line[j+2];
							for(int k = j+2; k <line.size(); k++)
							{
								if(line[k+1] == ' ')
								{
									countE++;
									vAux.z = stof(strAcumZ.c_str());
									pOut.insertarVertice(vAux);
									if(line[k+1] == ' ')
									{
										terminado = true;
										break;
									}
									i = k;
									strAcumX.clear();
									strAcumY.clear();
									strAcumZ.clear();
									break;
								}
								else
									strAcumZ += line[k+1];
							}
							break;
						}
						else
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
			if(line[0] == '-'&& line[1] == '1' && line.size() == 2)
			{
				break;
			}
			string cara;
			int contCara = 0;
			for(int i = 0; i < line.size(); i++)
			{
				cara+= line[i];
				contCara ++;
				if(line[i+1]== ' ')
					break;
			}
			cAux.tamanoCara = atoi(cara.c_str());
			strAcumX2 += line[contCara];
			for(int i = 1; i <=line.size(); i++)
			{
				if(line[i+1] == ' ')
				{
					cAux.jEsimoV.x = atoi(strAcumX2.c_str());
					strAcumY2 += line[i+2];
					for(int j = i+2; j <=line.size(); j++){
						if(line[j+1] == ' ')
						{
							cAux.jEsimoV.y = atoi(strAcumY2.c_str());
							strAcumZ2 += line[j+2];
							for(int k = j+2; k <=line.size(); k++){
								if(line[k+1] == ' ' )
								{
									cAux.jEsimoV.z = atoi(strAcumZ2.c_str());
									pOut.insertarCara(cAux);
									break;
								}
								else
									strAcumZ2 += line[k+1];
							}
							break;
						}
						else
							strAcumY2 += line[j+1];
					}
					break;
				}
				else
					strAcumX2 += line[i+1];
			}
		}
		myfile.close();
	}
	else cout << "No se pudo abrir el archivo"<<endl;
	return pOut;
}
bool buscarPoligono(list<poligono> listIn, string nombreIn)
{
	for(list<poligono>::iterator buscaItera = listIn.begin(); buscaItera != listIn.end();buscaItera++){
		if((*buscaItera).getNombre() == nombreIn)
			return true;
	}
	return false;
}
poligono buscarPoligono2(list<poligono> listIn, string nombreIn)
{
	poligono aux;
	aux.inicializarPoligono();
	for(list<poligono>::iterator buscaItera = listIn.begin(); buscaItera != listIn.end();buscaItera++){
		if((*buscaItera).getNombre() == nombreIn)
			return (*buscaItera);
	}
	return aux;
}
bool guardarPoligono(string nombreObjeto, string nombreArchivo, list<poligono> listIn)
{
	poligono pAux;
	list<vertice> listaVAux;
	list<cara> listaCAux;
	if(buscarPoligono(listIn, nombreObjeto))
	{
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
		cout<<"No se encontro el objeto en memoria"<<endl;
		return false;
	}
}
void listapoligonos(list<poligono> &poligonosMemoria)
{
	list<poligono>::iterator itPoli;
	cout<<"=========="<<poligonosMemoria.size()<<endl;
	if(poligonosMemoria.size()<=0)
	{
		cout<<"No hay objetos cargados en memoria\n";
		return;
	}
	else
	{
		cout<<"Hay "<<poligonosMemoria.size()<<" objetos en memoria."<<endl;
		cout<<"=======Listado de poligonos======="<<endl;
		for(itPoli=poligonosMemoria.begin(); itPoli!=poligonosMemoria.end(); itPoli++)
		{
			cout<<"Nombre: "<<itPoli->getNombre()<<" Cantidad de vertices: "<<itPoli->getCantidadVertices()<<" Cantidad de caras: "<<itPoli->getCantidadCaras()<<endl;
					/*<<" Cantidad de aristas: "<<itPoli->getCantidadAristas() TODO: imprimir cantidad de aristas*/
		}
		cout<<"=================================="<<endl;
	}
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
poligono envolvente(string nombreObjeto, list<poligono> listIn)
{
	poligono pObj,pAux;
	vertice auxmax={0,0,0}, auxmin={10000,10000,10000},aux;
	list<vertice> listaVAux;
	list<vertice>::iterator itVert;
	list<cara> listaCAux;
	list<cara>::iterator itCara;
	cara careishon;

	if(buscarPoligono(listIn, nombreObjeto))
	{
		pObj = buscarPoligono2(listIn, nombreObjeto);
		for(itVert=pObj.getListaVertices().begin();itVert!=pObj.getListaVertices().end();itVert++)
		{
			if(itVert->x>auxmax.x)
				auxmax.x=itVert->x;
			if(itVert->y>auxmax.y)
				auxmax.y=itVert->y;
			if(itVert->z>auxmax.z)
				auxmax.z=itVert->z;
			if(itVert->x<auxmin.x)
				auxmin.x=itVert->x;
			if(itVert->y<auxmin.y)
				auxmin.y=itVert->y;
			if(itVert->z<auxmin.z)
				auxmin.z=itVert->z;
		}
		listaVAux.push_front(auxmax);
		aux.x=auxmax.x;
		aux.y=auxmin.y;
		aux.z=auxmax.z;
		listaVAux.push_front(aux);
		aux.x=auxmax.x;
		aux.y=auxmin.y;
		aux.z=auxmin.z;
		listaVAux.push_front(aux);
		aux.x=auxmax.x;
		aux.y=auxmax.y;
		aux.z=auxmin.z;
		listaVAux.push_front(aux);
		aux.x=auxmin.x;
		aux.y=auxmax.y;
		aux.z=auxmax.z;
		listaVAux.push_front(aux);
		aux.x=auxmin.x;
		aux.y=auxmax.y;
		aux.z=auxmin.z;
		listaVAux.push_front(aux);
		aux.x=auxmin.x;
		aux.y=auxmin.y;
		aux.z=auxmax.z;
		listaVAux.push_front(aux);
		listaVAux.push_front(auxmin);

		careishon.tamanoCara = abs(auxmax.x - auxmin.x)* abs(auxmax.y - auxmin.y);
		careishon.jEsimoV = auxmin;
		listaCAux.push_front(careishon);
		careishon.jEsimoV = auxmax;
		listaCAux.push_front(careishon);

		careishon.tamanoCara = abs(auxmax.y - auxmin.y)* abs(auxmax.z - auxmin.z);
		careishon.jEsimoV = auxmin;
		listaCAux.push_front(careishon);
		careishon.jEsimoV = auxmax;
		listaCAux.push_front(careishon);

		careishon.tamanoCara = abs(auxmax.x - auxmin.x)* abs(auxmax.z - auxmin.z);
		careishon.jEsimoV = auxmin;
		listaCAux.push_front(careishon);
		careishon.jEsimoV = auxmax;
		listaCAux.push_front(careishon);


		pAux.setListaVertices(listaVAux);
		pAux.setCantidadVertices(8);
		pAux.setlistaCaras(listaCAux);

	}
	else
		cout<<"No se encontro el objeto en memoria"<<endl;
	return pAux;
}