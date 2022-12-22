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


void ordenEnLista(vector<persona> personas, listaEn *perOrdenRut);
void ordenEnArbol(vector<persona> personas, nodoBST *L);
void insert(nodoBST *(&root), int key, int pos);
void printPreorder(nodoBST *t);

int main(int argc, char **argv){
    if(argc != 2){
        cout << "Debe ejecutarse como ./tarea n" << endl;
        return EXIT_FAILURE;
    }

    string filename;
    cout <<"Ingrese nombre del archivo: ";
    cin >> filename;

    vector<persona> personas;

    // Cargar el archivo "filename" y guardar los datos en personas;
    fstream file(filename, ios::in);

    string line;


    if(file.is_open()){ // si el archivo esta abierto
        int elemento = 0;
        string elementos[6];
        persona personaActual;
        int lineIndex = 0;
        int totalLines = 0; //cantidad total de lineas
        //6 elementos
        while (getline(file, line)){ //recorrer lineas y almacenar datos en vector personas
            totalLines++;
            elemento = 0;
            if (lineIndex != 0){
                for(int i = 0; i < 6; i++){
                    elementos[i] = "";
                }
                for (int i = 0; i < line.size(); i++){
                    if(line[i] != ','){
                        elementos[elemento] += line[i];
                    }
                    else{
                        cout << elementos[elemento] << endl;
                        elemento++;
                    }
                }

                //guardar elementos en vector personas
                personaActual.rut = stoi(elementos[0]);
                personaActual.nombres = elementos[1];
                personaActual.apellido_paterno = elementos[2];
                personaActual.apellido_materno = elementos[3];
                if(elementos[4] == "1"){
                    personaActual.genero = true;
                }
                else personaActual.genero = false;
                personaActual.edad = stoi(elementos[5]);

                personas.push_back(personaActual);
            }
            lineIndex++;
        }
    
    listaEn *perOrdenRut;
    ordenEnLista(personas, perOrdenRut);
    
    //nodoBST *perOrdenArbol;
    //ordenEnArbol(personas, perOrdenArbol);
    }

    cout << " ### FIN DEL PROGRAMA ###" << endl;
    return EXIT_SUCCESS;
}
