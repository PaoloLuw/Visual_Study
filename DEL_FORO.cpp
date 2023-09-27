#include <iostream>

#include <cstdlib>

#include <ctime>

using namespace std;

//const int NUMNODOS = 10;

const int INFINITO = -777;

class Nodo {

public:

 int info;

 int sig;

public:

 Nodo() : info(INFINITO), sig(-1) {}

 

};

class ListaEnlazada {

private:

 

 Nodo nodos[100];

 int NUMNODOS;

 int disponible;

 int bottom;

public:

 ListaEnlazada(const int NUMNODOS=10) : disponible(NUMNODOS), bottom(NUMNODOS - 1), NUMNODOS(NUMNODOS) {}

 

 void iniciarLista(bool IniciarAtributos=true) {

 for (int i = 0; i < NUMNODOS; i++) {

 nodos[i].sig = i + 1;

 

 nodos[i].info = INFINITO;

 }

 nodos[NUMNODOS - 1].sig = -1;

 if(IniciarAtributos==true){

    for (int i = 0; i < NUMNODOS; i++) {

        int valorAleatorio = rand() % 100;

        insertarNodo(valorAleatorio);

    }

 }

 }

 int obtenerNodo() {

 int p = 0;

 if (!disponible) {

 return -1;

 }

 --disponible;

 while (nodos[p].info != INFINITO)

 p++;

 return (p);

 }

 void liberarNodo(int p) {

 nodos[p].info = INFINITO;

 nodos[p].sig = -1;

 bottom = p;

 ++disponible;

 }

 void insertarNodo(int x, bool insertadoEspacial=false) {

 int q;

 q = obtenerNodo();

 if (q == -1) {

 cout << "Insercion no efectuada ...!" << endl;

 return;

 }

 

 nodos[q].info = x;

 if(insertadoEspacial==true){

    for(int i=q;i<NUMNODOS;i++){

        if(nodos[i].sig!=-1){

            nodos[q].sig=i;break;

        }

    }

    if(nodos[q-1].sig!=-1)nodos[q-1].sig=q;

 }

 

 }

 void imprimirLista() {

 cout << "\nLa lista creada es: " << endl;

 cout << "\tindice\tinfo\tsiguiente: " << endl;

 for (int i = 0; i < NUMNODOS; i++)

 cout << "Indice " << i << " :\t" << nodos[i].info << "\t" << nodos[i].sig << "\t"<< endl;

 cout << endl << "Presione una tecla para continuar. . . ";

 getchar();

 }

 int obtenerBottom() {

 return bottom;

 }

 Nodo obtenerNodo(int indice) {

 if (indice >= 0 && indice < NUMNODOS) {

 return nodos[indice];

 } else {

 Nodo nodoVacio;

 return nodoVacio;

 }

 }

 bool buscarNodo(int valor) {

 for (int i = 0; i < NUMNODOS; i++) {

 if (nodos[i].info == valor) {

 return true;

 }

 }

 return false;

 }

 

 void eliminarNodo(int px) {

 int p = 0;

 int q = nodos[p].sig;

 if (nodos[p].info == px) {

 int nuevoBottom = nodos[p].sig;

 liberarNodo(p);

 bottom = nuevoBottom;

 

 return;

 }

 while (q != -1) {

 if (nodos[q].info == px) {

 nodos[p].sig = nodos[q].sig;

 liberarNodo(q);

 return;

 }

 p = q;

 

 q = nodos[q].sig;

 }

 cout << "No se encontró un nodo con el valor " << px << " para eliminar" << endl;

 }

 int retornarSize(){

    return NUMNODOS;

 }

 int InfodemiNodo(int pos){

    return nodos[pos].info;

 }

 

 void ordenarLista(){//de menor a mayor

    bool swapped;   

    for (int i = 0; i < NUMNODOS - 1; i++) {

        swapped = false;

        // Últimos i elementos ya están en su lugar

        for (int j = 0; j < NUMNODOS - i - 1; j++) {

            if(nodos[j].info != INFINITO && nodos[j+1].info != INFINITO){

                if (nodos[j].info > nodos[j+1].info) {

                     

                    int temp = nodos[j].info;

                    nodos[j].info = nodos[j+1].info;;

                    nodos[j+1].info = temp;

                    swapped = true;

              }

            }

        }

 

 

        if (!swapped) {

            break;

        }

    }

}

 ListaEnlazada operator +(ListaEnlazada& otraLista ){

 

    int SizeDeLasListas=this->retornarSize() + otraLista.retornarSize();

    ListaEnlazada Uniendo(SizeDeLasListas);

    Uniendo.iniciarLista(false);

 

    for (int i = 0; i < this->retornarSize(); i++){

    this[i];

    Uniendo.insertarNodo(this->InfodemiNodo(i));

    }

   

    for (int i = 0; i < otraLista.retornarSize(); i++){

    Uniendo.insertarNodo(otraLista.InfodemiNodo(i));

    }

    return Uniendo;

 }

 

 void fusionarListas(ListaEnlazada& otraLista ){

    int SizeDeLaNewLista = otraLista.retornarSize();

    this->NUMNODOS+=SizeDeLaNewLista;

    disponible=SizeDeLaNewLista;

    for (int i = 0; i < otraLista.retornarSize(); i++){

    this->insertarNodo(otraLista.InfodemiNodo(i));

    }

 }

 

};

 

int main() {

 srand(static_cast<unsigned>(time(nullptr)));

 

//--------------------------------------------------------------------------------------------

 ListaEnlazada lista0(20);

 lista0.iniciarLista();

 lista0.imprimirLista();

 

 ListaEnlazada lista(12);

 lista.iniciarLista();

 lista.imprimirLista();

 

//--------------------------------------------------------------------------------------------

 /*

 int bottomValue = lista.obtenerBottom();

 Nodo bottomNodo = lista.obtenerNodo(bottomValue); */

 // cout << "\nIndice " << bottomValue << " :\t" << bottomNodo.info << "\t" << bottomNodo.sig<< "\t" << endl;

 

//--------------------------------------------------------------------------------------------

int Quenodoelimino; cout<<endl<<"Digite el nodo que decea eliminar: ";

cin>>Quenodoelimino;

lista.eliminarNodo(Quenodoelimino);

cout << "\nLa lista después de eliminar el nodo con valor "<<Quenodoelimino<<" es: " << endl;

lista.imprimirLista();

//--------------------------------------------------------------------------------------------

int buscandoMyNodo;

cout<<endl<<"Digite el nodo que esta buscando: "; cin>>buscandoMyNodo;

 if (lista.buscarNodo(buscandoMyNodo))

 cout << "Se encontró un nodo con el valor " << buscandoMyNodo << endl;

 else

 cout << "No se encontró un nodo con el valor " << buscandoMyNodo << endl;

//--------------------------------------------------------------------------------------------

 int insertarMiNodo;

 cout<<endl<<"Digite el nodo que decea insertar: "; cin>>insertarMiNodo;

 lista.insertarNodo(insertarMiNodo, true);

 lista.imprimirLista();

//--------------------------------------------------------------------------------------------

 cout<<endl<<"Presione una tecla para ordenar esta lista. . . "<<endl;

 cin.get();

 lista.ordenarLista();

 cout<<endl<<"Lista ordenada ! ..."<<endl;

 lista.imprimirLista();

 

//--------------------------------------------------------------------------------------------

 

ListaEnlazada ConOperadores;

cout<<endl<<"Uniendo lista con sobrecarga de operadores";

ConOperadores=lista+lista0;//uniendo en "ConOperadores"

ConOperadores.imprimirLista();

cout<<endl<<"imprimiendo la lista unida y ordenada . .  "<<endl;

ConOperadores.ordenarLista();

ConOperadores.imprimirLista();

 cin.get();

//--------------------------------------------------------------------------------------------

 

ListaEnlazada SinOperadores;

SinOperadores.iniciarLista();

SinOperadores.imprimirLista();

cout<<endl<<"Uniendo lista sin sobrecarga de operadores";

SinOperadores.fusionarListas(lista);//uniendo en "SinOperadores"

ConOperadores.imprimirLista();

cout<<endl<<"imprimiendo la lista unida y ordenada . .  "<<endl;

SinOperadores.ordenarLista();

SinOperadores.imprimirLista();

 cin.get();

 

cout << "\nPresione una tecla para finalizar. . . ";

 cin.get();

 return 0;

}