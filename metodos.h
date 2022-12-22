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

//typedef map<int, int> nodos;


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





