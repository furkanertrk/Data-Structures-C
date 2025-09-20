#include <iostream>
#include <clocale>
using namespace std;

int dizi[2];
int tepe=0;
int boyut=2;


int pop(){
	return dizi[--tepe];
}
void push(int a){
	dizi[tepe++]=a;
}
void bastir(){
	for(int i=0;i<tepe;i++){
		printf("%d ",dizi[i]);
	}
}





int main(){
	push(10);
	push(20);
	bastir();
	
	
	return 0;
}
