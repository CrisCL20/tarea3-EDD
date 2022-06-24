#include <iostream>
#include <fstream>

using namespace std;

struct nodo{ string data; nodo* sig; };
typedef nodo* ptn;

struct arco{ ptn u,v; };
typedef arco* pta;

pta crear_arco(ptn,ptn);
void printarco(pta);

int main(int argc, char* argv[]){
	int n; //
	(void)argc;
	char **input=new char[n];
	ptn node = new nodo;
	pta edge = new arco;
	ifstream file(argv[1]);	
	if(!file.is_open()) exit(EXIT_FAILURE);
	while(file >> input){
	}

}

pta crear_arco(ptn nodo1, ptn nodo2){
	pta arc = new arco;
	while(nodo1!=NULL && nodo2!=NULL){
		nodo1->sig=nodo2;
		arc->u=nodo1;
		arc->v=nodo2;
	}
	return arc;
}

void printarco(pta arc){
	while(arc!=NULL) cout << arc->u->data << " " << arc->v->data << endl;
}
