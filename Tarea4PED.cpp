//Tarea4LaboratorioPED

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
