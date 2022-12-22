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
    for(int i = 0; i < personas.size(); i++) {
        p = new nodo;
        p->pos = i;
        p = p->next;
    }

    p = perOrdenRut;
    for(int i = 0; i < personas.size(); i++){
        cout << p->pos << " " << endl;
        p = p->next;
        
    }

    cout << "aaaaaaaaaaa" << endl;
    int aux; //numero aux para cambiar pos
    for(int i = 0; i < personas.size()-1; i++) {
        cout << "1aaa" << endl;
        for(int j = 0; j < personas.size()-i-1; j++) {
            cout << "2bbb" << endl;
            cout << personas[p->pos].rut << " y " << personas[p->next->pos].rut << endl; 
            if(personas[p->pos].rut>personas[p->next->pos].rut){
                cout << "3ccc" << endl;
                aux = p->pos;
                p->pos = p->next->pos;
                p->next->pos = aux;
            }
        p = p->next;
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
    for(int i=0; i<personas.size(); i++){
        insert(L, personas[i].rut, i);
    }
    printPreorder(L);
}





