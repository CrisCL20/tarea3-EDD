#include <iostream>
#include <fstream>
#include <string>
#define N 1000

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
    string line; 
    string description="";
    int n=line.size();
    
    ptg graph = new grafo;
    
    ifstream file(argv[1]);
    

    if(!file.is_open()) exit(EXIT_FAILURE);
    while(file.peek()!=EOF){
        getline(file,line);
        if(line=="-") continue;
        else if(n>=50){
            for(int i=0;i<N;i++) description += line;
            graph->descripcion=description;
        }
        else if(n<50 && n>15) graph->aventura=line;
        else if(line=="START" || n==1) graph->nodo=line;
    }

}

ptg crearnodo(ptg &graph,string desc_nodo){
    graph->descripcion=desc_nodo;
    graph->decisiones = NULL;
    graph->opciones=NULL;
    return graph;
}

void agregarcaminos(ptg &nodo, int cantidad, string* desc,string* deci){
    nodo->decisiones=deci;
    nodo->cantidad_caminos=cantidad;
    ptg* lista_opciones = new ptg[cantidad]; 
    for(int i=0;i<cantidad;i++){
        crearnodo(nodo, desc[i]);
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