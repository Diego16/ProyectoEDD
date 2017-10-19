#include <iostream>
#include "poligono.h"
#include "poligono.hpp"
#include "BinaryTree.h"
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
float* componente2Punto1(string nombrePoligono, list<poligono> poligonosMemoria, float x, float y, float z, bool on);
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
		cout<<"$";
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
			else
			{
				cout<< "Parametros invalidos"<<endl;
			}
		}
		else if(comando1=="listado")
			listapoligonos(poligonosMemoria);
		else if(comando1=="envolvente")
		{
			if (milista.size()==2)
			{
				it++;
				lineIn=*it;
				envolventes.push_front(envolvente(lineIn, poligonosMemoria));
			}
			else if (milista.size()==1)
			{
				lineIn="all";
				envolventes.push_front(envolvente(lineIn, poligonosMemoria));	
			}
			else
			{
				cout<< "Parametros invalidos"<<endl;
			}
		}
		else if(comando1=="descargar"){
			if (milista.size()==2)
			{
				it++;
				lineIn=*it;
				descargarmemoria(poligonosMemoria,lineIn);
			}
			else
			{
				cout<< "Parametros invalidos"<<endl;
			}
		}
		else if(comando1=="guardar")
		{
			if (milista.size()==3)
			{
				it++;
				lineIn=*it;
				it++;
				lineIn2=*it;
				guardarPoligono(lineIn, lineIn2, poligonosMemoria);
			}
			else
				cout<< "Parametros invalidos"<<endl;
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
				componente2Punto1(lineIn,poligonosMemoria,x,y,z,false);
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
		}
		else if(comando1=="v_cercanos_caja")
		{
			if (milista.size()==2)
			{
				it++;
				lineIn=*it;
				componente2Punto3(lineIn,poligonosMemoria);
			}
		}
		else if(comando1=="ayuda"){
			if (milista.size()==1)
			{
				cout<<endl<<"Comandos disponibles: "<<endl<<"   cargar"<<endl<<"   listado"<<endl<<"   envolvente"<<endl<<"   descargar"<<endl<<"   guardar"<<endl<<"   v_cercano"<<endl<<"   v_cercanos_caja"<<endl<<"   salir"<<endl;
			}
			else if (milista.size()==2){
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
		}
		else if(comando1=="salir")
			on = false;
		else
			cout<<"===Comando no valido"<<endl;
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

			if(line[0] == '-'&& line[1] == '1' && line.size() == 2){
				break;
			}
			strAcumX += line[0];
			for(int i = 0; i < line.size(); i++){

				if(line[i+1] == ' '){

					vAux.x = atoi(strAcumX.c_str());
					strAcumY += line[i+2];
					for(int j = i+2; j <line.size(); j++){
						if(line[j+1] == ' '){

							vAux.y = atoi(strAcumY.c_str());
							strAcumZ += line[j+2];
							for(int k = j+2; k <line.size(); k++){
								if(line[k+1] == NULL || line[k+1] == ' '){
									countE++;
									vAux.z = atoi(strAcumZ.c_str());
									pOut.insertarVertice(vAux);
									if(line[k+1] == NULL){
										terminado = true;
										break;
									}

									i = k;
									strAcumX.clear();
									strAcumY.clear();
									strAcumZ.clear();
                                    //strAcumX += line[i];

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
			strAcumX2 += line[contCara];
			for(int i = 1; i <=line.size(); i++){
				if(line[i+1] == ' '){
					cAux.jEsimoV.x = atoi(strAcumX2.c_str());
					strAcumY2 += line[i+2];
					for(int j = i+2; j <=line.size(); j++){
						if(line[j+1] == ' '){
							cAux.jEsimoV.y = atoi(strAcumY2.c_str());
							strAcumZ2 += line[j+2];
							for(int k = j+2; k <=line.size(); k++){
								if(line[k+1] == NULL || line[k+1] == ' ' ){
									cAux.jEsimoV.z = atoi(strAcumZ2.c_str());
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
				}
				else
					strAcumX2 += line[i+1];
			}
		}
		myfile.close();
	}
	else 
		cout << "Unable to open file";
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
	list<poligono>::iterator itPoli;
	cara careishon;
	if(nombreObjeto=="all")
	{
		for(itPoli=listIn.begin(); itPoli!=listIn.end(); itPoli++)
		{
			pObj=*itPoli;
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
		}
		pObj = buscarPoligono2(listIn, nombreObjeto);
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
	else if(buscarPoligono(listIn, nombreObjeto))
	{
		int i=0;
		pObj = buscarPoligono2(listIn, nombreObjeto);
		for(itVert=pObj.getListaVertices().begin();itVert!=pObj.getListaVertices().end();itVert++)
		{


			if(itVert->x>auxmax.x)
			{	
				auxmax.x=itVert->x;
			}
			if(itVert->y>auxmax.y)
			{	
				auxmax.y=itVert->y;
			}
			if(itVert->z>auxmax.z)
			{
				auxmax.z=itVert->z;
			}
			if(itVert->x<auxmin.x)
			{
				auxmin.x=itVert->x;
			}
			if(itVert->y<auxmin.y)
			{
				auxmin.y=itVert->y;
			}
			if(itVert->z<auxmin.z)
			{
				auxmin.z=itVert->z;
			}
			i++;
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
float* componente2Punto1(string nombrePoligono, list<poligono> poligonosMemoria, float x, float y, float z, bool on)
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
            cout<<"listaP.front.x: "<< listaP.front().x<< endl;
            cout<<"listaP.front.y: "<< listaP.front().y<< endl;
            cout<<"listaP.front.z: "<< listaP.front().z<< endl;
            cout<<"distancia calculada: "<< *(calcularDistancia(listaP.front().x, listaP.front().y, listaP.front().z, x, y, z))<< endl;
            arbolAux.insert(*(calcularDistancia(listaP.front().x, listaP.front().y, listaP.front().z, x, y, z)));
            listaP.pop_front();
         }
         listaP = aux.getListaVertices();
         int i = 1;
         *valorOut = arbolAux.min();
         if(on)
         	return valorOut;
         while(!listaP.empty())
         {
            if(arbolAux.min() == *calcularDistancia(listaP.front().x, listaP.front().y, listaP.front().z, x, y, z))
            {
                cout<<"--Del poligono "<< nombrePoligono<< ", el vertice numero "<< i
                <<  " con coordenadas ["<< listaP.front().x<<", "<<listaP.front().y
                <<", "<<listaP.front().z << "] es el mas cercano al punto [" <<x<<", "<<y<<", "<<z<<"] una distacia de "<< arbolAux.min() << " unidades--"<<endl;
                return valorOut;
            }
            i++;
            listaP.pop_front();
         }
    }
    else
    {
        cout<<"El poligono no se encontro en memoria"<<endl;
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
            arbolAux.insert(*componente2Punto1(listaAux.front().getNombre(), poligonosMemoria, x, y, z, true));
            listaAux.pop_front();
        }
        listaAux = poligonosMemoria;
        while(!listaAux.empty())
        {
            if(arbolAux.min() == *componente2Punto1(listaAux.front().getNombre(), poligonosMemoria, x, y, z, true))
            {
                float ans = *componente2Punto1(listaAux.front().getNombre(), poligonosMemoria, x, y, z, false);
            }
            listaAux.pop_front();
        }
    }
    else
    {
        cout<<"No hay poligonos en memoria"<<endl;
    }
}
void componente2Punto3(string nombrePoligono,list<poligono> poligonosMemoria)
{
    poligono envolvente1;
    BinaryTree<float> arbolAux;
    vertice vAux;
    if(buscarPoligono(poligonosMemoria, nombrePoligono))
    {
        envolvente1 = envolvente(nombrePoligono,  poligonosMemoria);
        list<vertice> listaP = envolvente1.getListaVertices();
        while(!listaP.empty())
        {
                componente2Punto1(nombrePoligono, poligonosMemoria, listaP.front().x, listaP.front().y, listaP.front().z, false);
                cout<< "Esquina de la envolvente de dicho objeto"<<endl;
        }

    }
    else
    {

        cout<<"El poligono no esta en memoria"<<endl;
    }

}
float* calcularDistancia( float x, float y, float z, float x2, float y2, float z2)
{
    float* out = new float;
    *out = abs(sqrt( pow((x2 - x),2) + pow((y2 - y),2) + pow((z2 - z),2)));
    return out;
}
