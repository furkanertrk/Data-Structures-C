#include <stdio.h>
#include <stdlib.h>

int *dizi;
int tepe=0;
int boyut=2;


int pop(){
		if(tepe<=boyut/4){
		int *dizi2 = (int*)malloc(sizeof(int) * boyut / 2);  
   
    for (int i = 0; i < boyut; i++) 
        dizi2[i] = dizi[i];
    
	free(dizi);
	dizi = dizi2;
    boyut /= 2;  
	}
	return dizi[--tepe];
}
void push(int a){
	if(tepe>=boyut){
		int *dizi2 = (int*)malloc(sizeof(int) * boyut * 2);  
   
    for (int i = 0; i < boyut; i++) 
        dizi2[i] = dizi[i];
    
	free(dizi);
	dizi = dizi2;
    boyut *= 2;  
	}
	dizi[tepe++]=a;
}
void bastir(){
	for(int i=0;i<tepe;i++){
		printf("%d ",dizi[i]);
	}
}



int main(int argc, char *argv[]) {
	dizi = (int*)malloc((sizeof(int)*2));
	printf("Boyut:%d \n",boyut);
	push(10);
	push(20);
	printf("\nBoyut:%d ",boyut);
	push(30);
	push(40);
	printf("\nBoyut:%d ",boyut);
	push(50);
	bastir();
	printf("\nBoyut:%d ",boyut);
	pop();
	printf("\n");
	bastir();
	printf("\nBoyut:%d ",boyut);
	pop();
	pop();
	printf("\nBoyut:%d ",boyut);
	pop();
	bastir();
	printf("\nBoyut:%d ",boyut);
	return 0;
}
