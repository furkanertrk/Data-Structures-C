#include <iostream>
#include <fstream>
#include <cstring>
#include <locale>

using namespace std;

struct Node {
    string kelime;  // Kelimenin kendisi
    int sayi;       // Kelimenin tekrar sayýsý
    Node* next;     // Sonraki düðüme iþaretçi
    Node* prev;     // Önceki düðüme iþaretçi
};

// Fonksiyonlar
void ekle(Node*& head, const string& kelime) {
    // Eðer liste boþsa yeni bir düðüm oluþtur ve baþa ekle
    if (head == nullptr) {
        head = new Node{kelime, 1, nullptr, nullptr};
        head->next = head;
        head->prev = head;
        return;
    }

    Node* iter = head;
    do {
        if (iter->kelime == kelime) { // Kelime zaten varsa sayýsýný artýr
            iter->sayi++;
            return;
        }
        iter = iter->next;
    } while (iter != head); // Dairesel olduðu için baþa dönene kadar kontrol et

    // Eðer kelime yoksa yeni düðüm ekle
    Node* yeniNode = new Node{kelime, 1, head, head->prev};
    head->prev->next = yeniNode;
    head->prev = yeniNode;
}

// Listeyi yazdýr
void yazdir(Node* head) {
    if (head == nullptr) return; // Eðer liste boþsa

    Node* iter = head;
    do {
        cout << iter->kelime << ": " << iter->sayi << endl;
        iter = iter->next;
    } while (iter != head); // Dairesel olduðu için baþa dönene kadar devam et
}

// Txt dosyasýný okuyup listeye kelimeleri ekle
void dosyaOku(Node*& head, const string& dosyaAdi) {
    ifstream dosya(dosyaAdi);
    if (!dosya.is_open()) {
        cerr << "Dosya açýlamadý!" << endl;
        return;
    }

    string kelime;
    while (dosya >> kelime) {
        ekle(head, kelime);  // Her bir kelimeyi listeye ekle
    }

    dosya.close();
}

int main() {
    setlocale(LC_ALL, "Turkish");

    Node* head = nullptr;  // Baþlangýçta liste boþ

    // Dosyayý oku ve listeye ekle
    dosyaOku(head, "kelimeler.txt");

    // Listeyi yazdýr
    yazdir(head);

    return 0;
}

