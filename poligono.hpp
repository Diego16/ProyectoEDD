#include <iostream>
#include "poligono.h"
#include <string>
#include <list>
#include <cmath>
using namespace std;

void poligono::inicializarPoligono(){
	nombre = "0a";
	cantidadVertices = 0;
	listaVertices.clear();
	listaCaras.clear();
}

string poligono::getNombre(){
	return nombre;
}
int poligono::getCantidadCaras(){
	return listaCaras.size();
}
int poligono::getCantidadVertices(){
	return cantidadVertices;
}
std::list<vertice> poligono::getListaVertices(){
	return listaVertices;
}
std::list<cara> poligono::getlistaCaras(){
	return listaCaras;
}
void poligono::setNombre(string val){
	nombre = val;
}
void poligono::setCantidadVertices(int val){
	cantidadVertices = val;
}
void poligono::setListaVertices(std::list<vertice> val){
	listaVertices.clear();
	listaVertices = val;
}
void poligono::setlistaCaras(std::list<cara> val){
	listaCaras.clear();
	listaCaras = val;
}
void poligono::insertarVertice(vertice val){
    listaVertices.push_front(val);
}
void poligono::insertarCara(cara val){
    listaCaras.push_front(val);
}

void poligono::insertarArista(vertice origen, vertice destino){
    arista aAux;
    aAux.distancia = calculaDist(origen, destino);
    aAux.origen = origen;
    aAux.destino = destino;
    listaAristas.push_front(aAux);

    /*
    bool band = false;

    for (list<arista>::iterator it=listaAristas.begin(); it != listaAristas.end(); ++it){

        for (list<arista>::iterator it2=listaAristas.begin(); it2 != listaAristas.end(); ++it2){
            band = true;
            if((*it) == (*it2)){
                listaAristas.remove((*it2));
                break;
            }
        }
        if(band) break;

    }

*/
}
std::list<arista> poligono:: getListaAristas(){
    return this->listaAristas;
}
void poligono::setListaAristas(std::list<arista> listaIn){
    this->listaAristas = listaIn;
}
int poligono::getIndice(){
    return this->indice;
}
void poligono::setIndice(int indice){
    this->indice = indice;
}

float poligono::calculaDist(vertice origen, vertice destino){

    return abs(sqrt( pow((destino.x - origen.x),2) + pow((destino.y - origen.y),2) + pow((destino.z - origen.z),2)));

}

vertice poligono::buscarVertice(int indice){

    for (list<vertice>::iterator it=listaVertices.begin(); it != listaVertices.end(); ++it){
        if((*it).indice == indice)
        return (*it);
    }
}

float poligono::tamCara(vertice v11, vertice v22, vertice v33){

    float arista1 = calculaDist(v11, v22);
    float arista2 = calculaDist(v11, v33);
    float arista3 = calculaDist(v22, v33);

    return ((sqrt((arista1+arista2+arista3)*(arista1+arista2-arista3)*(arista1+arista2-arista1)*(arista3+arista2-arista2)))/4);

}

void poligono::imprimeAristas(){

    for (list<arista>::iterator it=listaAristas.begin(); it != listaAristas.end(); ++it){
        cout<<"------------------------------"<<endl;
        cout<<"Distancia de la arista: "<<(*it).distancia<<endl;
        cout<<"vertice origen indice: "<<(*it).origen.indice<<endl;
        cout<<"vertice origen x: "<<(*it).origen.x<<endl;
        cout<<"vertice origen y: "<<(*it).origen.y<<endl;
        cout<<"vertice origen z: "<<(*it).origen.z<<endl;
        cout<<"vertice destino indice : "<<(*it).destino.indice<<endl;
        cout<<"vertice destino x: "<<(*it).destino.x<<endl;
        cout<<"vertice destino y: "<<(*it).destino.y<<endl;
        cout<<"vertice destino z: "<<(*it).destino.z<<endl;
    }


}
