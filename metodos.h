#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct persona { // estructura que almacena los datos de una persona
    int rut;
    string nombres;
    string apellido_paterno;
    string apellido_materno;
    bool genero;
    unsigned short edad;
};

struct nodo {
    int pos;
    nodo *next;
};
typedef struct nodo listaEn;

struct BinaryNode {
	int key; // es al campo por el cual se identifica, y se busca, un nodo
	int pos; // depende de la forma de recorrer su BST
	BinaryNode* izq;
	BinaryNode* der;
};
typedef struct BinaryNode nodoBST;

struct NodeAVL {
  int key; //rut
  int value; //pos en el vector
  int altura;
  NodeAVL *izq;
  NodeAVL *der;
};

typedef struct NodeAVL AVL;

struct infoStruct {
  string apellido;
  int repeticiones;
  int edad_promedio;
  float pcent_hombres;
  float pcent_mujeres;
};

typedef struct info;


//typedef map<int, int> nodos;

int altura(AVL *arbol) {
  // Si el nodo es NULL, su altura es 0
  if (arbol == NULL) {
    return 0;
  }
  // De lo contrario, la altura es el máximo de las alturas de sus hijos más uno
  return max(altura(arbol->izq), altura(arbol->der)) + 1;
}

void rotarIzq(AVL* &arbol) {
    // Crea un nuevo nodo con el valor del nodo a
    AVL *b = new AVL;
    b->key = arbol->key;
    b->altura = arbol->altura;
    b->izq = arbol->izq;
    b->der = arbol->der->izq;

    // Actualiza el nodo a con el valor y la altura del nodo b
    arbol->key = arbol->der->key;
    arbol->altura = altura(arbol);
    arbol->izq = b;
    arbol->der = arbol->der->der;

    // Actualiza la altura del nodo b
    b->altura = altura(b);

    // Actualiza el puntero al nodo a
    arbol = b;
}

void rotarDer(AVL* &arbol) {
    // Crea un nuevo nodo con el valor del nodo a
    AVL *b = new AVL;
    b->key = arbol->key;
    b->altura = arbol->altura;
    b->der = arbol->der;
    b->izq = arbol->izq->der;

    // Actualiza el nodo a con el valor y la altura del nodo b
    arbol->key = arbol->izq->key;
    arbol->altura = altura(arbol);
    arbol->der = b;
    arbol->izq = arbol->izq->izq;

    // Actualiza la altura del nodo b
    b->altura = altura(b);

    // Actualiza el puntero al nodo a
    arbol = b;
}

void equilibrar(AVL* &arbol) {
    // Calcula la desviación de la altura de los hijos del nodo a
    int desviacion = altura(arbol->izq) - altura(arbol->der);

    // Si la desviación es mayor que 1, entonces el nodo a está desequilibrado hacia la izquierda
    if (desviacion > 1) {
        // Calcula la desviación de la altura de los hijos del nodo izquierdo
        int desviacionIzq = altura(arbol->izq->izq) - altura(arbol->izq->der);

        // Si la desviación del nodo izquierdo es mayor que 0, entonces se necesita una rotación simple a la derecha
        if (desviacionIzq > 0) {
            rotarDer(arbol);
        }
        // Si la desviación del nodo izquierdo es menor que 0, entonces se necesita una rotación doble a la derecha
        else {
            rotarIzq(arbol->izq);
            rotarDer(arbol);
        }
    }
    // Si la desviación es menor que -1, entonces el nodo a está desequilibrado hacia la derecha
    else if (desviacion < -1) {
        // Calcula la desviación de la altura de los hijos del nodo derecho
        int desviacionDer = altura(arbol->der->izq) - altura(arbol->der->der);

        // Si la desviación del nodo derecho es mayor que 0, entonces se necesita una rotación doble a la izquierda
        if (desviacionDer > 0) {
            rotarDer(arbol->der);
            rotarIzq(arbol);
        }
        // Si la desviación del nodo derecho es menor que 0, entonces se necesita una rotación simple a la izquierda
        else {
            rotarIzq(arbol);
        }
    }
}
void insertarPersonaAVL(AVL* &arbol, persona p, int pos) {
    // Si el árbol está vacío, crea un nuevo nodo con el valor y la posición dada
    if (arbol == NULL) {
        arbol = new AVL;
        arbol->key = p.rut;
        arbol->value = pos;
        arbol->altura = 1;
        arbol->izq = NULL;
        arbol->der = NULL;
    }
    // Si el RUT es menor que el RUT del nodo actual, inserta el nuevo nodo en el subárbol izquierdo
    else if (p.rut < arbol->key) {
        insertarPersonaAVL(arbol->izq, p, pos);
    }
    // Si el RUT es mayor que el RUT del nodo actual, inserta el nuevo nodo en el subárbol derecho
    else if (p.rut > arbol->key) {
        insertarPersonaAVL(arbol->der, p, pos);
    }
    // Si el RUT es igual al RUT del nodo actual, no se hace nada (el árbol AVL no permite valores duplicados)

    // Llama a la función de equilibrado para asegurar que el árbol se mantenga equilibrado
    equilibrar(arbol);
}

vector<info> buscarApellidosAVL(AVL* arbol, vector<persona> personas, vector<string> apellidos) {
    // Crea un vector de estructuras info con un tamaño igual al número de apellidos en el vector de apellidos
    vector<info> resultado(apellidos.size());

    // Si el nodo es nulo, termina la función
    if (arbol == NULL) return resultado;

    // Obtiene la posición del elemento de tipo persona en el vector de personas
    int posicion = arbol->key;

    // Obtiene el elemento de tipo persona a partir de su posición en el vector de personas
    persona p = personas[posicion];

    // Recorre el vector de apellidos
    for (int i = 0; i < apellidos.size(); i++) {
        // Si el apellido paterno o materno del elemento de tipo persona es igual a alguno de los apellidos del vector de apellidos
        if (p.apellido_paterno == apellidos[i] || p.apellido_materno == apellidos[i]) {
            // Incrementa el contador de repeticiones de la estructura info correspondiente
            resultado[i].repeticiones++;
            resultado[i].edad_promedio += p.edad;
            if(p.genero == 1){
                resultado[i].pcent_hombres++;
            }
            else{
                resultado[i].pcent_mujeres++;
            }
        }
    }

    // Llama a la función de búsqueda recursivamente para el subárbol izquierdo y derecho del nodo actual
    vector<info> resultadoIzq = buscarApellidosAVL(arbol->izq, personas, apellidos);
    vector<info> resultadoDer = buscarApellidosAVL(arbol->der, personas, apellidos);

    // Suma los valores de los vectores de estructuras info resultadoIzq y resultadoDer al vector de estructuras info resultado
    for (int i = 0; i < apellidos.size(); i++) {
        resultado[i].repeticiones += resultadoIzq[i].repeticiones + resultadoDer[i].repeticiones;
    }

    // Calcula el porcentaje de hombres y mujeres para cada estructura info
    for (int i = 0; i < apellidos.size(); i++) {
        if (resultado[i].repeticiones > 0) {
            resultado[i].pcent_hombres = ((float) resultado[i].pcent_hombres / resultado[i].repeticiones)*100;
            resultado[i].pcent_mujeres = ((float) resultado[i].pcent_mujeres / resultado[i].repeticiones)*100;
            resultado[i].edad_promedio = (float) resultado[i].edad_promedio / resultado[i].repeticiones;
        }
    }
    // Devuelve el vector de estructuras info resultado
    return resultado;
}

void ordenEnLista(vector<persona> personas, listaEn *perOrdenRut){   //ordenar vector usando listaEn((lazada))
    //listaEn *perOrdenRut lista enlazada de personas ordenadas segun rut.
    nodo *p; //puntero actual dentro de la lista enlazada
    p = perOrdenRut;
    p->pos = 0;
    unsigned int i,j; //iteradores
    for(i = 1; i < personas.size(); i++) {
        p->next = new nodo;
        p = p->next;
        p->pos = i;
    }
    cout << "ListaEn creada." << endl;
    p = perOrdenRut;

    //imprimir pos (SOLO TEST)
    // for(int i = 0; i < personas.size(); i++){
    //     cout << p->pos << " " << endl;
    //     p = p->next;
        
    // }

    int aux; //numero aux para cambiar pos
    for(i = 0; i < personas.size()-1; i++) {
        for(j = 0; j < personas.size()-i-1; j++) {
            if(p != nullptr && p->next != nullptr){
                if(personas[p->pos].rut>personas[p->next->pos].rut){
                    aux = p->pos;
                    p->pos = p->next->pos;
                    p->next->pos = aux;
                }
                p = p->next;
            }
        }
    }
}

void insert(nodoBST *(&root), int key, int pos){
    if (root == NULL){
        root = new nodoBST;
        root->key = key;
        root->pos = pos;
        root->izq = NULL;
        root->der = NULL;
    }
    else if (key < root->key){
        insert(root->izq, key, pos);
    }
    else if (key > root->key){
        insert(root->der, key, pos);
    }
}

void printPreorder(nodoBST *t){
	if (t!=nullptr){
		cout << "(" << t->key << ":" << t->pos << ") ";
		printPreorder(t->izq);
		printPreorder(t->der);
	}
}


void ordenEnArbol(vector<persona> personas, nodoBST *L){
    unsigned int i; //iterador
    for(i=0; i<personas.size(); i++){
        insert(L, personas[i].rut, i);
    }
    printPreorder(L);
}

void abreArchivo(string filename, vector<persona> personas){

    // Cargar el archivo "filename" y guardar los datos en personas;
    fstream file(filename, ios::in);

    string line;

    if(file.is_open()){ // si el archivo esta abierto
        int elemento = 0;
        string elementos[6];
        persona personaActual;
        int lineIndex = 0; //linea actual
        int totalLines = 0; //cantidad total de lineas
        unsigned int i; //iterador
        //6 elementos
        while (getline(file, line)){ //recorrer lineas y almacenar datos en vector personas
            elemento = 0;
            if (lineIndex != 0){
                totalLines++; //aumentar total de lineas
                for(i = 0; i < 6; i++){
                    elementos[i] = "";
                }
                for (i = 0; i < line.size(); i++){
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
                //cout << "-----" << elementos[0] << "-----" << stoi(elementos[0]) << "-----" << personaActual.rut << "-----" << endl;
                if(elementos[4] == "1"){
                    personaActual.genero = true;
                }
                else personaActual.genero = false;
                personaActual.edad = stoi(elementos[5]);

                personas.push_back(personaActual);
            }
            lineIndex++;
        }

        
    }
}





