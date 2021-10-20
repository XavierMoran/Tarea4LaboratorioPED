//Tarea4LaboratorioPED//

//doble.hpp//
#include <iostream>
#include <string>
using namespace std;

struct personaId{
    string nombre;
    int numperfil; 
};

personaId solicitarpersonaId(void){
    personaId p;
    cout << "Nombre de la perosona y en () el rol que desempeña: (Administrador, Empleado o Cliente) " << endl;
    getline(cin, p.nombre);
    cout << "Id de la persona: ";
    cin >> p.numperfil; cin.ignore();
    return p;
}

void mostrarpersonaId(personaId p){
    cout << "Perfil de la perona: " << p.nombre; 
    cout << " (" << p.numperfil << ")." << endl;
}

//Uso de typedef para generalizar la lista doble con una plantilla

typedef personaId T;
const T noValido = {"",0};

struct nodo{
    T dato;
    nodo *sig;
    nodo *ant;
};

class ListaDoble{
    private:
        nodo *pInicio;
    public:
        ListaDoble();
        ~ListaDoble();
        void insertFront(T);
        void insertBack(T);
        void traversalForwardDirection(void);
        void traversalReverseDirection(void);
        void deleteItem(T);
        bool empty(void);
        bool searchItem(T);
        void insertAfter(T dato, T datoRef);
};

ListaDoble::ListaDoble(void){
    pInicio = NULL;
}

ListaDoble::~ListaDoble(void){
    nodo *p;
    while(pInicio){
        p = pInicio;
        pInicio = pInicio->sig;
        delete p;
    }
}

void ListaDoble::insertFront(T dato){
    nodo *nuevo = new nodo;
    nuevo->dato = dato;
    nuevo->sig = pInicio;
    if(pInicio != NULL)
        pInicio->ant = nuevo;
    pInicio = nuevo;
}

void ListaDoble::insertBack(T dato){
    nodo *nuevo = new nodo;
    nuevo->dato = dato;
    if(!pInicio){
        pInicio = nuevo;
        pInicio->sig = pInicio->ant = NULL;
    }
    else{
        nodo *saltarin = pInicio;
        while(saltarin->sig != NULL)
            saltarin = saltarin->sig;
        saltarin->sig = nuevo;
        nuevo->ant = saltarin;
        nuevo->sig = NULL;
    }
}

void ListaDoble::traversalForwardDirection(void){
    nodo *saltarin = pInicio;
    while(saltarin != NULL){
        mostrarpersonaId(saltarin->dato);//cout << saltarin->dato << endl;
        saltarin = saltarin->sig;
    }
}

void ListaDoble::traversalReverseDirection(void){
    if(!pInicio)
        return;
    nodo *p = pInicio;
    nodo *q = NULL;
    while(p){
        q = p;
        p = p->sig;
    }
    while(q){
        mostrarpersonaId(q->dato);//cout << q->dato << endl;
        q = q->ant;
    }
}

void ListaDoble::deleteItem(T datoB){
    if(!pInicio){ // Lista vacía.
        cout << "Actualmente no hay personas." << endl;
    }
    else{ // Si la lista no está vacía, entonces:
        nodo *saltarin = pInicio;
        while(saltarin && (saltarin->dato).nombre.compare(datoB.nombre)!=0) // Saltar.
            saltarin = saltarin->sig; // Luego de saltar hay varias posibilidades:
        if(!saltarin) // a) saltarín se salió (el dato no está en la lista).
            cout << "La persona no se encuentra en la lista." << endl;
        else{ // Si saltarín no se salió (está sobre el dato a eliminar):
              // el nodo puede estar al principio, puede estar al final,
              // puede estar entre dos nodos, puede ser el único nodo.
            if(!saltarin->ant && saltarin->sig){ // Al principio (y hay más nodos).
                pInicio = pInicio->sig;
                pInicio->ant = NULL;
                delete saltarin;
            }
            else
                if(saltarin->ant && !saltarin->sig){
                    saltarin->ant->sig = NULL;
                    delete saltarin;
                }
                else
                    if(saltarin->ant && saltarin->sig){
                        saltarin->ant->sig = saltarin->sig;
                        saltarin->sig->ant = saltarin->ant;
                        delete saltarin;
                    }
                    else{
                        pInicio = NULL;
                        delete saltarin;
                    }
            cout << "Persona eliminada correctamente" << endl;
        }
    }
}

bool ListaDoble::empty(void){
    return pInicio == NULL;
}

bool ListaDoble::searchItem(T datoB){
    if(!pInicio){ // Lista vacía.
        cout << "Actualmente no hay personas." << endl;
        return false;
    }
    else{ // Si la lista no está vacía, entonces:
        nodo *saltarin = pInicio;
        while(saltarin && (saltarin->dato).nombre.compare(datoB.nombre)!=0) // Saltar.
            saltarin = saltarin->sig; // Luego de saltar hay varias posibilidades:
        if(!saltarin) // a) saltarín se salió (el dato no está en la lista).
            return false;
        else
            return true;
    }
}

void ListaDoble::insertAfter(T dato, T datoRef){
    nodo *nuevo;
    nuevo = new nodo;
    nuevo->dato = dato;

    if(!pInicio){
        pInicio = nuevo;
        pInicio->sig = pInicio->ant = NULL;
    }
    else{
        nodo *saltarin;
        saltarin = pInicio;
        while(saltarin->sig != NULL && (saltarin->dato).nombre.compare(datoRef.nombre) != 0){
            saltarin = saltarin->sig;
        }
        nuevo->sig = saltarin->sig;
        nuevo->ant = saltarin;
        if(saltarin->sig != NULL)
            saltarin->sig->ant = nuevo;
        saltarin->sig = nuevo;

    }
}

//main.cpp//
#include "doble.hpp"

int menu(){
    int opcion = 0;
    cout << "---BIENVENIDO AL ADMINISTRADOR DE PERSONAS---" << endl << endl;
    cout << "1) Agregar una persona: " << endl; 
    cout << "2) Mostrar lista de personas." << endl; 
    cout << "3) Eliminar persona." << endl;
    cout << "4) Salir." << endl;
    cout << "Opcion: ";
    cin >> opcion; cin.ignore();
    return opcion;
}

int main(void){
    ListaDoble admin;
    
    bool continuar = true;
    personaId p;
    
    personaId pref;
    do{
        switch(menu()){
            case 1: //Agregar persona
                p = solicitarpersonaId();
                admin.insertFront(p);
                cout << "Persona agregada exitosamente!" << endl;
                break;
            case 2: //Mostrar lista
                admin.traversalForwardDirection();
                break;
            case 3: //Eliminar una persona
                if(admin.empty())
                    cout << "No hay personas por eliminar" << endl;
                else{
                    p = solicitarpersonaId();
                    admin.deleteItem(p);
                }
                break;
            case 4: //Salir
                continuar = false;
                break;
            default: //El usuario se equivoco
                cout << "La opcion no es valida, favor intente denuevo." << endl;
                break;
        }
    }while(continuar);
    
    return 0;
}
