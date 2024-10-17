#include <iostream>
#include <fstream>
#include <cstring>
#include <locale>

using namespace std;

struct Node {
    string kelime;  // Kelimenin kendisi
    int sayi;       // Kelimenin tekrar say�s�
    Node* next;     // Sonraki d���me pointer
    Node* prev;     // �nceki d���me pointer
};

// Fonksiyonlar
void ekle(Node*& head, const string& kelime) {
    if (head == nullptr) {  // E�er liste bo�sa
        head = new Node{kelime, 1, nullptr, nullptr};
        head->next = head;
        head->prev = head;
        return;
    }

    Node* iter = head;
    do {
        if (iter->kelime == kelime) {  // Kelime zaten varsa say�s�n� art�r�yoruz
            iter->sayi++;
            return;
        }
        iter = iter->next;
    } while (iter != head);

    // E�er kelime yoksa ekliyoruz
    Node* yeniNode = new Node{kelime, 1, head, head->prev};
    head->prev->next = yeniNode;
    head->prev = yeniNode;
}

// Listeyi yazd�r
void yazdir(Node* head) {
    int sayac = 0;
    if (head == nullptr) return; // Liste bo�sa direkt d�nderiyor

    Node* iter = head;
    do {
        sayac++;
        if (sayac % 10 == 0) cout << endl; //Her 10 kelimede 1 a�a�� sat�ra iniyor
        cout << iter->kelime << ":" << iter->sayi << "  ";
        iter = iter->next;
    } while (iter != head);
}

// Txt dosyas�n� okuyup listeye kelimeleri ekleme
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

// Verilen prefix ile ba�layan t�m kelimeleri silme
void kelimeSil(Node*& head, const string& prefix) {
    if (head == nullptr) return;  // Liste bo�sa d�n�yor

    Node* iter = head;
    bool ilkNode = true;  // �lk d���m i�in �zel durum (root de�i�ebilir)

    do {
        Node* sonraki = iter->next;
        if (iter->kelime.rfind(prefix, 0) == 0) {  // Prefix ile ba�l�yorsa
            if (iter == head) {  // E�er ilk d���m silinecekse
                if (iter->next == head) {  // Listede tek d���m varsa
                    delete iter;
                    head = nullptr;
                    return;
                }
                head = iter->next;  // �nceden ikinci (veya silme durumuna g�re 3.-4. ...) olan d���m ilk d���m oluyor
            }

            // RAM'den de i�letim sistemine iade ediyoruz
            iter->prev->next = iter->next;
            iter->next->prev = iter->prev;
            delete iter;
        }

        iter = sonraki;
        ilkNode = false;
    } while (iter != head);
}

// Menu function updated to accept 'head'
void menu(Node*& head) {
	cout<<endl;
    cout << "1-Mevcut Kelimeleri Listele" << endl;
    cout << "2-Kelime Ekle" << endl;
    cout << "3-Kelime Sil" << endl;
    cout<<"Se�im:";
    
    string yenikelimeekle;
    int x;
    cin >> x;
    switch (x) {
        case 1:
            yazdir(head);
            break;
        case 2: {
            cout << "Kelime giriniz: ";
            cin >> yenikelimeekle;
            ekle(head, yenikelimeekle);
            cout << "Eklendi\nYeni Liste:";
            yazdir(head);
            break;
        }
        case 3: {
            // Kullan�c�dan silinecek kelimenin prefix'ini al
            string prefix;
            cout << endl << "Silinecek kelimenin ba�lang�� k�sm�n� girin: ";
            cin >> prefix;
            kelimeSil(head, prefix);
            break;
        }
        default:
            cout << "Hatal� se�im yapt�n�z, tekrar deneyiniz" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Turkish"); // T�rk�e ifade bast�rmak i�in

    Node* head = nullptr;  // Ba�lang��ta liste bo� olu�turdum

    // Dosyay� oku ve listeye ekle
    dosyaOku(head, "kelimeler.txt");
    
    while (true)
        menu(head);  // Pass 'head' to the menu function

    return 0;
}

