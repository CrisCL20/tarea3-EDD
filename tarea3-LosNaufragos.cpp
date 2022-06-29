#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

void printgraph(ptg);
bool contains(string, char);

int main(int argc, char* argv[]){
    (void)argc;
    string line; 
	//vector<string> description;
	string desc = "";
    //ptg graph = new grafo;
    ifstream file(argv[1]);
    

    if(!file.is_open()) exit(EXIT_FAILURE);
    while(file.peek()!=EOF){
        getline(file,line);
	if(!contains(line,'-') && line.size()>N/100) desc += line;
	}
}

bool contains(string s, char c){
	if(s.find(c) != string::npos) return true;
	return false;
}


