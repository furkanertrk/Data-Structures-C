#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

struct node
{
    int data;
    struct node *next;
};
typedef struct node node;

node* root=NULL;
node* son=NULL;
int enq(int x){
    if(root == NULL){
        root = (node*)malloc(sizeof(node));
        root ->data = x;
        root ->next = NULL;
        son = root;
        return 0;
    }
    son->next = (node*)malloc(sizeof(node));
    son->next->data= x;
    son = son->next;
    son->next = NULL;
    return 0;
}
int deq(){
    if(root == NULL){
        printf("Linked list boş");
        return -1;
    }
    int rvalue = root->data; //silinecek değeri göstermek için tuttuk
    node* temp=root; //rootu tutan bir pointer aldık ki free yapabilelim
    root=root->next;
    free(temp);
    return rvalue; //silinen değeri gönderdik
}


int main(){
    for(int i=0; i<20;i++)
        enq(i*10);
    for(int i=0;i<13;i++)
        printf("\nSilindi: %d",deq());

    return 0;
}