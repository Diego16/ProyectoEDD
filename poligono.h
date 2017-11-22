#ifndef POLIGONO_H
#define POLIGONO_H
#include <string>
#include <list>
// cambios realizados, en la envolvente se modifico uno de los ciclos
// en el poligono, se agrego el tipo de dato arista
// en el tipo de dato cara se agrego los vertices que la conforman
// se agrergo la variable indice en vertice
// se elimino la variable esimov de cara
// se modifico el guardado ya que guardaba alrevez
//cambios en el cargado para agregar de una vez las aristas
//se tiene un problema y es que las aristas se repiten


struct vertice{
    int indice;
	float x;
	float y;
	float z;
};

struct cara{
	float tamanoCara;
	vertice v1;
	vertice v2;
	vertice v3;
};

struct arista{
	float distancia;
	vertice origen;
	vertice destino;
};
class poligono{
	public:
		void inicializarPoligono();
		std::string getNombre();
		int getCantidadVertices();
		std::list<vertice> getListaVertices();
		std::list<cara> getlistaCaras();
		void setNombre(std::string val);
		void setCantidadVertices(int val);
		void setListaVertices(std::list<vertice> val);
		void setlistaCaras(std::list<cara> val);
		void insertarVertice(vertice val);
		void insertarCara(cara val);
		int getCantidadCaras();
		void insertarArista(vertice origen, vertice destino);
		std::list<arista>  getListaAristas();
		void setListaAristas(std::list<arista> listaIn);
		int getIndice();
		void setIndice(int indice);
		float calculaDist(vertice origen, vertice destino);
		vertice buscarVertice(int indice);
		float tamCara(vertice v11, vertice v22, vertice v33);
		void imprimeAristas();


	protected:
	    int indice;
		std::string nombre;
		int cantidadVertices;
		std::list<vertice> listaVertices;
		std::list<cara> listaCaras;
		std::list<arista> listaAristas;
		int cantidadCaras;


};
#endif
