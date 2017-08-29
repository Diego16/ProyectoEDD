#include <iostream>
#include "poligono.h"
#include <string>
using namespace std;

void poligono::inicializarPolinomio(){

nombre = "0a";
cantidadVertices = 0;
listaVertices.clear();
listaCaras.clear();

}

string poligono::getNombre(){
return nombre;
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
void poligono::insertarVertice(){
    //listaCaras.push_front();

}
void poligono::insertarCara(){

}
