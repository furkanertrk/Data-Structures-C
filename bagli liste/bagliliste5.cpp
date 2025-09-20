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

// Fonksiyon tanýmlarý
string kucukHarfeCevir(const string& str);
void ekle(Node*& head, const string& kelime);
void yazdir(Node* head);
void dosyaOku(Node*& head, const string& dosyaAdi);
void kelimeSil(Node*& head, const string& prefix);

int main() {
    setlocale(LC_ALL, "Turkish");

    Node* head = nullptr;

    // Dosyayý oku ve listeye ekle
    dosyaOku(head, "kelimeler.txt");

    // Listeyi yazdýr
    cout << "Orijinal Liste:" << endl;
    yazdir(head);

    // Kullanýcýdan silinecek kelimenin prefix'ini al
    string prefix;
    cout << "Silinecek kelimenin baþlangýç kýsmýný girin: ";
    cin >> prefix;

    // Prefix ile baþlayan kelimeleri sil
    try {
        kelimeSil(head, prefix);
    } catch (exception& e) {
        cerr << e.what() << endl;
    }

    // Güncellenmiþ listeyi yazdýr
    cout << "Güncellenmiþ Liste:" << endl;
    yazdir(head);

    return 0;
}

// Fonksiyon tanýmlarý...
// (diðer fonksiyonlarý burada ekleyin)

