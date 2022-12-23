#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "metodos.h"
#include "utilidades.h"


// AGREGAR INCLUSIONES DE LIBRERIAS AQUI


using namespace std;

#define RUT_INF 192327744
#define RUT_SUP 195291841


struct info { // estructura que almacena informacion relevante sobre un apellido
    string apellido;
    int repeticiones;
    double edad_promedio;
    double pcent_mujeres;
    double pcent_hombres;
};


typedef struct nodo listaEn;


//void ordenEnLista(vector<persona> personas, listaEn *perOrdenRut);
//void ordenEnArbol(vector<persona> personas, nodoBST *L);
//void insert(nodoBST *(&root), int key, int pos);
//void printPreorder(nodoBST *t);
//void abreArchivo(string filename, vector<persona> personas);
//void genera_salida(const vector<T> &datos, const string &filename="salida_default");

int main(int argc, char **argv){
    if(argc != 2){
        cout << "Debe ejecutarse como ./tarea n" << endl;
        return EXIT_FAILURE;
    }

    string filename;
    cout <<"Ingrese nombre del archivo: ";
    cin >> filename;

    vector<persona> personas;

    abreArchivo(filename, personas);

    listaEn *perOrdenRut = new listaEn; //cout << "CHECK!" << endl;
    ordenEnLista(personas, perOrdenRut);

    //genera_salida(&datos, const string &filename="salida_default");


    
    //nodoBST *perOrdenArbol;
    //ordenEnArbol(personas, perOrdenArbol);

    cout << " ### FIN DEL PROGRAMA ###" << endl;
    return EXIT_SUCCESS;
}
