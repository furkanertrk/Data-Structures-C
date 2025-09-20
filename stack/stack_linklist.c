#include <stdio.h>
#include <stdlib.h>
#include "stacklinklist.h"


int pop(node* root){
    if(root == NULL){
        printf("Stack bos");
        return -1;}
    
    node*iter = root;
    while(iter->next->next != NULL){
        iter = iter->next;
    }
    node* temp = iter->next;
    int rvalue = temp->data;
    free(temp);
    iter ->next = NULL;


node * push(node * root, int a){
    if(root == NULL){
        root = (node*) malloc(sizeof(node));
        root->data=a;
        root ->next=NULL;
        return root;
    }
    node * iter = root;
    while(iter->next !=NULL){
        iter = iter->next;
    }
    node* temp= (node*)malloc(sizeof(node));
    temp ->data = a;
    temp ->next = NULL;
    iter->next = temp;
    return root;

}







int main(int argc, char *argv[]) {
	node* s= NULL;
    s= push(s,10);
    s=push(s,20);
    perror("gecti");
    printf("%d =>",pop(s));
    printf("%d =>",pop(s));
	return 0;
}
