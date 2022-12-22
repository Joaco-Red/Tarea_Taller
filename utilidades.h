#include <vector>
#include <iostream>
#include <fstream>

using namespace std;



vector<string> consigue_apellidos(const int n){

    /*
    n -> Número de apellidos a buscar

    Devuelve un vector con apellidos conseguidos del archivo apellidos.txt
    */

    vector<string> apellidos;
    int c = 0;

    string line;
    fstream file("apellidos.txt", ios::in);

    if(file.is_open()){
        while(getline(file, line) && c++ < n){
            apellidos.push_back(line);
        }
    }

    return apellidos;
}



template <typename T>
void genera_salida(const vector<T> &datos, const string &filename="salida_default"){

    /*
    datos -> vector de información que contiene los datos a almacenar en el archivo de salida.
    filename (opcional) -> Nombre del archivo SIN FORMATO a guardar.

    guarda los datos en un archivo .csv, util para visualizar los resultados del programa.
    */

    ofstream file(filename+".csv");
    
    file << "apellido_paterno,repeticiones,edad_promedio,porcentaje_mujeres,porcentaje_hombres\n";
    for(T dato: datos){
        file << dato.apellido + ",";
        file << to_string(dato.repeticiones) + ",";
        file << to_string(dato.edad_promedio) + ",";
        file << to_string(dato.pcent_mujeres) + ",";
        file << to_string(dato.pcent_hombres) + "\n";
    }
    file.close();
    cout << " ** ARCHIVO " << filename + ".csv" << " GENERADO CON ÉXITO **" << endl;
}
