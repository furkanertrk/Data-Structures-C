#include <iostream>
#include <fstream>
#include <cstring>
#include <locale>
#include <algorithm>  
#include <stdexcept>  

using namespace std;

struct Node {
    string kelime;
    int sayi;
    Node* next;
    Node* prev;
};

// Fonksiyon tan�mlar�
string kucukHarfeCevir(const string& str);
void ekle(Node*& head, const string& kelime);
void yazdir(Node* head);
void dosyaOku(Node*& head, const string& dosyaAdi);
void kelimeSil(Node*& head, const string& prefix);

int main() {
    setlocale(LC_ALL, "Turkish");

    Node* head = nullptr;

    // Dosyay� oku ve listeye ekle
    dosyaOku(head, "kelimeler.txt");

    // Listeyi yazd�r
    cout << "Orijinal Liste:" << endl;
    yazdir(head);

    // Kullan�c�dan silinecek kelimenin prefix'ini al
    string prefix;
    cout << "Silinecek kelimenin ba�lang�� k�sm�n� girin: ";
    cin >> prefix;

    // Prefix ile ba�layan kelimeleri sil
    try {
        kelimeSil(head, prefix);
    } catch (exception& e) {
        cerr << e.what() << endl;
    }

    // G�ncellenmi� listeyi yazd�r
    cout << "G�ncellenmi� Liste:" << endl;
    yazdir(head);

    return 0;
}

// Fonksiyon tan�mlar�...
// (di�er fonksiyonlar� burada ekleyin)

