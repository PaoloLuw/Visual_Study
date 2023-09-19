
/*El siguiente codigo contiene los 8 ejercicios resueltos, esta en uno solo por que solo 
son funciones que se agregan a nuestra clase ListaEnlazada Gracias*/

#include <iostream>
#include <sqlite3.h> 
using namespace std;
// Definición de la estructura del nodo
struct Node {
    int data;
    Node* next;
    Node* prev;
    
    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

// Definición de la clase ListaEnlazada
class ListaEnlazada {
private:
    Node* head;
    Node* tail; // Puntero final
public:
    ListaEnlazada() : head(nullptr) {} 

    // Método para insertar un elemento al principio de la lista
    void insertarAlPrincipio(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }
    
    // Método para mostrar la lista
    void mostrar() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }

    // Método para buscar un elemento en la lista
    bool buscar(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Método para eliminar un elemento de la lista
    void eliminar(int value) {
        if (head == nullptr) {
            return; // La lista está vacía, no hay nada que eliminar
        }

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        while (current->next != nullptr) {
            if (current->next->data == value) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                return;
            }
            current = current->next;
        }
    }

    // Destructor para liberar la memoria de los nodos
    ~ListaEnlazada() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
//--------------------------------------------------------------------------------------------
    //Ejercicio 1
    void insertarEnPosicion(int value, int posicion) {
    if (posicion < 0) {
        std::cout << "Posición no válida." << std::endl;
        return;
    }

    Node* newNode = new Node(value);

    if (posicion == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        int i = 0;
        while (current != nullptr && i < posicion - 1) {
            current = current->next;
            i++;
        }

        if (current != nullptr) {
            newNode->next = current->next;
            current->next = newNode;
        } else {
            std::cout << "Posición no válida." << std::endl;
            delete newNode; // Liberar la memoria del nodo si no se puede insertar
        }
    }
    }
//--------------------------------------------------------------------------------------------
    //Ejercicio 2
    void eliminarDuplicados() {
    if (head == nullptr) {
        return; // Si esque no hay duplicados para eliminar
    }

    Node* current = head;

    while (current != nullptr) {
        // Compara el valor actual con el valor de los nodos siguientes
        Node* runner = current;
        while (runner->next != nullptr) {
            if (runner->next->data == current->data) {   // Si hay un duplicado, entonces eliminamos el nodo duplicado
                Node* temp = runner->next;
                runner->next = runner->next->next;
                delete temp;
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
    }
//--------------------------------------------------------------------------------------------
    //Ejercicio 3
    void concatenar(ListaEnlazada& segundaLista) {
    if (head == nullptr) {
        head = segundaLista.head;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = segundaLista.head; 
    }
    // limpa la segunda lista la deja vacía
    segundaLista.head = nullptr;
    }
//--------------------------------------------------------------------------------------------
    //Ejercicio 4
    void invertir() {
    if (head == nullptr || head->next == nullptr) {
        // Si está vacía o tiene solo un elemento
        return;
    }
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;

    while (current != nullptr) {
        next = current->next; 
        current->next = prev; 
        prev = current;       
        current = next;       
    }
    head = prev;
}
//--------------------------------------------------------------------------------------------
    //Ejercicio 5
    Node* detectarCiclo() {
    Node* tortuga = head;
    Node* liebre = head;

    //Detección de ciclo
    while (liebre != nullptr && liebre->next != nullptr) {
        tortuga = tortuga->next;
        liebre = liebre->next->next;

        if (tortuga == liebre) {
            //Encuentra el nodo donde comienza el ciclo
            tortuga = head;
            while (tortuga != liebre) {
                tortuga = tortuga->next;
                liebre = liebre->next;
            }
            return tortuga; // Retorna el nodo donde comienza el ciclo
        }
    }
    return nullptr; // No se encontró un ciclo
}
//Necesario Para verificar que nuestra funcion "detectarCiclo()" este funcionando
void crearCiclo(int posicionNodo) {
    // Encuentra el nodo en la posición especificada
    Node* nodoActual = head;
    int contador = 0;

    while (nodoActual != nullptr && contador < posicionNodo) {
        nodoActual = nodoActual->next;
        contador++;
    }

    // Verifica si se encontró un nodo en la posición especificada
    if (nodoActual != nullptr) {
        // Encuentra el último nodo en la lista
        Node* ultimoNodo = head;
        while (ultimoNodo->next != nullptr) {
            ultimoNodo = ultimoNodo->next;
        }

        // Establece el puntero next del último nodo para que apunte al nodo encontrado,
        // creando así un ciclo en la lista
        ultimoNodo->next = nodoActual;
    }
}
//--------------------------------------------------------------------------------------------
    //Ejercicio 6
    void ordenar_Insertar(bool ascending = true) {
        if (head == nullptr || head->next == nullptr) {
            return; // La lista está vacía o tiene un solo elemento, ya está ordenada
        }

        Node* sorted = nullptr;
        Node* current = head;

        while (current != nullptr) {
            Node* next = current->next;

            if (ascending) {
                insertarEnOrdenAscendente(sorted, current);
            } else {
                insertarEnOrdenDescendente(sorted, current);
            }

            current = next;
        }

        head = sorted;
    }
    void insertarEnOrdenAscendente(Node*& sorted, Node* newNode) {
        if (sorted == nullptr || sorted->data >= newNode->data) {
            newNode->next = sorted;
            sorted = newNode;
        } else {
            Node* current = sorted;
            while (current->next != nullptr && current->next->data < newNode->data) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void insertarEnOrdenDescendente(Node*& sorted, Node* newNode) {
        if (sorted == nullptr || sorted->data <= newNode->data) {
            newNode->next = sorted;
            sorted = newNode;
        } else {
            Node* current = sorted;
            while (current->next != nullptr && current->next->data > newNode->data) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }
//--------------------------------------------------------------------------------------------
    //Ejercicio 7
    void insertarAlPrincipio_PListaDble(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        if (head != nullptr) {
            head->prev = newNode;
        }
        head = newNode;
        if (tail == nullptr) {
            tail = head;
        }
    }
     // Método para insertar un elemento al final de la lista es util en estos casos
    void insertarAlFinal(int value) {
        Node* newNode = new Node(value);
        newNode->prev = tail;
        if (tail != nullptr) {
            tail->next = newNode;
        }
        tail = newNode;
        if (head == nullptr) {
            head = tail;
        }
    }
    void mostrarReversa() { //con el puntero alrevez
        Node* current = tail;
        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->prev;
        }
        cout << "nullptr" << endl;
    }
//--------------------------------------------------------------------------------------------
    //Ejercicio 8
    void insertarAlPrincipioListaCircular(int value) {
    Node* newNode = new Node(value);
    
    if (head == nullptr) {
        newNode->next = newNode; 
    } else {
        newNode->next = head; // El nuevo nodo apunta al antiguo inicio de la lista
        Node* current = head;


        while (current->next != head) {
            current = current->next;
        }

        // Hacemos que el último nodo apunte al nuevo nodo
        current->next = newNode;
    }

    head = newNode;
}

    // Método necesario para mostrar la lista circular
    
    void mostrarListaCircular() {
    if (head == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }
    
    Node* current = head;

    do {
        cout << current->data << " -> ";
        current = current->next;
    } while (current != head);

    cout << " (Vuelve al inicio)" << endl;
}
//--------------------------------------------------------------------------------------------
    //Extra OrdenamientoQuiksort funciona solamente con la lista creada como DoblementeEnlazada
    Node* partition(Node* low, Node* high, bool ascending) {
        int pivot = high->data;
        Node* i = low->prev;

        for (Node* j = low; j != high; j = j->next) {
            if ((ascending && j->data <= pivot) || (!ascending && j->data >= pivot)) {
                i = (i == nullptr) ? low : i->next;
                std::swap(i->data, j->data);
            }
        }

        i = (i == nullptr) ? low : i->next;
        std::swap(i->data, high->data);
        return i;
    }

    void quicksort(Node* low, Node* high, bool ascending) {
        if (low != nullptr && high != nullptr && low != high && low != high->next) {
            Node* pivot = partition(low, high, ascending);
            quicksort(low, pivot->prev, ascending);
            quicksort(pivot->next, high, ascending);
        }
    }

    void ordenar_quicksort(bool ascending = true) {
        Node* last = head;
        while (last->next != nullptr) {
            last = last->next;
        }

        quicksort(head, last, ascending);
    }
};
//--------------------------------------------------------------------------------------------
int main() {
    ListaEnlazada lista;

    // Ejercicio 1: Inserción en posición específica  . . .
    cout << endl<< "Ejercicio 1 prueba . . " << endl;
    lista.insertarAlPrincipio(5);
    lista.insertarAlPrincipio(10);
    lista.insertarAlPrincipio(15);
    lista.insertarAlPrincipio(77);
    lista.insertarAlPrincipio(45);
    lista.insertarAlPrincipio(10);
    lista.insertarEnPosicion(7, 1); // Insertar el valor 7 en la posición 1
    lista.mostrar(); // Deve mostrar la lista: 10 -> 7 -> 15 -> 10 -> 45 -> 77 -> 5 -> nullptr

    // Ejercicio 2: Eliminación de duplicados  . . .
    cout << endl<< "Ejercicio 2 prueba . . " << endl;
    lista.eliminarDuplicados();
    lista.mostrar(); // Deve mostrar la lista sin duplicados: 10 -> 7 -> 15 -> 45 -> 77 -> 5 -> nullptr

    // Ejercicio 3: Concatenación de listas  . . .
    cout << endl<< "Ejercicio 3 prueba . . " << endl;
    ListaEnlazada segundaLista;
    segundaLista.insertarAlPrincipio(20);
    segundaLista.insertarAlPrincipio(25);
    lista.concatenar(segundaLista);
    lista.mostrar(); // Deve mostrar la lista concatenada: 10 -> 7 -> 15 -> 45 -> 77 -> 5 -> 25 -> 20 -> nullptr

    // Ejercicio 4: Inversión de una lista  . . .
    cout << endl<< "Ejercicio 4 prueba . . " << endl;
    lista.invertir();
    lista.mostrar(); // Deve mostrar la lista invertida: 20 -> 25 -> 5 -> 77 -> 45 -> 15 -> 7 -> 10 -> nullptr

    // Ejercicio 5: Detectar ciclos  . . .
    cout << endl<< "Ejercicio 5 prueba . . " << endl;
    lista.crearCiclo(5); // Crea un ciclo en la lista de prueba
    Node* cicloStart = lista.detectarCiclo();
    if (cicloStart != nullptr) {
        cout << "La lista contiene un ciclo y comienza en el nodo con valor " << cicloStart->data << endl;
    } else {
        cout << "La lista no contiene ciclos." << endl;
    }

    // Ejercicio 6: Ordenamiento de la lista  . . .
    cout << endl<< "Ejercicio 6 prueba . . " << endl;
    ListaEnlazada OtraLista;
    OtraLista.insertarAlPrincipio(0);
    OtraLista.insertarAlPrincipio(90);
    OtraLista.insertarAlPrincipio(19);
    OtraLista.insertarAlPrincipio(66);
    OtraLista.insertarAlPrincipio(33);
    OtraLista.insertarAlPrincipio(1);

    OtraLista.ordenar_Insertar(); // Orden ascendente por defecto
    OtraLista.mostrar(); // Deve mostrar la lista ordenada en orden ascendente

    OtraLista.ordenar_Insertar(false); // Orden descendente
    OtraLista.mostrar(); // Deve mostrar la lista ordenada en orden descendente

    // Ejercicio 7: Implementación de una lista doblemente enlazada  . . .
    cout << endl<< "Ejercicio 7 prueba . . " << endl;
    ListaEnlazada P_DoblementeEnlazada;
    P_DoblementeEnlazada.insertarAlPrincipio_PListaDble(32);
    P_DoblementeEnlazada.insertarAlPrincipio_PListaDble(44);
    P_DoblementeEnlazada.insertarAlPrincipio_PListaDble(92);
    P_DoblementeEnlazada.insertarAlPrincipio_PListaDble(2);
    P_DoblementeEnlazada.insertarAlPrincipio_PListaDble(45);
    P_DoblementeEnlazada.mostrar();         // Deve mostrar la lista: 45 -> 2 -> 92 -> 44 -> 32 -> nullptr
    P_DoblementeEnlazada.mostrarReversa();  // Deve mostrar la lista: 32 -> 44 -> 92 -> 2 -> 45 -> nullptr
    // Ya hemos implementado una lista doblemente enlazada en la clase ListaEnlazada pero solo se puede usar con "insertarAlPrincipio_PListaDble();"

    // Ejercicio 8: Lista circular  . . .
    cout << endl<< "Ejercicio 8 prueba . . " << endl;
    ListaEnlazada listaCircular;
    listaCircular.insertarAlPrincipioListaCircular(30);
    listaCircular.insertarAlPrincipioListaCircular(35);
    listaCircular.insertarAlPrincipioListaCircular(40);
    listaCircular.mostrarListaCircular(); // Deve mostrar la lista circular y la siguiente lista 40 -> 35 -> 30 ->  (Vuelve al inicio)
    return 0;
}

