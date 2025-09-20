#include <iostream>
#include <clocale>

struct n{
	int data;
	n*sol;
	n*sag;
};
typedef n node;

node * ekle(node*agac,int x){
	if(agac==NULL){
		node *root=(node*)malloc(sizeof(node));
		root->sol=NULL;
		root->sag=NULL;
		root->data=x;
		return root;
	}
	
	
	
}


int main() {
	return 0;
}
