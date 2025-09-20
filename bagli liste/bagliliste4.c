#include <iostream>
#include <fstream>
#include <cstring>
#include <locale>

using namespace std;

struct Node {
    string kelime;  // Kelimenin kendisi
    int sayi;       // Kelimenin tekrar say�s�
    Node* next;     // Sonraki d���me i�aret�i
    Node* prev;     // �nceki d���me i�aret�i
};

// Fonksiyonlar
void ekle(Node*& head, const string& kelime) {
    // E�er liste bo�sa yeni bir d���m olu�tur ve ba�a ekle
    if (head == nullptr) {
        head = new Node{kelime, 1, nullptr, nullptr};
        head->next = head;
        head->prev = head;
        return;
    }

    Node* iter = head;
    do {
        if (iter->kelime == kelime) { // Kelime zaten varsa say�s�n� art�r
            iter->sayi++;
            return;
        }
        iter = iter->next;
    } while (iter != head); // Dairesel oldu�u i�in ba�a d�nene kadar kontrol et

    // E�er kelime yoksa yeni d���m ekle
    Node* yeniNode = new Node{kelime, 1, head, head->prev};
    head->prev->next = yeniNode;
    head->prev = yeniNode;
}

// Listeyi yazd�r
void yazdir(Node* head) {
    if (head == nullptr) return; // E�er liste bo�sa

    Node* iter = head;
    do {
        cout << iter->kelime << ": " << iter->sayi << endl;
        iter = iter->next;
    } while (iter != head); // Dairesel oldu�u i�in ba�a d�nene kadar devam et
}

// Txt dosyas�n� okuyup listeye kelimeleri ekle
void dosyaOku(Node*& head, const string& dosyaAdi) {
    ifstream dosya(dosyaAdi);
    if (!dosya.is_open()) {
        cerr << "Dosya a��lamad�!" << endl;
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

    Node* head = nullptr;  // Ba�lang��ta liste bo�

    // Dosyay� oku ve listeye ekle
    dosyaOku(head, "kelimeler.txt");

    // Listeyi yazd�r
    yazdir(head);

    return 0;
}

