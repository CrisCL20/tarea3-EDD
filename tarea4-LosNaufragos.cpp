#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

void limpiar(vector<int> &arr){
    vector<int>().swap(arr);
}

vector<int> hubert_read(ifstream &file){
    vector<int> arr;
    if(!file.is_open()) exit(1);
    else{
        int i;
        while(file>>i) arr.push_back(i);
    }
    return arr;
}

void hubert_write(vector<int> arr, int i){//i = {1,2}
    ofstream output("output_"+to_string(i)+".hubert");
    for(int n:arr){
        output << n << endl;
    } 
    output.close();
}

void swap(int *a,int *b){
    int aux=*a;
    *a=*b;
    *b=aux;
}

void selection_sort(vector<int> &arr){
    long unsigned int n = arr.size(); int min;
    for(long unsigned int i=0;i<n-1;i++){
        min=i;
        for(long unsigned int j=i+1;j<n;j++){
            if(arr[j]<arr[min]) min=j;
            swap(&arr[i],&arr[min]);
        }
    }
}

int pivote(int l, int r){
    int p=rand()%(r-l+1);
    return l+p;
}

int part(vector<int> arr,int l, int h){
    int p=pivote(l,h);
    int i=(l-1);
    for(int j=l;j<=h-1;j++){
        if(arr[j]<p){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[h]);
    return (i+1);
}

void quick_sort(vector<int> &arr,int l, int h){
    if(l<h){
        int p=part(arr,l,h);
        quick_sort(arr,l,p-1);
        quick_sort(arr,p+1,h);
    }
}

int main(int argc, char* argv[]){
    (void) argc;
    ifstream file1(argv[1]);
    ifstream file2(argv[1]);
    
    vector<int> arreglo1 = hubert_read(file1);
    vector<int> arreglo2 = hubert_read(file2);

    auto inicio=high_resolution_clock::now();

    selection_sort(arreglo1);
    hubert_write(arreglo1,1);
    limpiar(arreglo1);

    auto final = high_resolution_clock::now();
    auto delta = duration_cast<microseconds>(final-inicio);
    file1.close();

    cout << "Archivo 1 creado en " << delta.count() << " microsegundos" << endl;

    inicio=high_resolution_clock::now();

    int n=arreglo2.size();
    quick_sort(arreglo2,0,n-1);
    hubert_write(arreglo2,2);
    limpiar(arreglo2);

    final=high_resolution_clock::now();
    delta=duration_cast<microseconds>(final-inicio);
    file2.close();

    cout << "Archivo 2 creado en " << delta.count() << " microsegundos" << endl;

}