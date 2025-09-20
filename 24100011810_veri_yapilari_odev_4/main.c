//24100011810 FURKAN ERTÜRK

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct node {
    char site_isim[100];
    int ID;
    struct node* next;
} Node;

Node* top = NULL; // Stack'in en üst elemanýný tutmak için
Node* iter = NULL; // Stack'te gezinmek için gezici deðiþken

Node* createNewNode(char* ad, int id) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->site_isim, ad);
    newNode->ID = id;
    newNode->next = NULL;
    return newNode;
}

// Stack'e eleman ekleme (Push)
void push(char* ad) {
    static int ID = 0; // Static yaptým böylece her düðüme özgü ID'yi otomatik artýrýr
    Node* newNode = createNewNode(ad, ++ID);
    newNode->next = top;
    top = newNode;
    iter = top; // iter'i de güncelle (en son düðümü gösteriyor)
    printf("Site eklendi: %s, ID: %d\n", ad, newNode->ID);
}


void pop() {
    if (top == NULL) {
        printf("Stack boþ, çýkartýlacak bir site yok.\n");
        return;
    }
    Node* temp = top;
    printf("Çýkartýlan site: %s, ID: %d\n", temp->site_isim, temp->ID);
    top = top->next;
    iter = top;
    free(temp);
}

void displayStack() {
    if (top == NULL) {
        printf("Stack boþ.\n");
        return;
    }
    Node* current = top;
    printf("Stack'teki siteler:\n");
    while (current != NULL) {
        printf("ID: %d, Site: %s\n", current->ID, current->site_isim);
        current = current->next;
    }
}

int countNodes() {
    int count = 0;
    Node* current = top;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void ileri() {
    if (iter != NULL && iter->next != NULL) {
        iter = iter->next;
        printf("Ýleri gidildi. ID: %d, Site: %s\n", iter->ID, iter->site_isim);
    } else {
        printf("Son elemana ulaþýldý, ileri gidilemiyor.\n");
    }
}

void geri() {
    if (iter == top) {
        printf("Stack baþýndasýnýz, geri gidilemiyor.\n");
        return;
    }
    Node* temp = top;
    while (temp->next != iter) {
        temp = temp->next;
    }
    iter = temp;
    printf("Geri gidildi. ID: %d, Site: %s\n", iter->ID, iter->site_isim);
}

int main() {
    setlocale(LC_ALL, "Turkish");
    int secim;
    char site[100];

    do {
        printf("\n1: Yeni site ekle (Push)\n2: Son siteyi çýkart (Pop)\n3: Stack'i göster\n4: Ýleri git\n5: Geri git\n6: Çýkýþ\nSeçim: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                printf("Site ismini girin: ");
                scanf("%s", site);
                push(site);
                break;
            case 2:
                pop();
                break;
            case 3:
                displayStack();
                break;
            case 4:
                ileri();
                break;
            case 5:
                geri();
                break;
            case 6:
                printf("Çýkýþ yapýlýyor...\n");
                break;
            default:
                printf("Geçersiz seçim, tekrar deneyin.\n");
        }
    } while (secim != 6);

    return 0;
}
