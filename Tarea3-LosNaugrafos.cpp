#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
using namespace std;


struct Nodo
{
	int clave;
	string claveSala;
	string descripcion;
	Nodo* derecha;
	Nodo* izquierda;
	Nodo(int clave, string claveSala, string descripcion) : clave(clave), claveSala(claveSala),
		descripcion(descripcion), derecha(NULL), izquierda(NULL) {}
};
struct Grafo
{
	Nodo* raiz;
	Grafo() : raiz(NULL) {};
	void agregarNodo(int clavePadre, int clave, string claveSala, string descripcion)
	{
		Nodo* nuevoNodo = new Nodo(clave, claveSala, descripcion);
		if (!this->raiz)
		{
			this->raiz = nuevoNodo;
			return;
		}
		this->agregarNodoRecursivo(nuevoNodo, this->raiz, clavePadre);
	}
	Nodo* obtenerNodo(string claveSala)
	{
		if (!this->raiz) return NULL;
		Nodo* nodoBuscado = new Nodo(-1, "", "");
		this->obtenerNodoRecursivo(this->raiz, claveSala, *nodoBuscado);
		return (*nodoBuscado).clave == -1 ? NULL : nodoBuscado;
	}
	private:

		void agregarNodoRecursivo(Nodo* nuevoNodo, Nodo* raiz, int clavePadre)
		{
			if (!raiz) return;
			agregarNodoRecursivo(nuevoNodo, raiz->izquierda, clavePadre);
			agregarNodoRecursivo(nuevoNodo, raiz->derecha, clavePadre);
			if (raiz->clave == clavePadre)
			{
				if (!raiz->izquierda) raiz->izquierda = nuevoNodo;
				else if (!raiz->derecha) raiz->derecha = nuevoNodo;
				return;
			}
		}
		void obtenerNodoRecursivo(Nodo* raiz, string claveSala, Nodo& nodoBuscado)
		{
			if (!raiz) return;

			if (raiz->claveSala == claveSala)
			{
				nodoBuscado = *raiz;
				return;
			}
			if (raiz->derecha) this->obtenerNodoRecursivo(raiz->derecha, claveSala, nodoBuscado);
			if (raiz->izquierda) this->obtenerNodoRecursivo(raiz->izquierda, claveSala, nodoBuscado);
		}

};
struct Sistema
{
	Grafo* grafo;
	Sistema() : grafo(new Grafo()) {};
	void inicializacion()
	{
		this->leerArchivo();
		this->iniciarJuego();
	}
	private:
		void leerArchivo()
		{
			int clave = 1;
			ifstream archivo("Input.txt");
			string clavePadre = "";
			while (getline(archivo, clavePadre))
			{
				int numeroClavePadre = 0;
				string claveSala, descripcion, actualLineaDescripcion;

				if (clavePadre != "START")
				{
					std::istringstream(clavePadre) >> numeroClavePadre;
				}
				getline(archivo, claveSala);
				while (1)
				{
					getline(archivo, actualLineaDescripcion);
					if (actualLineaDescripcion == "-")
					{
						break;
					}
					descripcion += actualLineaDescripcion + "\n";
				}
				grafo->agregarNodo(numeroClavePadre, clave, claveSala, descripcion);
				clave++;
			}
			archivo.close();
		}
		void iniciarJuego()
		{
			while (1)
			{
				system("clear");
				Nodo* nodoJuego = this->grafo->obtenerNodo("				----HENRY----");
				string despliegue = "				----HENRY----\n" + nodoJuego->descripcion + "\n\n";
				string claveSala = this->nuevaClaveSala(nodoJuego, despliegue);
				while (claveSala != "")
				{
					nodoJuego = this->grafo->obtenerNodo(claveSala);
					despliegue = nodoJuego->descripcion + "\n\n";
					claveSala = this->nuevaClaveSala(nodoJuego, despliegue);
				}
			}
		}
		string nuevaClaveSala(Nodo* raiz, string despliegue)
		{
			string opcion = "";
			if (raiz->derecha && raiz->izquierda)
			{
				while (opcion != "1" && opcion != "2")
				{
					system("cls");
					cout << despliegue;
					cout << "1 - " << raiz->izquierda->claveSala << "\n";
					cout << "2 - " << raiz->derecha->claveSala << "\n";
					getline(cin, opcion);
				}
				if (opcion == "1")
				{
					return raiz->izquierda->claveSala;
				}
				return raiz->derecha->claveSala;
			}
			if (raiz->izquierda)
			{
				while (opcion != "1")
				{
					system("clear");
					cout << despliegue;
					cout << "1 - " << raiz->izquierda->claveSala << "\n";
					getline(cin, opcion);
				}
				return raiz->izquierda->claveSala;
			}
			if (raiz->derecha)
			{
				while (opcion != "1")
				{
					system("clear");
					cout << despliegue;
					cout << "1 - " << raiz->derecha->claveSala << "\n";
					getline(cin, opcion);
				}
				return raiz->derecha->claveSala;
			}
			system("clear");
			cout << despliegue;
			system("pause");
			return opcion;
		}
};
int main()
{
	setlocale(LC_ALL, "es_ES");
	Sistema* sistema = new Sistema();
	sistema->inicializacion();
	delete sistema;
	return 0;
}
