#include  <iostream>
#include <string.h>
#include<unistd.h>



using namespace std;


const int size = 128;

struct letraSim{
	char sim;
	float prob;
    int top=-1;
    int cod[20];
};

letraSim *letra = new letraSim[size];

int TamanoEntrada(char []);
void Probabilidad(char let, string E, float largo, int pos, int c);
bool Existe(char l, string E, int pos);
void Quicksort( int start, int end );
int Divide( int start, int end );
void imprimirDatos(int c, int largo);
void shannon(int l, int h);
void display(int n);
//void imprimirShannon(int c);

int main(){
    string Entrada; 
    int contador = 0;
    Entrada = "ABCCDDDBM";
    float largo = Entrada.size();
    for (int i=0; i<=largo; i++){
        if (Existe(Entrada[i], Entrada, i) == false){
            Probabilidad(Entrada[i], Entrada, largo, i, contador);
            contador = contador+1;
            
        }
    }
    
    Quicksort(0,contador-1);
    imprimirDatos(contador, largo);
    
  
    shannon(0, contador-1);
    //cout<<"c = "<<contador;
    display(contador);
    //cout<<"frecuencia: "<<letra[0].prob<<" letra: "<<letra[0].sim;
    //cout<<" ";
    return 0;
}

void Probabilidad(char let, string E, float largo, int pos, int posreg){
    float prob;
    float c = 0;
    while(pos<=largo){
        if (let == E[pos]){
            c=c+1;
        }
        pos = pos+1;
    }
    prob = c/largo;
    //cout<<"c: "<< c<< " ||";
    letra[posreg].sim = let; 
    letra[posreg].prob = prob;
    //cout<<"frecuencia: "<<letra[posreg].prob<<" letra: "<<letra[posreg].sim;
    cout<<" ";
}

bool Existe(char l, string E, int pos){
    int posi = pos;
    bool ex;
    while (0<=posi){
        posi=posi-1;
        if (E[posi]==E[pos]){
            ex=true;
            return ex;
            break;
        }
    }
    if (posi == 0){
        ex=false;
        return ex;
    }
    else{
        return false;
    }
}

void Quicksort( int start, int end ){
    int pivot;
    cout<<"end: "<<end;
 
    if (start < end) {
        pivot = Divide( start, end );
 
        Quicksort( start, pivot - 1 );
        Quicksort( pivot + 1, end);
    }
}
 
int Divide( int start, int end ) {
    int left;
    int right;
    float pivot;
    letraSim temp;
     cout<<"end: "<<end;
 
    pivot = letra[start].prob;
    left = start;
    right = end;
 
    while (left < right) {
        while (letra[right].prob > pivot) {
            right--;
            //cout<<"en while: "<<letra[right].prob;
        }
 
        while ((left < right) && (letra[left].prob <= pivot)) {
            left++;
        }
        if (left < right) {
            temp = letra[left];
            letra[left] = letra[right];
            letra[right] = temp;
        }
    }
    temp = letra[right];
    letra[right] = letra[start];
    letra[start] = temp;
 
    return right;
}

void imprimirDatos(int c, int largo){
 
    for( int i = 0; i < c; i++ ) {
 
		cout  <<i
              << "\n"<< letra[i].sim<<" "
            
             << "Probabilidad: " << letra[i].prob
             << "Cantidad de apariciones "<< letra[i].prob*largo<< endl;
	}
}

void shannon(int l, int h) 
{   
    
	float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0; 
	int i, d, k, j; 
    
    cout<<"l = "<<l<<endl;
    cout<<"h = "<<h<<endl;
	if ((l + 1) == h || l == h || l > h) { 
		if (l == h || l > h) 
			return; 
		letra[h].cod[++(letra[h].top)] = 0; 
		letra[l].cod[++(letra[l].top)] = 1; 
		return; 
	} 
	else { 
		for (i = l; i <= h - 1; i++) 
			pack1 = pack1 + letra[i].prob; 
		pack2 = pack2 + letra[h].prob; 
		diff1 = pack1 - pack2; 
		if (diff1 < 0) 
			diff1 = diff1 * -1; 
		j = 2; 
		while (j != h - l + 1) { 
			k = h - j; 
			pack1 = pack2 = 0; 
			for (i = l; i <= k; i++) 
				pack1 = pack1 + letra[i].prob; 
			for (i = h; i > k; i--) 
				pack2 = pack2 + letra[i].prob; 
			diff2 = pack1 - pack2; 
			if (diff2 < 0) 
				diff2 = diff2 * -1; 
			if (diff2 >= diff1) 
				break; 
			diff1 = diff2; 
			j++; 
		} 
		k++; 
		for (i = l; i <= k; i++) 
			letra[i].cod[++(letra[i].top)] = 1; 
            cout<<"letra[i].cod = "<<letra[i].cod[(letra[i].top)]<<endl;
		for (i = k + 1; i <= h; i++) 
			letra[i].cod[++(letra[i].top)] = 0; 
            cout<<"con 0 letra[i].cod = "<<letra[i].cod[(letra[i].top)]<<endl;

		// Invoke shannon function 
		shannon(l, k); 
		shannon(k + 1, h); 
	} 
} 
/*void imprimirShannon(int c){

    for( int i = 0; i < c; i++ ) {
 
		cout << "\n"<< letra[i].sim<<" "
             << "Probabilidad: " << letra[i].prob<< endl
             <<"Codigo: ";
             for(int j=0; j<=20;j++){
             cout<< letra[i].cod[j];
             }
        cout <<"\n";
	}
}*/
   
void display(int n) 
{ 
	int i, j; 
	cout << "\n\n\n\tSymbol\tProbability\tCode"; 
	for (i = n-1; i >=0; i--) { 
		cout << "\n\t" << letra[i].sim << "\t\t" << letra[i].prob << "\t"; 
		for (j = 0; j <= letra[i].top; j++) 
			cout << letra[i].cod[j]; 
	} 
} 

