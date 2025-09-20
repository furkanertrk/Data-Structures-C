#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
struct node
{
    char* musteri_adi;
    struct node *next;
};
typedef struct node n; // node structından n adında yeni bir veri tipi tanımlaması yaptık

n *root=NULL;
n *iter=NULL;
int enque(char* ad ){
    if(root == NULL){   // linked list boşsa
        root = (n*)malloc(sizeof(n)); //
        root->musteri_adi=ad;
        root->next=NULL;
        iter=root;
        return 0;
    }
    //linked list boş değilse
    iter->next=(n*)malloc(sizeof(n));
    iter=iter->next;    //pointerı kaydırdık
    iter->musteri_adi=ad; //atama yaptık
    iter->next = NULL;  //liste sonu NULL gösteriyor
    return 0;   //kod düzgün çalıştığını belirtmek için return 0 döndürdük


}

char* deque(){
    if(root==NULL){
        printf("sıra yok");
        return NULL;
    }
    n* temp;
    char* rvalue= root->musteri_adi;
    temp=root;
    root=root->next;
    free(temp);
    return rvalue;
}

int isEmpty(){
    if(root == NULL){
        printf("\nHerhangi bir sıra yok");
        return 0;
    }
    printf("\nŞuan sırada birileri var");
    return -1;
}
char* peek(){
    if(isEmpty() == -1){
        char* siradaki =root->musteri_adi;
        return siradaki;
    }
    else return NULL;
}
    


int zaman(){
    int sayac=0;
    if(isEmpty() == -1){
        n* siradakiler;
        siradakiler = root;
        while(siradakiler->next != NULL){
            siradakiler = siradakiler->next;
            sayac+=2;
        }
    }
    return sayac;
}

int main(){
    setlocale(LC_ALL,"Turkish");
    enque("ali");
    enque("veli");
    enque("hasan");
    enque("hüseyin");
    deque();
    deque();
    printf("\nSıradaki kişi: %s",peek());
    printf("\nKalan süre: %d",zaman());

    return 0;
}