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

int main()
{
	int on = 1;
	list<poligono> poligonosMemoria;
	list<poligono>::iterator itLPoli;
	poligono cargado;
	string lineIn, obj;
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
			cout<<cargado.getNombre()<<encontrado<<endl;
			if(cargado.getNombre()=="0a")
			{
				cout<<"No se cargó ningun poligono"<<endl;
			}
			else if(cargado.getNombre()!="0a"&&poligonosMemoria.size()>0)
			{
				for(itLPoli=poligonosMemoria.begin(); itLPoli!=poligonosMemoria.end(); itLPoli++)
				{
					if(cargado.getNombre()==itLPoli->getNombre())
					{
						encontrado = true;
					}
				}
				itLPoli=poligonosMemoria.begin();
			}
			else if(encontrado==true)
				cout<<"Este poligono ya ha sido cargado anteriormente"<<endl;
			else if(!encontrado)
			{
				poligonosMemoria.push_front(cargado);
				cout<<"Poligono cargado correctamente"<<endl;
			}
			cout<<encontrado<<endl;
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
			break;
		case 7:
			on = 0;
			break;
		}
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
	int cont = 1;
	int cont2 = 1;
	vertice vAux;
	cara cAux;

	if (myfile.is_open())
	{
		while (getline (myfile,line))
		{
			if(line[0] == '-'&& line[1] == '1'&& line.size()==2 )
			{
				cout<<"-1 encontrado!"<<endl;
				break;
			}
			
			str = tokenizador(line);

			if(cont == 4)
			{

				cAux.tamanoCara = atoi((*str).c_str());
				cAux.jEsimoV.y = atoi((*(str+1)).c_str());
				cAux.jEsimoV.x = atoi((*(str+2)).c_str());
				cAux.jEsimoV.z = atoi((*(str+3)).c_str());


				pOut.insertarCara(cAux);


				cout<<"----: "<<endl;
				cout<<cont<<endl;
				cout<<"tamanio cara: "<<pOut.getlistaCaras().front().tamanoCara<<endl;
				cout<<"verticeX: "<<pOut.getlistaCaras().front().jEsimoV.x<<endl;
				cout<<"verticeY: "<<pOut.getlistaCaras().front().jEsimoV.y<<endl;
				cout<<"verticeZ: "<<pOut.getlistaCaras().front().jEsimoV.z<<endl;
				cout<<"---- "<<endl;


			}

			if(cont == 3)
			{

				vAux.x = atoi((*str).c_str());
				vAux.y = atoi((*(str+1)).c_str());
				vAux.z = atoi((*(str+2)).c_str());
				pOut.insertarVertice(vAux);
				cout<<"----: "<<endl;
				cout<<cont<<endl;
				cout<<"verticeX: "<<pOut.getListaVertices().front().x<<endl;
				cout<<"verticeY: "<<pOut.getListaVertices().front().y<<endl;
				cout<<"verticeZ: "<<pOut.getListaVertices().front().z<<endl;
				cout<<"---- "<<endl;

				cont2++;
				if(cont2 == pOut.getCantidadVertices()+1)
				{
					cont++;
					cont2 = 1;
				}
			}
			if(cont == 2)
			{
				pOut.setCantidadVertices(atoi((*str).c_str()));
				cont++;
				cout<<"Cantidad de vertices: "<<pOut.getCantidadVertices()<<endl;
			}
			if(cont == 1)
			{
				pOut.setNombre(*str);
				cont++;
				cout<<"Nombre: "<<pOut.getNombre()<<endl;
			}
		}
		myfile.close();
	}
	return pOut;
}
void listapoligonos(list<poligono> &poligonosMemoria)
{
	list<poligono>::iterator itPoli;
	if(poligonosMemoria.size()==0)
		cout<<"No hay objetos cargados en memoria\n";
	for(itPoli=poligonosMemoria.begin(); itPoli!=poligonosMemoria.end(); itPoli++)
	{
		cout<<"Nombre: "<<itPoli->getNombre()<<" Cantidad de vertices: "<<itPoli->getCantidadVertices()<<" Cantidad de caras: "<<itPoli->getCantidadCaras()<<endl;
		/*<<" Cantidad de aristas: "<<itPoli->getCantidadAristas() TODO: imprimir cantidad de aristas*/
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
string* tokenizador(std::string val)
{
	int tam = 0;
	int ini = 0;
	int fin = 0;
	for(int i = 0; i < val.size(); i++)
		if(val[i] == ' ')
			tam++;
	string* strOut = new string[tam+1];
	if(tam > 0)
	{
		int cont = 0;
		for(int i = 0; i < val.size(); i++)
		{
	
			if(val[i] == ' ' || (i+1 == val.size()))
			{

				for(int j = ini; j < i; j++)
				{
					*(strOut + cont) += val[j];
			
					if((i+1 == val.size()))
					{
						*(strOut + tam) = val[val.size()-1];

					}
				}
				cont++;
				ini = i;
			}
		}

	}
	else
	{
		*strOut = val;
	}
	return strOut;
}
