#include <iostream>
#include <string>
using namespace std;

// ===== ESTRUCTURA DEL NODO =====
// Define la estructura de un nodo del árbol genealógico.
// Cada nodo representa un miembro con sus datos personales y punteros a sus hijos izquierdo y derecho.
struct Nodo
{
    int ID;                        // Identificador único
    string nombre;                 // Nombre del miembro
    string fechaNacimiento;       // Fecha de nacimiento
    string fechaDefuncion;        // Fecha de defunción (puede ser "-")
    char sexo;                    // 'M' o 'F'
    Nodo* izquierda;              // Puntero al hijo izquierdo
    Nodo* derecha;                // Puntero al hijo derecho
};

// ===== FUNCIONES PARA CREAR E INGRESAR MIEMBROS =====

// Crea un nuevo nodo con los datos proporcionados
Nodo* crearNodo(int ID, string nombre, string nacimiento, string defuncion, char sexo)
{
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

// Solicita al usuario los datos de un nuevo miembro y retorna el nodo creado
Nodo* ingresarDatosMiembro()
{
    int id;
    string nombre, nacimiento, defuncion;
    char sexo;

    cout << "ID: ";
    cin >> id;
    cout << "Nombre (una palabra): ";
    cin >> nombre;
    cout << "Fecha de nacimiento: ";
    cin >> nacimiento;
    cout << "Fecha de defuncion (o '-' si no aplica): ";
    cin >> defuncion;
    cout << "Sexo (M/F): ";
    cin >> sexo;

    return crearNodo(id, nombre, nacimiento, defuncion, sexo);
}

// ===== OPERACIONES DEL ÁRBOL BINARIO DE BÚSQUEDA =====

// Busca un nodo por su ID de forma recursiva
Nodo* buscarPorID(Nodo* raiz, int IDbuscado)
{
    if (raiz == NULL || raiz->ID == IDbuscado)
        return raiz;
    if (IDbuscado < raiz->ID)
        return buscarPorID(raiz->izquierda, IDbuscado);
    else
        return buscarPorID(raiz->derecha, IDbuscado);
}

// Inserta un nuevo nodo al árbol de forma ordenada por ID
Nodo* insertar(Nodo* raiz, Nodo* nuevo)
{
    if (buscarPorID(raiz, nuevo->ID) != NULL)
	{
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

// ===== RECORRIDOS DEL ÁRBOL =====

// Recorrido inorden: Izquierda - Raíz - Derecha (muestra miembros ordenados por ID)
void inorden(Nodo* raiz)
{
    if (raiz != NULL)
	{
        inorden(raiz->izquierda);
        cout << raiz->ID << " - " << raiz->nombre << endl;
        inorden(raiz->derecha);
    }
}

// Recorrido preorden: Raíz - Izquierda - Derecha
void preorden(Nodo* raiz)
{
    if (raiz != NULL)
	{
        cout << raiz->ID << " - " << raiz->nombre << endl;
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

// Recorrido postorden: Izquierda - Derecha - Raíz
void postorden(Nodo* raiz)
{
    if (raiz != NULL) {
        postorden(raiz->izquierda);
        postorden(raiz->derecha);
        cout << raiz->ID << " - " << raiz->nombre << endl;
    }
}

// ===== FUNCIONES AUXILIARES PARA CONSULTAS =====

// Muestra todos los datos de un miembro
void mostrarMiembro(Nodo* nodo)
{
    if (nodo != NULL)
	{
        cout << "\n--- Miembro encontrado ---\n";
        cout << "ID: " << nodo->ID << endl;
        cout << "Nombre: " << nodo->nombre << endl;
        cout << "Nacimiento: " << nodo->fechaNacimiento << endl;
        cout << "Defuncion: " << nodo->fechaDefuncion << endl;
        cout << "Sexo: " << nodo->sexo << endl;
    } else {
        cout << "Miembro no encontrado.\n";
    }
}

// Busca al padre de un nodo dado, retornando el puntero al padre
Nodo* buscarPadre(Nodo* raiz, int id, Nodo* padre)
{
    if (raiz == NULL)
        return NULL;
    if (raiz->ID == id)
        return padre;
    if (id < raiz->ID)
        return buscarPadre(raiz->izquierda, id, raiz);
    else
        return buscarPadre(raiz->derecha, id, raiz);
}

// Muestra los hijos de un miembro (si existen)
void mostrarHijos(Nodo* raiz, int id)
{
    if (raiz == NULL)
        return;
    if (raiz->ID == id)
	{
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

// Muestra todos los descendientes de un nodo de forma recursiva
void mostrarDescendientes(Nodo* nodo)
{
    if (nodo == NULL)
        return;
    if (nodo->izquierda != NULL)
	{
        cout << "Hijo: " << nodo->izquierda->nombre << " (ID: " << nodo->izquierda->ID << ")\n";
        mostrarDescendientes(nodo->izquierda);
    }
    if (nodo->derecha != NULL)
	{
        cout << "Hijo: " << nodo->derecha->nombre << " (ID: " << nodo->derecha->ID << ")\n";
        mostrarDescendientes(nodo->derecha);
    }
}

// ===== FUNCIONES LLAMADAS DESDE EL MENÚ =====

// Llama al ingreso de datos y los inserta en el árbol
void insertarMiembro(Nodo*& raiz)
{
    Nodo* nuevo = ingresarDatosMiembro();
    raiz = insertar(raiz, nuevo);
}

// Solicita un ID y busca un miembro para mostrar sus datos
void buscarMiembro(Nodo* raiz)
{
    int id;
    cout << "Ingrese ID a buscar: ";
    cin >> id;
    Nodo* resultado = buscarPorID(raiz, id);
    mostrarMiembro(resultado);
}

// Muestra el padre y los hijos de un miembro dado su ID
void mostrarParentescos(Nodo* raiz)
{
    int id;
    cout << "Ingrese ID para mostrar parentescos: ";
    cin >> id;

    Nodo* miembro = buscarPorID(raiz, id);
    if (miembro == NULL)
	{
        cout << "Miembro no encontrado.\n";
        return;
    }

    Nodo* padre = buscarPadre(raiz, id, NULL);
    if (padre != NULL)
        cout << "Padre: " << padre->nombre << " (ID: " << padre->ID << ")\n";
    else
        cout << "No se encontró padre (posiblemente es la raíz).\n";

    mostrarHijos(raiz, id);
}

// Muestra todos los descendientes (hijos, nietos, etc.) de un miembro
void mostrarDescendencia(Nodo* raiz)
{
    int id;
    cout << "Ingrese ID para mostrar descendientes: ";
    cin >> id;

    Nodo* miembro = buscarPorID(raiz, id);
    if (miembro == NULL) {
        cout << "Miembro no encontrado.\n";
        return;
    }

    cout << "Descendientes de " << miembro->nombre << " (ID: " << miembro->ID << "):\n";
    mostrarDescendientes(miembro);
}

// ===== PROGRAMA PRINCIPAL =====
int main()
{
    Nodo* raiz = NULL;  // Raíz del árbol genealógico
    int opcion;         // Opción seleccionada por el usuario

    do {
        // Menú principal
        cout << "\n===== Menu Árbol Genealógico (ABB) =====\n";
        cout << "1. Insertar nuevo miembro\n";
        cout << "2. Buscar miembro por ID\n";
        cout << "3. Mostrar recorrido Inorden\n";
        cout << "4. Mostrar parentescos (padre e hijos)\n";
        cout << "5. Mostrar descendientes\n";
        cout << "6. Mostrar recorrido Preorden\n";
        cout << "7. Mostrar recorrido Postorden\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        // Evaluación de opciones
        switch (opcion)
		{
            case 1: insertarMiembro(raiz); break;
            case 2: buscarMiembro(raiz); break;
            case 3: cout << "\n--- Recorrido Inorden ---\n"; inorden(raiz); break;
            case 4: mostrarParentescos(raiz); break;
            case 5: mostrarDescendencia(raiz); break;
            case 6: cout << "\n--- Recorrido Preorden ---\n"; preorden(raiz); break;
            case 7: cout << "\n--- Recorrido Postorden ---\n"; postorden(raiz); break;
            case 8: cout << "Saliendo del programa...\n"; break;
            default: cout << "Opción inválida.\n";
        }

    } while (opcion != 8);  // El programa continúa hasta que se elija salir

    return 0;
}
