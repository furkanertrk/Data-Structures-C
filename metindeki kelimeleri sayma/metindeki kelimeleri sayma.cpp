#include <iostream>
#include <fstream>
#include <cstring>
#include <locale>

using namespace std;

struct Node {
    string kelime;  // Kelimenin kendisi
    int sayi;       // Kelimenin tekrar sayýsý
    Node* next;     // Sonraki düðüme pointer
    Node* prev;     // Önceki düðüme pointer
};

// Fonksiyonlar
void ekle(Node*& head, const string& kelime) {
    if (head == nullptr) {  // Eðer liste boþsa
        head = new Node{kelime, 1, nullptr, nullptr};
        head->next = head;
        head->prev = head;
        return;
    }

    Node* iter = head;
    do {
        if (iter->kelime == kelime) {  // Kelime zaten varsa sayýsýný artýrýyoruz
            iter->sayi++;
            return;
        }
        iter = iter->next;
    } while (iter != head);

    // Eðer kelime yoksa ekliyoruz
    Node* yeniNode = new Node{kelime, 1, head, head->prev};
    head->prev->next = yeniNode;
    head->prev = yeniNode;
}

// Listeyi yazdýr
void yazdir(Node* head) {
    int sayac = 0;
    if (head == nullptr) return; // Liste boþsa direkt dönderiyor

    Node* iter = head;
    do {
        sayac++;
        if (sayac % 10 == 0) cout << endl; //Her 10 kelimede 1 aþaðý satýra iniyor
        cout << iter->kelime << ":" << iter->sayi << "  ";
        iter = iter->next;
    } while (iter != head);
}

// Txt dosyasýný okuyup listeye kelimeleri ekleme
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

// Verilen prefix ile baþlayan tüm kelimeleri silme
void kelimeSil(Node*& head, const string& prefix) {
    if (head == nullptr) return;  // Liste boþsa dönüyor

    Node* iter = head;
    bool ilkNode = true;  // Ýlk düðüm için özel durum (root deðiþebilir)

    do {
        Node* sonraki = iter->next;
        if (iter->kelime.rfind(prefix, 0) == 0) {  // Prefix ile baþlýyorsa
            if (iter == head) {  // Eðer ilk düðüm silinecekse
                if (iter->next == head) {  // Listede tek düðüm varsa
                    delete iter;
                    head = nullptr;
                    return;
                }
                head = iter->next;  // Önceden ikinci (veya silme durumuna göre 3.-4. ...) olan düðüm ilk düðüm oluyor
            }

            // RAM'den de iþletim sistemine iade ediyoruz
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
    cout<<"Seçim:";
    
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
            // Kullanýcýdan silinecek kelimenin prefix'ini al
            string prefix;
            cout << endl << "Silinecek kelimenin baþlangýç kýsmýný girin: ";
            cin >> prefix;
            kelimeSil(head, prefix);
            break;
        }
        default:
            cout << "Hatalý seçim yaptýnýz, tekrar deneyiniz" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Turkish"); // Türkçe ifade bastýrmak için

    Node* head = nullptr;  // Baþlangýçta liste boþ oluþturdum

    // Dosyayý oku ve listeye ekle
    dosyaOku(head, "kelimeler.txt");
    
    while (true)
        menu(head);  // Pass 'head' to the menu function

    return 0;
}

