#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
using namespace std;

typedef struct node {
    int x;
    node* next;
};

void bastir(node* r) {
    while (r != NULL) {
        printf("%d ", r->x);
        r = r->next;
    }
}
void ekle(node* r, int sayý) {
    while (r->next != NULL) {
        r = r->next;
    }
    r->next = (node*)malloc(sizeof(node));
    r->next->x = sayý;
    r->next->next = NULL;

}
node * ekleSirali(node * r,int x) {
    if (r == NULL) { //linklist boþsa
        r = (node*)malloc(sizeof(node));
        r->next = NULL;
        r->x = x;
        return r;
    }
    if (r->x > x) { //ilk eleman küçükse
                    //root deðiþiyor
        node* temp = (node*)malloc(sizeof(node));
        temp->x = x;
        temp->next = r;
        return temp;
    }
    node* iter = r;
    while (iter->next != NULL && iter->next->x < x) {
        iter = iter->next;
    }
    node* temp = (node*)malloc(sizeof(node));
    temp->next = iter->next;
    iter->next = temp;
    temp->x = x;
    return r;
}
node *sil(node*r,int x){
	node*temp;
	node*iter = r;
	
	if(r->x == x){
		temp=r;
		r=r->next;
		free(temp);
	}
	while(iter->next != NULL && iter->next->x != x){
		iter=iter->next;
	}
	if(iter->next ==NULL )
}
int main()
{
    setlocale(LC_ALL, "Turkish");

    node* root;
    root = NULL;
    root = ekleSirali(root, 400);
    root = ekleSirali(root, 40);
    root = ekleSirali(root, 4);
    root = ekleSirali(root, 450);
    root = ekleSirali(root, 50);
    bastir(root);
}
