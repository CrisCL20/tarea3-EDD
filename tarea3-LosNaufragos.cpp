#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct grafo{ 
              string nodo;
              string aventura;
              string descripcion;
              string* decisiones;
              int cantidad_caminos;
              bool gameover; 
              grafo** opciones; };
typedef grafo* ptg;

int main(int argc, char* argv[]){
    (void)argc;
    ifstream file(argv[1]);
    string line;
    ptg graph = new grafo;
    if(!file.is_open()) exit(EXIT_FAILURE);
    while(file.peek()!=EOF){
        getline(file,line);
        if(line=="-") continue;
        else if(line.size()>=50) graph->descripcion=line;
    }

}

ptg crearnodo(string desc_nodo){
    ptg aux = new grafo;
    aux->descripcion=desc_nodo;
    aux->decisiones = NULL;
    aux->opciones=NULL;
    return aux;
}

void agregarcaminos(ptg &nodo, int cantidad, string* desc,string* deci){
    nodo->decisiones=deci;
    nodo->cantidad_caminos=cantidad;
    ptg* lista_opciones = new ptg[cantidad]; 
    for(int i=0;i<cantidad;i++){
        crearnodo(desc[i]);
    }
    nodo->opciones=lista_opciones;
}

void escoger_camino(ptg nodo){
    cout << nodo->descripcion << endl;
    for (int i = 0; i < nodo->cantidad_caminos; i++) cout << i++ << ") " << nodo->decisiones[i]<<endl;
    if(nodo->opciones==NULL){
        string x;
        cin >> x;
    }
    else{
        int camino;
        cin >> camino;
        escoger_camino(nodo->opciones[camino]);
    }
    if(nodo->gameover) return;
    
}