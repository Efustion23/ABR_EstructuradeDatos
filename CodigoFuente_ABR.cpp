#include <iostream>
#include <string>

using namespace std;

// ===== ESTRUCTURA DEL NODO =====
struct Nodo {
    int ID;
    string nombre;
    string fechaNacimiento;
    string fechaDefuncion;
    char sexo;
    Nodo* izquierda;
    Nodo* derecha;
};

// ===== FUNCIONES PARA CREAR E INGRESAR MIEMBROS =====
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

Nodo* ingresarDatosMiembro() {
    int id;
    string nombre, nacimiento, defuncion;
    char sexo;

    // Validar ID
    do {
        cout << "ID (positivo): ";
        cin >> id;
        if (id <= 0) cout << "? Error: El ID debe ser un número positivo.\n";
    } while (id <= 0);

    // Validar nombre
    do {
        cout << "Nombre (una palabra): ";
        cin >> nombre;
        if (nombre.empty()) cout << "? Error: El nombre no puede estar vacío.\n";
    } while (nombre.empty());

    // Validar fecha de nacimiento
    do {
        cout << "Fecha de nacimiento (dd-mm-aaaa): ";
        cin >> nacimiento;
        if (nacimiento.empty()) cout << "? Error: Este campo no puede estar vacío.\n";
    } while (nacimiento.empty());

    // Validar fecha de defunción
    do {
        cout << "Fecha de defunción (dd-mm-aaaa o 'no'): ";
        cin >> defuncion;
        if (defuncion.empty()) cout << "? Error: Este campo no puede estar vacío.\n";
    } while (defuncion.empty());

    // Validar sexo
    do {
        cout << "Sexo (M/F): ";
        cin >> sexo;
        sexo = toupper(sexo);
        if (sexo != 'M' && sexo != 'F') cout << "? Error: Solo se permite M o F.\n";
    } while (sexo != 'M' && sexo != 'F');

    return crearNodo(id, nombre, nacimiento, defuncion, sexo);
}

// ===== OPERACIONES DEL ÁRBOL BINARIO DE BÚSQUEDA =====
Nodo* buscarPorID(Nodo* raiz, int IDbuscado) {
    if (raiz == NULL || raiz->ID == IDbuscado)
        return raiz;
    if (IDbuscado < raiz->ID)
        return buscarPorID(raiz->izquierda, IDbuscado);
    else
        return buscarPorID(raiz->derecha, IDbuscado);
}

Nodo* insertar(Nodo* raiz, Nodo* nuevo) {
    if (buscarPorID(raiz, nuevo->ID) != NULL) {
        cout << "? Error: Ya existe un miembro con ese ID.\n";
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

// ===== RECORRIDOS DEL ÁRBOL =====
void inorden(Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda);
        cout << raiz->ID << " - " << raiz->nombre << endl;
        inorden(raiz->derecha);
    }
}

void preorden(Nodo* raiz) {
    if (raiz != NULL) {
        cout << raiz->ID << " - " << raiz->nombre << endl;
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

void postorden(Nodo* raiz) {
    if (raiz != NULL) {
        postorden(raiz->izquierda);
        postorden(raiz->derecha);
        cout << raiz->ID << " - " << raiz->nombre << endl;
    }
}

// ===== FUNCIONES AUXILIARES PARA CONSULTAS =====
void mostrarMiembro(Nodo* nodo) {
    if (nodo != NULL) {
        cout << "\n--- Miembro encontrado ---\n";
        cout << "ID: " << nodo->ID << endl;
        cout << "Nombre: " << nodo->nombre << endl;
        cout << "Nacimiento: " << nodo->fechaNacimiento << endl;
        cout << "Defunción: " << nodo->fechaDefuncion << endl;
        cout << "Sexo: " << nodo->sexo << endl;
    } else {
        cout << "? Miembro no encontrado.\n";
    }
}

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

void mostrarDescendientes(Nodo* nodo) {
    if (nodo == NULL)
        return;
    if (nodo->izquierda != NULL) {
        cout << "Hijo: " << nodo->izquierda->nombre << " (ID: " << nodo->izquierda->ID << ")\n";
        mostrarDescendientes(nodo->izquierda);
    }
    if (nodo->derecha != NULL) {
        cout << "Hijo: " << nodo->derecha->nombre << " (ID: " << nodo->derecha->ID << ")\n";
        mostrarDescendientes(nodo->derecha);
    }
}

// ===== FUNCIONES LLAMADAS DESDE EL MENÚ =====
void insertarMiembro(Nodo*& raiz) {
    Nodo* nuevo = ingresarDatosMiembro();
    raiz = insertar(raiz, nuevo);
}

void buscarMiembro(Nodo* raiz) {
    int id;
    cout << "Ingrese ID a buscar: ";
    cin >> id;
    if (id <= 0) {
        cout << "? ID inválido.\n";
        return;
    }
    Nodo* resultado = buscarPorID(raiz, id);
    mostrarMiembro(resultado);
}

void mostrarParentescos(Nodo* raiz) {
    int id;
    cout << "Ingrese ID para mostrar parentescos: ";
    cin >> id;
    if (id <= 0) {
        cout << "? ID inválido.\n";
        return;
    }

    Nodo* miembro = buscarPorID(raiz, id);
    if (miembro == NULL) {
        cout << "Miembro no encontrado.\n";
        return;
    }

    Nodo* padre = buscarPadre(raiz, id, NULL);
    if (padre != NULL)
        cout << "Padre: " << padre->nombre << " (ID: " << padre->ID << ")\n";
    else
        cout << "No se encontró padre (es la raíz).\n";

    mostrarHijos(raiz, id);
}

void mostrarDescendencia(Nodo* raiz) {
    int id;
    cout << "Ingrese ID para mostrar descendientes: ";
    cin >> id;
    if (id <= 0) {
        cout << "? ID inválido.\n";
        return;
    }

    Nodo* miembro = buscarPorID(raiz, id);
    if (miembro == NULL) {
        cout << "Miembro no encontrado.\n";
        return;
    }

    cout << "Descendientes de " << miembro->nombre << " (ID: " << miembro->ID << "):\n";
    mostrarDescendientes(miembro);
}

// ===== PROGRAMA PRINCIPAL =====
int main() {
    Nodo* raiz = NULL;
    int opcion;

    do {
        cout << "\n===== Menú Árbol Genealógico (ABB) =====\n";
        cout << "1. Insertar nuevo miembro\n";
        cout << "2. Buscar miembro por ID\n";
        cout << "3. Mostrar parentescos (padre e hijos)\n";
        cout << "4. Mostrar descendientes\n";
        cout << "5. Mostrar recorrido Inorden (miembros por ID de manera creciente)\n";
        cout << "6. Mostrar recorrido Preorden (Línea de tiempo de padres a hijos)\n";
        cout << "7. Mostrar recorrido Postorden (Desde más reciente a antiguo)\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: insertarMiembro(raiz); break;
            case 2: buscarMiembro(raiz); break;
            case 3: mostrarParentescos(raiz); break;
            case 4: mostrarDescendencia(raiz); break;
            case 5: cout << "\n--- Recorrido Inorden ---\n"; inorden(raiz); break;
            case 6: cout << "\n--- Recorrido Preorden ---\n"; preorden(raiz); break;
            case 7: cout << "\n--- Recorrido Postorden ---\n"; postorden(raiz); break;
            case 8: cout << "Saliendo del programa...\n"; break;
            default: cout << "? Opción inválida.\n";
        }

    } while (opcion != 8);

    return 0;
}
