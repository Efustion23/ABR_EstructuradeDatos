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

// Mostrar menú de opciones
void mostrarMenu() {
cout << "\n===== Menú Árbol Genealógico =====" << endl;
cout << "1. Insertar miembro" << endl;
cout << "2. Mostrar árbol (Inorden)" << endl;
cout << "3. Buscar miembro por ID" << endl;
cout << "4. Salir" << endl;
cout << "Seleccione una opción: ";
}

// Función principal
int main() {
Nodo* raiz = NULL;
int opcion;
do {
    mostrarMenu();
    cin >> opcion;
    cin.ignore(); // Limpia salto de línea en buffer

    switch(opcion) {
        case 1: {
            int id;
            string nombre, nacimiento, defuncion;
            char sexo;

            cout << "ID: ";
            cin >> id;
            cin.ignore();

            cout << "Nombre completo: ";
            getline(cin, nombre);

            cout << "Fecha de nacimiento: ";
            getline(cin, nacimiento);

            cout << "Fecha de defuncion (si aplica): ";
            getline(cin, defuncion);

            cout << "Sexo (M/F): ";
            cin >> sexo;
            cin.ignore();

            Nodo* nuevo = new Nodo(id, nombre, nacimiento, defuncion, sexo);
            raiz = insertar(raiz, nuevo);
            break;
        }

        case 2:
            cout << "\nMiembros registrados (Inorden):\n";
            inorden(raiz);
            break;

        case 3: {
            int idBuscar;
            cout << "Ingrese ID a buscar: ";
            cin >> idBuscar;

            Nodo* resultado = buscarPorID(raiz, idBuscar);
            if (resultado != NULL) {
                cout << "Miembro encontrado:\n";
                cout << "Nombre: " << resultado->nombre << endl;
                cout << "Nacimiento: " << resultado->fechaNacimiento << endl;
                cout << "Defuncion: " << resultado->fechaDefuncion << endl;
                cout << "Sexo: " << resultado->sexo << endl;
            } else {
                cout << "No se encontró un miembro con ese ID.\n";
            }
            break;
        }

        case 4:
            cout << "Saliendo del programa..." << endl;
            break;

        default:
            cout << "Opción inválida. Intente nuevamente.\n";
    }

} while (opcion != 4);

return 0;
}
