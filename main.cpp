#include <iostream>
#include "poligono.h"
#include "poligono.hpp"
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;


poligono cargarPoligono(string val, std::list<poligono> &poligonosMemoria);
string* tokenizador(std::string val);

int main()
{
    int on = 1;
    std::list<poligono> poligonosMemoria;
    string lineIn;

    while(on){
    int eleccion = 0;
    cout << "Bienvenido a la entrega 1, que desea hacer" << endl;
    cout << "1. Cargar poligono a memoria" << endl;
    cout << "2. Listar poligonos en memoria" << endl;
    cout << "3. Envolver objeto" << endl;
    cout << "4. Envolver objetos en memoria" << endl;
    cout << "5. Descargar memoria" << endl;
    cout << "6. Guardar objetos" << endl;
    cout << "7. Terminar programa" << endl;

    cin>>eleccion;

    switch(eleccion){

    case 1:
        cout << "ingrese nombre de archivo" << endl;
        cin>>lineIn;
        cargarPoligono(lineIn, poligonosMemoria);
        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

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



poligono cargarPoligono(string val, std::list<poligono> &poligonosMemoria){

    poligono pOut;
    pOut.inicializarPolinomio();
    string* str;
    string line;
    ifstream myfile(val.c_str());
    int cont = 1;

    if (myfile.is_open())
    {
        while (getline (myfile,line))
        {
            if(line == "-1")
                break;

            //cout << line << '\n';
            str = tokenizador(line);

            if(cont == 2){
                pOut.setCantidadVertices(atoi((*str).c_str()));
                cont++;
                cout<<"cont: "<<cont<<endl;
                cout<<"cant:"<<endl;
                cout<<pOut.getCantidadVertices()<<endl;
                cout<<"---"<<endl;
            }
            if(cont == 1){
                pOut.setNombre(*str);
                cout<<"cont: "<<cont<<endl;
                cont++;
                cout<<"nombre:"<<endl;
                cout<<pOut.getNombre()<<endl;
                cout<<"cont: "<<cont<<endl;
            }



            if(cont == 3){

                    //pOut.


            }

        }
    myfile.close();
    }

  else cout << "Unable to open file";
  return pOut;

}

string* tokenizador(std::string val){


    int tam = 0;
    int ini = 0;
    int fin = 0;

    for(int i = 0; i < val.size(); i++)
        if(val[i] == ' ')
            tam++;


    string* strOut = new string[tam+1];
    if(tam > 0){
        int cont = 0;
        for(int i = 0; i < val.size(); i++){
            if(val[i] == ' '){
                for(int j = ini; j < i; j++){
                    *(strOut + cont) += val[j];
                }
                cont++;
                ini = i;
            }
        }
    }else{
    *strOut = val;
    }

    return strOut;
}
