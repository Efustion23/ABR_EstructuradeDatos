#include <iostream>

using namespace std;

struct Nodo {
    int ID;
    string nombre;
    string fechaNacimiento;
    string fechaDefuncion;
    char sexo;
    Nodo* izquierda;
    Nodo* derecha;
};

Nodo(int _ID, string _nombre, string _nac, string _def, char _sexo, string _rol) {
        ID = _ID;
        nombre = _nombre;
        fechaNacimiento = _nac;
        fechaDefuncion = _def;
        sexo = _sexo;
        rol = _rol;
        izquierda = NULL;
        derecha = NULL;
    }
};


Nodo* insertar(Nodo* raiz, Nodo* nuevo) {
    if (raiz == nullptr)
        return nuevo;
    if (nuevo->ID < raiz->ID)
        raiz->izquierda = insertar(raiz->izquierda, nuevo);
    else
        raiz->derecha = insertar(raiz->derecha, nuevo);
    return raiz;
}


