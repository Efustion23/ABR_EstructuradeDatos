#include <iostream>
#include <string>

using namespace std;

// Estructura del nodo del árbol
struct Nodo {
    int ID;
    string nombre;
    string fechaNacimiento;
    string fechaDefuncion;
    char sexo;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo(int _ID, string _nombre, string _nac, string _def, char _sexo) {
        ID = _ID;
        nombre = _nombre;
        fechaNacimiento = _nac;
        fechaDefuncion = _def;
        sexo = _sexo;
        izquierda = NULL;
        derecha = NULL;
    }
};

// Buscar nodo por ID
Nodo* buscarPorID(Nodo* raiz, int IDbuscado) {
    if (raiz == NULL)
        return NULL;
    if (IDbuscado == raiz->ID)
        return raiz;
    if (IDbuscado < raiz->ID)
        return buscarPorID(raiz->izquierda, IDbuscado);
    else
        return buscarPorID(raiz->derecha, IDbuscado);
}

// Insertar nodo con verificación
Nodo* insertar(Nodo* raiz, Nodo* nuevo) {
    if (buscarPorID(raiz, nuevo->ID) != NULL) {
        cout << "Error: Ya existe un miembro con ID " << nuevo->ID << endl;
        return raiz;
    }

    if (raiz == NULL)
        return nuevo;

    if (nuevo->ID < raiz->ID)
        raiz->izquierda = insertar(raiz->izquierda, nuevo);
    else
        raiz->derecha = insertar(raiz->derecha, nuevo);

    return raiz;
}

// Recorrido Inorden
void inorden(Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda);
        cout << "\nID: " << raiz->ID;
        cout << "\nNombre: " << raiz->nombre;
        cout << "\nNacimiento: " << raiz->fechaNacimiento;
        cout << "\nDefunción: " << raiz->fechaDefuncion;
        cout << "\nSexo: " << raiz->sexo << "\n---------------------------";
        inorden(raiz->derecha);
    }
}

// Recorrido Preorden
void preorden(Nodo* raiz) {
    if (raiz != NULL) {
        cout << "\nID: " << raiz->ID;
        cout << "\nNombre: " << raiz->nombre;
        cout << "\nNacimiento: " << raiz->fechaNacimiento;
        cout << "\nDefunción: " << raiz->fechaDefuncion;
        cout << "\nSexo: " << raiz->sexo << "\n---------------------------";
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

// Recorrido Postorden
void postorden(Nodo* raiz) {
    if (raiz != NULL) {
        postorden(raiz->izquierda);
        postorden(raiz->derecha);
        cout << "\nID: " << raiz->ID;
        cout << "\nNombre: " << raiz->nombre;
        cout << "\nNacimiento: " << raiz->fechaNacimiento;
        cout << "\nDefunción: " << raiz->fechaDefuncion;
        cout << "\nSexo: " << raiz->sexo << "\n---------------------------";
    }
}

// Menú principal
int main() {
    Nodo* raiz = NULL;
    int opcion;

    do {
        cout << "\n========= Árbol Genealógico =========\n";
        cout << "1. Insertar miembro\n";
        cout << "2. Buscar miembro por ID\n";
        cout << "3. Mostrar Inorden\n";
        cout << "4. Mostrar Preorden\n";
        cout << "5. Mostrar Postorden\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (opcion == 1) {
            int id;
            string nombre, nac, def;
            char sexo;
            cout << "\n Ingrese los datos del nuevo miembro:\n";
            cout << "ID: ";
            cin >> id;
            cout << "Nombre: ";
            cin >> nombre;
            cout << "Fecha de nacimiento: ";
            cin >> nac;
            cout << "Fecha de defunción: ";
            cin >> def;
            cout << "Sexo (M/F): ";
            cin >> sexo;
            raiz = insertar(raiz, new Nodo(id, nombre, nac, def, sexo));
        }
        else if (opcion == 2) {
            int id;
            cout << "\n Ingrese el ID a buscar: ";
            cin >> id;
            Nodo* encontrado = buscarPorID(raiz, id);
            if (encontrado != NULL) {
                cout << "\n Miembro encontrado:";
                cout << "\n Nombre: " << encontrado->nombre;
                cout << "\n Nacimiento: " << encontrado->fechaNacimiento;
                cout << "\n Defunción: " << encontrado->fechaDefuncion;
                cout << "\n Sexo: " << encontrado->sexo << endl;
            } else {
                cout << "\n No se encontró ningún miembro con ese ID.\n";
            }
        }
        else if (opcion == 3) {
            cout << "\n Recorrido Inorden:\n";
            inorden(raiz);
        }
        else if (opcion == 4) {
            cout << "\n Recorrido Preorden:\n";
            preorden(raiz);
        }
        else if (opcion == 5) {
            cout << "\n Recorrido Postorden:\n";
            postorden(raiz);
        }
        else if (opcion == 0) {
            cout << "\n Saliendo del programa...\n";
        }
        else {
            cout << "\n Opción inválida. Intente nuevamente.\n";
        }

    } while (opcion != 0);

    return 0;
}
