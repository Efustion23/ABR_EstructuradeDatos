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

// Función para buscar un nodo por ID
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

// Función para insertar un nuevo nodo, con validación de ID
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

// Recorrido Inorden para mostrar los miembros
void inorden(Nodo* raiz) {
if (raiz != NULL) {
inorden(raiz->izquierda);
cout << "ID: " << raiz->ID
<< " | Nombre: " << raiz->nombre
<< " | Nacimiento: " << raiz->fechaNacimiento
<< " | Defuncion: " << raiz->fechaDefuncion
<< " | Sexo: " << raiz->sexo << endl;
inorden(raiz->derecha);
}
}

// Menú principal
int main() {
    Nodo* raiz = nullptr;
    int opcion;

    do {
        cout << "\n--- Árbol Genealógico de la Antigua Civilización ---\n";
        cout << "1. Insertar miembro\n";
        cout << "2. Buscar miembro\n";
        cout << "3. Mostrar descendientes\n";
        cout << "4. Mostrar ancestros\n";
        cout << "5. Eliminar miembro\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (opcion == 1) {
            int id;
            string nombre, nac, def;
            char sexo;
            cout << "ID: "; cin >> id;
            cin.ignore();
            cout << "Nombre: "; getline(cin, nombre);
            cout << "Fecha de nacimiento: "; getline(cin, nac);
            cout << "Fecha de defunción (si aplica): "; getline(cin, def);
            cout << "Sexo (M/F): "; cin >> sexo;
            raiz = insertar(raiz, new Nodo(id, nombre, nac, def, sexo));
        } else if (opcion == 2) {
            int id;
            cout << "Ingrese ID a buscar: "; cin >> id;
            Nodo* encontrado = buscar(raiz, id);
            if (encontrado) {
                cout << "Encontrado: " << encontrado->nombre << ", Nac: " << encontrado->fechaNacimiento << ", Def: " << encontrado->fechaDefuncion << endl;
            } else {
                cout << "Miembro no encontrado.\n";
            }
        } else if (opcion == 3) {
            cout << "Descendientes:\n";
            mostrarDescendientes(raiz);
        } else if (opcion == 4) {
            int id;
            cout << "Ingrese ID del descendiente para ver ancestros: "; cin >> id;
            if (!mostrarAncestros(raiz, id))
                cout << "Miembro no encontrado.\n";
        } else if (opcion == 5) {
            int id;
            cout << "Ingrese ID a eliminar: "; cin >> id;
            raiz = eliminar(raiz, id);
            cout << "Eliminado si existía.\n";
        }
    } while (opcion != 0);

    return 0;
}
