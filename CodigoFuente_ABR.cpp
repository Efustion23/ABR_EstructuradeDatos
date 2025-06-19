#include <iostream>
#include <string>
using namespace std;

// Estructura del nodo
struct Nodo {
    int ID;
    string nombre;
    string fechaNacimiento;
    string fechaDefuncion;
    char sexo;
    Nodo* izquierda;
    Nodo* derecha;
};

// Crear nuevo nodo
Nodo* crearNodo(int ID, string nombre, string nacimiento, string defuncion, char sexo) {
    Nodo* nuevo = new Nodo;
    nuevo->ID = ID;
    nuevo->nombre = nombre;
    nuevo->fechaNacimiento = nacimiento;
    nuevo->fechaDefuncion = defuncion;
    nuevo->sexo = sexo;
    nuevo->izquierda = NULL;
    nuevo->derecha = NULL;
    return nuevo;
}

// Ingresar datos por consola
Nodo* ingresarDatosMiembro() {
    int id;
    string nombre, nacimiento, defuncion;
    char sexo;

    cout << "ID: ";
    cin >> id;
    cout << "Nombre (una palabra): ";
    cin >> nombre;
    cout << "Fecha de nacimiento: ";
    cin >> nacimiento;
    cout << "Fecha de defunción (o '-' si no aplica): ";
    cin >> defuncion;
    cout << "Sexo (M/F): ";
    cin >> sexo;

    return crearNodo(id, nombre, nacimiento, defuncion, sexo);
}

// Verificar si el árbol está vacío
bool estaVacio(Nodo* raiz) {
    return raiz == NULL;
}

// Buscar por ID
Nodo* buscarPorID(Nodo* raiz, int IDbuscado) {
    if (raiz == NULL || raiz->ID == IDbuscado)
        return raiz;
    if (IDbuscado < raiz->ID)
        return buscarPorID(raiz->izquierda, IDbuscado);
    else
        return buscarPorID(raiz->derecha, IDbuscado);
}

// Insertar nodo con validación
Nodo* insertar(Nodo* raiz, Nodo* nuevo) {
    if (buscarPorID(raiz, nuevo->ID) != NULL) {
        cout << "Error: Ya existe un miembro con ese ID.\n";
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

// Recorrido inorden
void inorden(Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda);
        cout << "ID: " << raiz->ID
             << " | Nombre: " << raiz->nombre
             << " | Nac: " << raiz->fechaNacimiento
             << " | Def: " << raiz->fechaDefuncion
             << " | Sexo: " << raiz->sexo << endl;
        inorden(raiz->derecha);
    }
}

// Encontrar mínimo
Nodo* encontrarMinimo(Nodo* raiz) {
    if (raiz == NULL) return NULL;
    while (raiz->izquierda != NULL)
        raiz = raiz->izquierda;
    return raiz;
}

// Encontrar máximo
Nodo* encontrarMaximo(Nodo* raiz) {
    if (raiz == NULL) return NULL;
    while (raiz->derecha != NULL)
        raiz = raiz->derecha;
    return raiz;
}

// Mostrar un nodo
void mostrarMiembro(Nodo* nodo) {
    if (nodo != NULL) {
        cout << "\n--- Miembro encontrado ---\n";
        cout << "ID: " << nodo->ID << endl;
        cout << "Nombre: " << nodo->nombre << endl;
        cout << "Nacimiento: " << nodo->fechaNacimiento << endl;
        cout << "Defunción: " << nodo->fechaDefuncion << endl;
        cout << "Sexo: " << nodo->sexo << endl;
    } else {
        cout << "Miembro no encontrado.\n";
    }
}

// Buscar padre desde la raíz
Nodo* buscarPadre(Nodo* raiz, int id, Nodo* padre) {
    if (raiz == NULL)
        return NULL;
    if (raiz->ID == id)
        return padre;
    if (id < raiz->ID)
        return buscarPadre(raiz->izquierda, id, raiz);
    else
        return buscarPadre(raiz->derecha, id, raiz);
}

// Mostrar hijos del nodo
void mostrarHijos(Nodo* raiz, int id) {
    if (raiz == NULL)
        return;
    if (raiz->ID == id) {
        if (raiz->izquierda != NULL)
            cout << "Hijo izquierdo: " << raiz->izquierda->nombre << " (ID: " << raiz->izquierda->ID << ")\n";
        if (raiz->derecha != NULL)
            cout << "Hijo derecho: " << raiz->derecha->nombre << " (ID: " << raiz->derecha->ID << ")\n";
        if (raiz->izquierda == NULL && raiz->derecha == NULL)
            cout << "No tiene hijos registrados.\n";
        return;
    }
    if (id < raiz->ID)
        mostrarHijos(raiz->izquierda, id);
    else
        mostrarHijos(raiz->derecha, id);
}

// Menú principal con opción de parentescos
int main() {
    setlocale(LC_CTYPE, "Spanish");
    Nodo* raiz = NULL;
    int opcion;

    do {
        cout << "\n===== Menú Árbol Genealógico (ABB) =====\n";
        cout << "1. Insertar nuevo miembro\n";
        cout << "2. Buscar miembro por ID\n";
        cout << "3. Mostrar árbol inorden (ordenado por ID)\n";
        cout << "4. Mostrar miembro con menor ID\n";
        cout << "5. Mostrar miembro con mayor ID\n";
        cout << "6. Verificar si el árbol está vacío\n";
        cout << "7. Mostrar parentescos (padre e hijos)\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                Nodo* nuevo = ingresarDatosMiembro();
                raiz = insertar(raiz, nuevo);
                break;
            }
            case 2: {
                int id;
                cout << "Ingrese ID a buscar: ";
                cin >> id;
                Nodo* resultado = buscarPorID(raiz, id);
                mostrarMiembro(resultado);
                break;
            }
            case 3:
                cout << "\n--- Miembros ordenados por ID (Inorden) ---\n";
                inorden(raiz);
                break;
            case 4: {
                Nodo* min = encontrarMinimo(raiz);
                cout << "\nMiembro con menor ID:\n";
                mostrarMiembro(min);
                break;
            }
            case 5: {
                Nodo* max = encontrarMaximo(raiz);
                cout << "\nMiembro con mayor ID:\n";
                mostrarMiembro(max);
                break;
            }
            case 6:
                if (estaVacio(raiz))
                    cout << "El árbol está vacío.\n";
                else
                    cout << "El árbol NO está vacío.\n";
                break;
            case 7: {
                int id;
                cout << "Ingrese ID para mostrar parentescos: ";
                cin >> id;

                Nodo* miembro = buscarPorID(raiz, id);
                if (miembro == NULL) {
                    cout << "Miembro no encontrado.\n";
                    break;
                }

                Nodo* padre = buscarPadre(raiz, id, NULL);
                if (padre != NULL)
                    cout << "Padre: " << padre->nombre << " (ID: " << padre->ID << ")\n";
                else
                    cout << "No se encontró padre (posiblemente es la raíz).\n";

                mostrarHijos(raiz, id);
                break;
            }
            case 0:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }

    } while (opcion != 0);

    return 0;
}

