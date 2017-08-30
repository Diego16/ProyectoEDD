#ifndef POLIGONO_H
#define POLIGONO_H
#include <string>
#include <list>

struct vertice{
	int x;
	int y;
	int z;
};

struct cara{
	float tamanoCara;
	vertice jEsimoV;
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

	protected:
		std::string nombre;
		int cantidadVertices;
		std::list<vertice> listaVertices;
		std::list<cara> listaCaras;
		int cantidadCaras;

};
#endif
