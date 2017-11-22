#include <iostream>
#include "poligono.h"
#include "poligono.hpp"
#include "BinaryTree.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <cstring>
using namespace std;

poligono cargarPoligono(string val, list<poligono> &poligonosMemoria);
string* tokenizador(string val);
void listapoligonos(list<poligono> &poligonosMemoria);
bool descargarmemoria(list<poligono> &poligonosMemoria, string nombre_objeto);
bool buscarPoligono(list<poligono> listIn, string nombreIn);
bool guardarPoligono(string nombreObjeto, string nombreArchivo, list<poligono> listIn);
poligono buscarPoligono2(list<poligono> listIn, string nombreIn);
poligono envolvente(string nombreObjeto, list<poligono> listIn);
float* componente2Punto1(string nombrePoligono, list<poligono> poligonosMemoria, float x, float y, float z, bool on, int imp);
void componente2Punto2(list<poligono> poligonosMemoria, float x, float y, float z);
void componente2Punto3(string nombrePoligono,list<poligono> poligonosMemoria);
float* calcularDistancia( float x, float y, float z, float x2, float y2, float z2);


int main()
{
	bool on = true;
	list<poligono> poligonosMemoria;
	list<poligono> envolventes;
	list<poligono>::iterator itLPoli;
	poligono cargado;
	bool encontrado=false;
	string lineIn, lineIn2;
	while(on)
	{
		cout<<"$ ";
		char comando[300];
		cin.getline(comando,300);
		char * pch;
		list<char*> milista;
		pch = strtok (comando," ");
		while (pch != NULL)
		{
			milista.push_back(pch);
			pch = strtok (NULL, " ");
		}
		list<char*>::iterator it=milista.begin();
		string comando1=*it;
		if (comando1=="cargar")
		{
			if (milista.size()==2)
			{
				it++;
				lineIn=*it;
				cargado.inicializarPoligono();
				cargado=cargarPoligono(lineIn, poligonosMemoria);
				if(cargado.getNombre()=="0a")
				{
					cout<<"~No se cargó ningun poligono"<<endl;
				}
				else if(cargado.getNombre()=="wrongfile")
				{
					cout <<"~El archivo "<<lineIn<<" no existe o es ilegible."<<endl;
				}
				else if(cargado.getNombre()!="0a" && !poligonosMemoria.empty())
				{
					encontrado = buscarPoligono(poligonosMemoria,cargado.getNombre());
				}
				if(encontrado)
					cout<<"~El objeto "<<cargado.getNombre()<<" ya ha sido cargado anteriormente"<<endl;
				else if(!encontrado)
				{
					poligonosMemoria.push_front(cargado);
					cout<<"~El objeto "<<cargado.getNombre()<<" ha sido cargado exitosamente del archivo "<<lineIn<<endl;
				}
			}
			else
				cout<< "~Parametros invalidos"<<endl;
		}
		else if(comando1=="listado")
			listapoligonos(poligonosMemoria);
		else if(comando1=="envolvente")
		{
			if (milista.size()==2)
			{
				it++;
				lineIn=*it;
				cargado.inicializarPoligono();
				cargado=envolvente(lineIn, poligonosMemoria);
				if(cargado.getNombre()=="fallo")
				{
					cout<<"~No se cargó ningun poligono"<<endl;
				}
				else
				{
					envolventes.push_front(cargado);
					cout<<"~La caja envolvente de "<<lineIn<<" se ha generado con el nombre "<<cargado.getNombre()<<endl;
				}
			}
			else if (milista.size()==1)
			{
				lineIn="all";
				cargado.inicializarPoligono();
				cargado=envolvente(lineIn, poligonosMemoria);
				if(cargado.getNombre()=="fallo")
				{
					cout<<"~No se cargó ningun poligono"<<endl;
				}
				else
				{
					envolventes.push_front(cargado);
					cout<<"~La caja envolvente de los objetos en memoria se ha generado con el nombre "<<cargado.getNombre()<<endl;
				}
			}
			else
				cout<< "~Parametros invalidos"<<endl;
		}
		else if(comando1=="descargar")
		{
			if (milista.size()==2)
			{
				it++;
				lineIn=*it;
				if(descargarmemoria(poligonosMemoria,lineIn))
					cout<<"~El objeto "<<lineIn<<" ha sido eliminado de la memoria de trabajo."<<endl;
				else
					cout<<"~El objeto "<<lineIn<<" no ha sido cargado en memoria."<<endl;
			}
			else
				cout<< "~Parametros invalidos"<<endl;
		}
		else if(comando1=="guardar")
		{
			if (milista.size()==3)
			{
				it++;
				lineIn=*it;
				it++;
				lineIn2=*it;
				if(guardarPoligono(lineIn, lineIn2, envolventes))
					cout<<"~La informacion del objeto "<<lineIn<<" ha sido guardada exitosamente en el archivo "<<lineIn2<<"."<<endl;
				else
					cout<<"~El objeto "<<lineIn<<" no ha sido cargado en memoria."<<endl;
			}
			else
				cout<< "~Parametros invalidos"<<endl;
		}
		else if(comando1=="v_cercano")
		{
			if (milista.size()==5)
			{
				it++;
				float x=stof(*it);
				it++;
				float y=stof(*it);
				it++;
				float z=stof(*it);
				it++;
				lineIn=*it;
				componente2Punto1(lineIn,poligonosMemoria,x,y,z,false,1);
			}
			else if (milista.size()==4)
			{
				it++;
				float x=stof(*it);
				it++;
				float y=stof(*it);
				it++;
				float z=stof(*it);
				componente2Punto2(poligonosMemoria,x,y,z);
			}
			else
				cout<< "~Parametros invalidos"<<endl;
		}
		else if(comando1=="v_cercanos_caja")
		{
			if (milista.size()==2)
			{
				it++;
				lineIn=*it;
				componente2Punto3(lineIn,poligonosMemoria);
			}
			else
				cout<< "Parametros invalidos"<<endl;
		}
		else if(comando1=="ayuda")
		{
			if (milista.size()==1)
			{
				cout<<endl<<"~Comandos disponibles: "<<endl<<"   cargar"<<endl<<"   listado"<<endl<<"   envolvente"<<endl<<"   descargar"<<endl<<"   guardar"<<endl<<"   v_cercano"<<endl<<"   v_cercanos_caja"<<endl<<"   salir"<<endl;
			}
			else if (milista.size()==2)
			{
				it++;
				lineIn=*it;
				if(lineIn=="cargar")
					cout<<"===cargar <nombre_archivo>"<<endl<<"====Carga en memoria la información del objeto nombre_objeto contenida en el archivo identificado por nombre_archivo"<<endl;
				if(lineIn=="listado")
					cout<<"===listado"<<endl<<"====Lista los objetos cargados actualmente en memoria, junto con la información básica de cada uno: cantidad de puntos, de aristas y de caras."<<endl;
				if(lineIn=="envolvente")
					cout<<"===envolvente / envolvente <nombre_archivo>"<<endl<<"====Calcula la caja envolvente del objeto identificado por nombre_objeto, si no se ingresa nombre_objeto se calcula la caja que envuelve todos los objetos."<<endl;
				if(lineIn=="descargar")
					cout<<"===descargar <nombre_objeto>"<<endl<<"====Descarga de la memoria toda la información básica (vértices, aristas, caras) del objeto identificado por nombre_objeto."<<endl;
				if(lineIn=="guardar")
					cout<<"===guardar <nombre_objeto nombre_archivo>"<<endl<<"====Escribe en un archivo de texto, identificado por nombre_archivo, la información básica (vértices y caras) del objeto identificado por nombre_objeto."<<endl;
				if(lineIn=="v_cercano")
					cout<<"===v_cercano <x y z nombre_objeto> / v_cercano <x y z>"<<endl<<"====Identifica el vértice del objeto nombre_objeto más cercano al punto indicado por las coordenadas px , py y pz. En caso de no ingresarse nombre_objeto se calcula el vertice mas cercano al punto entre todos los objetos"<<endl;
				if(lineIn=="v_cercano_caja")
					cout<<"===v_cercanos_caja <nombre_objeto>"<<endl<<"====Identifica los vértices del objeto nombre_objeto más cercanos a los puntos (vértices) que definen la respectiva caja envolvente del objeto."<<endl;
				if(lineIn=="salir")
					cout<<"===salir"<<endl<<"====Termina la ejecucion de la aplicacion."<<endl;
			}
			else
				cout<< "~Parametros invalidos"<<endl;
		}
		else if(comando1=="salir")
			on = false;
		else
			cout<<"~Comando no valido"<<endl;
	}
	return 0;
}
poligono cargarPoligono(string val, std::list<poligono> &poligonosMemoria)
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
		pOut.setNombre(line);
		getline (myfile,line);
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
									vAux.indice = countE;
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
			cAux.tamanoCara = stof(cara.c_str());
			strAcumX2 += line[contCara];
			for(int i = 1; i <=line.size(); i++)
			{
				if(line[i+1] == ' ')
				{
					cAux.v1 = (pOut.buscarVertice(stof(strAcumX2.c_str())));
					strAcumY2 += line[i+2];
					for(int j = i+2; j <=line.size(); j++)
					{
						if(line[j+1] == ' ')
						{
							cAux.v2 = (pOut.buscarVertice(stof(strAcumY2.c_str())));
							strAcumZ2 += line[j+2];
							for(int k = j+2; k <=line.size(); k++)
							{
								if(line[k+1] == ' ' )
								{
									cAux.v3 = (pOut.buscarVertice(stof(strAcumZ2.c_str())));
									pOut.insertarCara(cAux);
									pOut.insertarArista(cAux.v1, cAux.v2);
									pOut.insertarArista(cAux.v2, cAux.v3);
									pOut.insertarArista(cAux.v1, cAux.v3);
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
	else
		pOut.setNombre("wrongfile");
	return pOut;
}
bool buscarPoligono(list<poligono> listIn, string nombreIn)
{
	for(list<poligono>::iterator buscaItera = listIn.begin(); buscaItera != listIn.end();buscaItera++)
	{
		if((*buscaItera).getNombre() == nombreIn)
			return true;
	}
	return false;
}
poligono buscarPoligono2(list<poligono> listIn, string nombreIn)
{
	poligono aux;
	aux.inicializarPoligono();
	for(list<poligono>::iterator buscaItera = listIn.begin(); buscaItera != listIn.end();buscaItera++)
	{
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
		for(list<vertice>::reverse_iterator  buscaIteraV = listaVAux.rbegin(); buscaIteraV != listaVAux.rend();++buscaIteraV)
			myfile <<(*buscaIteraV).x<<" " <<(*buscaIteraV).y<<" " <<(*buscaIteraV).z<<"\n";
		for(list<cara>::reverse_iterator  buscaIteraC = listaCAux.rbegin(); buscaIteraC != listaCAux.rend();++buscaIteraC)
			myfile <<(*buscaIteraC).tamanoCara<<" " <<(*buscaIteraC).v1.indice<<" " <<(*buscaIteraC).v2.indice<<" "<<(*buscaIteraC).v3.indice<<"\n";
		myfile <<"-1"<<"\n";
		myfile.close();
		return true;
	}
	else
	{
		return false;
	}
}
void listapoligonos(list<poligono> &poligonosMemoria)
{
	list<poligono>::iterator itPoli;
	list<vertice> listaAux;
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
			cout<<"Nombre: "<<itPoli->getNombre()<<" Contiene: "<<itPoli->getCantidadVertices()<<" vertices, "<<itPoli->getListaAristas().size()
					<<" aristas y "<<itPoli->getCantidadCaras() <<" caras."<<endl;
			listaAux = itPoli->getListaVertices();
		}
		cout<<"=================================="<<endl;
	}
}
bool descargarmemoria(list<poligono> &poligonosMemoria, string nombre_objeto)
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
		return true;
	else
		return false;
}
poligono envolvente(string nombreObjeto, list<poligono> listIn)
{
	poligono pObj,pAux;
	vertice auxmax, auxmin,aux;
	auxmax.x = 0;
	auxmax.y = 0;
	auxmax.z = 0;
	auxmin.x = 100000;
	auxmin.y = 100000;
	auxmin.z = 100000;
	vertice v1;
	vertice v2;
	vertice v3;
	vertice v4;
	vertice v5;
	vertice v6;
	vertice v7;
	vertice v8;
	list<vertice> listaVAux;
	list<vertice>::iterator itVert;
	list<cara> listaCAux;
	list<cara>::iterator itCara;
	list<poligono>::iterator itPoli;
	cara careishon;
	if(nombreObjeto=="all")
	{
		for(itPoli=listIn.begin(); itPoli!=listIn.end(); itPoli++)
		{
			pObj=*itPoli;
			list<vertice> listaAuxx = pObj.getListaVertices();
			for(itVert=listaAuxx.begin();itVert!=listaAuxx.end();itVert++)
			{
				if(itVert->x > auxmax.x)
					auxmax.x = itVert->x;
				if(itVert->y > auxmax.y)
					auxmax.y = itVert->y;
				if(itVert->z > auxmax.z)
					auxmax.z = itVert->z;
				if(itVert->x < auxmin.x)
					auxmin.x = itVert->x;
				if(itVert->y < auxmin.y)
					auxmin.y = itVert->y;
				if(itVert->z < auxmin.z)
					auxmin.z=itVert->z;
			}
		}
		auxmax.indice = 0;
		listaVAux.push_front(auxmax);
		v1 = auxmax;
		aux.x=auxmax.x;
		aux.y=auxmin.y;
		aux.z=auxmax.z;
		aux.indice = 1;
		listaVAux.push_front(aux);
		v2 = aux;
		aux.x=auxmax.x;
		aux.y=auxmin.y;
		aux.z=auxmin.z;
		aux.indice = 2;
		listaVAux.push_front(aux);
		v3 = aux;
		aux.x=auxmax.x;
		aux.y=auxmax.y;
		aux.z=auxmin.z;
		aux.indice = 3;
		listaVAux.push_front(aux);
		v4 = aux;
		aux.x=auxmin.x;
		aux.y=auxmax.y;
		aux.z=auxmax.z;
		aux.indice = 4;
		listaVAux.push_front(aux);
		v5 = aux;
		aux.x=auxmin.x;
		aux.y=auxmax.y;
		aux.z=auxmin.z;
		aux.indice = 5;
		listaVAux.push_front(aux);
		v6 = aux;
		aux.x=auxmin.x;
		aux.y=auxmin.y;
		aux.z=auxmax.z;
		aux.indice = 6;
		listaVAux.push_front(aux);
		v7 = aux;
		auxmin.indice = 7;
		listaVAux.push_front(auxmin);
		v8 = aux;
		careishon.tamanoCara = pObj.tamCara(v1,v2,v3);
		careishon.v1 = v1;
		careishon.v2 = v2;
		careishon.v3 = v3;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v2,v3,v4);
		careishon.v1 = v2;
		careishon.v2 = v3;
		careishon.v3 = v4;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v3,v4,v5);
		careishon.v1 = v3;
		careishon.v2 = v4;
		careishon.v3 = v5;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v4,v5,v6);
		careishon.v1 = v4;
		careishon.v2 = v5;
		careishon.v3 = v6;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v5,v6,v7);
		careishon.v1 = v5;
		careishon.v2 = v6;
		careishon.v3 = v7;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v6,v7,v8);
		careishon.v1 = v6;
		careishon.v2 = v7;
		careishon.v3 = v8;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v1,v2,v8);
		careishon.v1 = v1;
		careishon.v2 = v2;
		careishon.v3 = v8;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v1,v8,v7);
		careishon.v1 = v1;
		careishon.v2 = v8;
		careishon.v3 = v7;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v2,v4,v8);
		careishon.v1 = v2;
		careishon.v2 = v4;
		careishon.v3 = v8;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v4,v8,v6);
		careishon.v1 = v4;
		careishon.v2 = v8;
		careishon.v3 = v6;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v5,v3,v1);
		careishon.v1 = v5;
		careishon.v2 = v3;
		careishon.v3 = v1;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v7,v1,v5);
		careishon.v1 = v7;
		careishon.v2 = v1;
		careishon.v3 = v5;
		listaCAux.push_front(careishon);
		pAux.setListaVertices(listaVAux);
		pAux.setCantidadVertices(8);
		pAux.setlistaCaras(listaCAux);
		pAux.setNombre("envolTodos");
	}
	else if(buscarPoligono(listIn, nombreObjeto))
	{
		pObj = buscarPoligono2(listIn, nombreObjeto);
		list<vertice> listaAuxx = pObj.getListaVertices();
		for(itVert=listaAuxx.begin();itVert!=listaAuxx.end();itVert++)
		{

			if(itVert->x > auxmax.x)
				auxmax.x = itVert->x;
			if(itVert->y > auxmax.y)
				auxmax.y = itVert->y;
			if(itVert->z > auxmax.z)
				auxmax.z = itVert->z;
			if(itVert->x < auxmin.x)
				auxmin.x = itVert->x;
			if(itVert->y < auxmin.y)
				auxmin.y = itVert->y;
			if(itVert->z < auxmin.z)
				auxmin.z=itVert->z;
		}
		auxmax.indice = 0;
		listaVAux.push_front(auxmax);
		v1 = auxmax;
		aux.x=auxmax.x;
		aux.y=auxmin.y;
		aux.z=auxmax.z;
		aux.indice = 1;
		listaVAux.push_front(aux);
		v2 = aux;
		aux.x=auxmax.x;
		aux.y=auxmin.y;
		aux.z=auxmin.z;
		aux.indice = 2;
		listaVAux.push_front(aux);
		v3 = aux;
		aux.x=auxmax.x;
		aux.y=auxmax.y;
		aux.z=auxmin.z;
		aux.indice = 3;
		listaVAux.push_front(aux);
		v4 = aux;
		aux.x=auxmin.x;
		aux.y=auxmax.y;
		aux.z=auxmax.z;
		aux.indice = 4;
		listaVAux.push_front(aux);
		v5 = aux;
		aux.x=auxmin.x;
		aux.y=auxmax.y;
		aux.z=auxmin.z;
		aux.indice = 5;
		listaVAux.push_front(aux);
		v6 = aux;
		aux.x=auxmin.x;
		aux.y=auxmin.y;
		aux.z=auxmax.z;
		aux.indice = 6;
		listaVAux.push_front(aux);
		v7 = aux;
		auxmin.indice = 7;
		listaVAux.push_front(auxmin);
		v8 = aux;
		careishon.tamanoCara = pObj.tamCara(v1,v2,v3);
		careishon.v1 = v1;
		careishon.v2 = v2;
		careishon.v3 = v3;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v2,v3,v4);
		careishon.v1 = v2;
		careishon.v2 = v3;
		careishon.v3 = v4;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v3,v4,v5);
		careishon.v1 = v3;
		careishon.v2 = v4;
		careishon.v3 = v5;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v4,v5,v6);
		careishon.v1 = v4;
		careishon.v2 = v5;
		careishon.v3 = v6;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v5,v6,v7);
		careishon.v1 = v5;
		careishon.v2 = v6;
		careishon.v3 = v7;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v6,v7,v8);
		careishon.v1 = v6;
		careishon.v2 = v7;
		careishon.v3 = v8;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v1,v2,v8);
		careishon.v1 = v1;
		careishon.v2 = v2;
		careishon.v3 = v8;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v1,v8,v7);
		careishon.v1 = v1;
		careishon.v2 = v8;
		careishon.v3 = v7;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v2,v4,v8);
		careishon.v1 = v2;
		careishon.v2 = v4;
		careishon.v3 = v8;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v4,v8,v6);
		careishon.v1 = v4;
		careishon.v2 = v8;
		careishon.v3 = v6;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v5,v3,v1);
		careishon.v1 = v5;
		careishon.v2 = v3;
		careishon.v3 = v1;
		listaCAux.push_front(careishon);
		careishon.tamanoCara  = pObj.tamCara(v7,v1,v5);
		careishon.v1 = v7;
		careishon.v2 = v1;
		careishon.v3 = v5;
		listaCAux.push_front(careishon);
		pAux.setListaVertices(listaVAux);
		pAux.setCantidadVertices(8);
		pAux.setlistaCaras(listaCAux);
		pAux.setNombre("envol"+nombreObjeto);
	}
	else
		pAux.setNombre("fallo");
	return pAux;
}
float* componente2Punto1(string nombrePoligono, list<poligono> poligonosMemoria, float x, float y, float z, bool on, int imp)
{
	if(buscarPoligono(poligonosMemoria, nombrePoligono))
	{
		poligono aux = buscarPoligono2(poligonosMemoria, nombrePoligono);
		list<vertice> listaP = aux.getListaVertices();
		BinaryTree<float> arbolAux;
		vertice vAux;
		float* valorOut = new float;
		while(!listaP.empty())
		{
			arbolAux.insert(*(calcularDistancia(listaP.front().x, listaP.front().y, listaP.front().z, x, y, z)));
			listaP.pop_front();
		}
		listaP = aux.getListaVertices();
		int i = 1;
		*valorOut = arbolAux.min();
		if(on && imp==0)
			return valorOut;
		while(!listaP.empty())
		{
			if(arbolAux.min() == *calcularDistancia(listaP.front().x, listaP.front().y, listaP.front().z, x, y, z) && imp == 1)
			{
				cout<<"~El vertice "<<listaP.front().indice<<" ("<< listaP.front().x<<", "<<listaP.front().y<<", "<<listaP.front().z<<") del objeto "<<nombrePoligono<<
					" es el mas cercano al punto("<<x<<", "<<y<<", "<<z<<") a una distacia de "<< arbolAux.min() <<endl;
				return valorOut;
			}
			if(arbolAux.min() == *calcularDistancia(listaP.front().x, listaP.front().y, listaP.front().z, x, y, z) && imp == 2)
			{
				cout<<" ("<<x<<","<<y<<","<<z<<")     "<<listaP.front().indice<<" ("<< listaP.front().x<<","<<listaP.front().y<<","<<listaP.front().z<<")     "<<arbolAux.min() <<endl;
				return valorOut;
			}
			i++;
			listaP.pop_front();
		}
	}
	else
	{
		cout<<"~El objeto "<<nombrePoligono<<" no ha sido cargado en memoria"<<endl;
	}
	return 0;
}
void componente2Punto2(list<poligono> poligonosMemoria, float x, float y, float z)
{
	list<poligono> listaAux = poligonosMemoria;
	BinaryTree<float> arbolAux;
	if(!poligonosMemoria.empty())
	{
		while(!listaAux.empty())
		{
			arbolAux.insert(*componente2Punto1(listaAux.front().getNombre(), poligonosMemoria, x, y, z, true, 0));
			listaAux.pop_front();
		}
		listaAux = poligonosMemoria;
		while(!listaAux.empty())
		{
			if(arbolAux.min() == *componente2Punto1(listaAux.front().getNombre(), poligonosMemoria, x, y, z, true, 0))
			{
				float ans = *componente2Punto1(listaAux.front().getNombre(), poligonosMemoria, x, y, z, false, 1);
			}
			listaAux.pop_front();
		}
	}
	else
	{
		cout<<"~Ningun objeto ha sido cargado en memoria"<<endl;
	}
}
void componente2Punto3(string nombrePoligono,list<poligono> poligonosMemoria)
{
	poligono envolvente1;
	BinaryTree<float> arbolAux;
	vertice vAux;
	int i=1;
	if(buscarPoligono(poligonosMemoria, nombrePoligono))
	{
		envolvente1 = envolvente(nombrePoligono,  poligonosMemoria);
		list<vertice> listaP = envolvente1.getListaVertices();
		cout<<"Esquina               Vertice               Distancia"<<endl;
		while(!listaP.empty())
		{
			cout<<i;
			componente2Punto1(nombrePoligono, poligonosMemoria, listaP.front().x, listaP.front().y, listaP.front().z, false, 2);
			listaP.pop_front();
			i++;
		}
	}
	else
	{
		cout<<"~El objeto "<<nombrePoligono<<" no ha sido cargado en memoria"<<endl;
	}

}
float* calcularDistancia( float x, float y, float z, float x2, float y2, float z2)
{
	float* out = new float;
	*out = abs(sqrt( pow((x2 - x),2) + pow((y2 - y),2) + pow((z2 - z),2)));
	return out;
}
