#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "utilidades.h"

// AGREGAR INCLUSIONES DE LIBRERIAS AQUI


using namespace std;

#define RUT_INF 192327744
#define RUT_SUP 195291841


struct persona { // estructura que almacena los datos de una persona
    int rut;
    string nombres;
    string apellido_paterno;
    string apellido_materno;
    bool genero;
    unsigned short edad;
};

struct info { // estructura que almacena informacion relevante sobre un apellido
    string apellido;
    int repeticiones;
    double edad_promedio;
    double pcent_mujeres;
    double pcent_hombres;
};

struct nodo {
    int pos;
    nodo *next;
};

typedef struct nodo listaEn;


int main(int argc, char **argv){
    if(argc != 2){
        cout << "Debe ejecutarse como ./prog n" << endl;
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

        //ordenar vector usando listaEn((lazada))
        listaEn *perOrdenRut; //lista enlazada de personas ordenadas segun rut.
        nodo *p; //puntero actual dentro de la lista enlazada
        p = perOrdenRut;
        for(int i = 0; i < personas.size(); i++) {
            p = new nodo;
            p->pos = i;
            p = p->next;
        }

        int aux; //numero aux para cambiar pos
        for(int i = 0; i < personas.size()-1; i++) {
            for(int j = 0; j < personas.size()-i-1; j++) {
                if(personas[p->pos].rut>personas[p->next->pos].rut){
                    aux = p->pos;
                    p->pos = p->next->pos;
                    p->next->pos = aux;
                }
            }
        }
    }

    cout << " ### FIN DEL PROGRAMA ###" << endl;
    return EXIT_SUCCESS;
}