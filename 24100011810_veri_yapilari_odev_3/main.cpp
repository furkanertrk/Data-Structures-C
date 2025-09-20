#include <iostream>
#include <stack>
#include <string>
#include <cctype>    // isdigit için
#include <clocale> //türkçe karakterleri yazdýrmak için gereken kütüphane
using namespace std;

// Operatör önceliklerini kontrol eden fonksiyon
int oncelik(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Operatör olup olmadýðýný kontrol eden fonksiyon
bool operatorMu(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Her adýmda devam etmek için Enter'a basmayý bekler
void bekle() {
    cout << "Devam etmek için Enter'a basýn...";
    cin.get();  // Enter tuþunu bekle
}

// Infix to Postfix (çok basamaklý sayýlar için)
string infix_to_postfix(const string &infix) {
    stack<char> stk;
    string postfix = "";
    int i = 0;

    cout << "\nInfix to Postfix dönüþtürme adýmlarý:\n";

    while (i < infix.length()) {
        if (isdigit(infix[i])) {
            // Çok basamaklý sayýlarý iþle
            while (i < infix.length() && isdigit(infix[i])) {
                postfix += infix[i];
                i++;
            }
            postfix += ' '; // Sayýlar arasýnda boþluk koy
            cout << "Operand (" << postfix << ") eklendi.\n";
            bekle();  // Enter'a basmayý bekle
            continue;
        } else if (infix[i] == '(') {
            stk.push(infix[i]);
            cout << "Parantez '(' stack'e eklendi.\n";
            bekle();
        } else if (infix[i] == ')') {
            while (!stk.empty() && stk.top() != '(') {
                postfix += stk.top();
                postfix += ' ';
                stk.pop();
                cout << "Operatör stack'ten postfix'e eklendi.\n";
                bekle();
            }
            stk.pop(); // '(''yi de stack'ten çýkar
            cout << "Parantez ')' stack'ten çýkarýldý.\n";
            bekle();
        } else if (operatorMu(infix[i])) {
            while (!stk.empty() && oncelik(stk.top()) >= oncelik(infix[i])) {
                postfix += stk.top();
                postfix += ' ';
                stk.pop();
                cout << "Operatör stack'ten postfix'e eklendi.\n";
                bekle();
            }
            stk.push(infix[i]);
            cout << "Operatör (" << infix[i] << ") stack'e eklendi.\n";
            bekle();
        }
        i++;
    }

    // Kalan operatörleri de postfix'e ekle
    while (!stk.empty()) {
        postfix += stk.top();
        postfix += ' ';
        stk.pop();
        cout << "Kalan operatör stack'ten postfix'e eklendi.\n";
        bekle();
    }

    cout << "Postfix dönüþüm tamamlandý: " << postfix << endl;
    return postfix;
}

// Postfix çözüm algoritmasý (Çok basamaklý sayýlar için)
void postfix_cozum_algoritmasi(const string &postfix) {
    stack<int> stk;
    int i = 0;

    cout << "\nPostfix çözümleme adýmlarý:\n";

    while (i < postfix.length()) {
        if (isdigit(postfix[i])) {
            int operand = 0;
            // Çok basamaklý sayýlarý iþleyelim
            while (i < postfix.length() && isdigit(postfix[i])) {
                operand = operand * 10 + (postfix[i] - '0');
                i++;
            }
            stk.push(operand);
            cout << operand << " operandý stack'e eklendi.\n";
            bekle();  // Enter'a basmayý bekle
        } else if (operatorMu(postfix[i])) {
            // Operatör ile iþlem yapalým
            int operand2 = stk.top(); stk.pop();
            int operand1 = stk.top(); stk.pop();
            int sonuc = 0;

            switch (postfix[i]) {
                case '+': sonuc = operand1 + operand2; break;
                case '-': sonuc = operand1 - operand2; break;
                case '*': sonuc = operand1 * operand2; break;
                case '/': sonuc = operand1 / operand2; break;
            }

            stk.push(sonuc);
            cout << operand1 << " " << postfix[i] << " " << operand2 << " iþlemi yapýldý. Sonuç: " << sonuc << endl;
            bekle();  // Enter'a basmayý bekle
        }

        // Boþluklarý atla
        while (i < postfix.length() && postfix[i] == ' ') {
            i++;
        }
    }

    cout << "\nSonuç: " << stk.top() << endl;
}

// Ýfadenin geçerli olup olmadýðýný kontrol eden fonksiyon
bool kontrol(const string &infix) {
    int parantezSayaci = 0; // Açýk parantez sayýsýný saymak için
    bool sonKarakterOperator = false; // Son karakterin operatör olup olmadýðýný kontrol etmek için

    for (char ch : infix) {
        if (ch == '(') {
            parantezSayaci++;
        } else if (ch == ')') {
            parantezSayaci--;
            if (parantezSayaci < 0) {
                return false; // Kapanmayan parantez
            }
        } else if (operatorMu(ch)) {
            if (sonKarakterOperator) {
                return false; // Ýki operatör yan yana
            }
            sonKarakterOperator = true; // Son karakter operatör
        } else if (isdigit(ch)) {
            sonKarakterOperator = false; // Son karakter sayý
        } else if (ch != ' ') {
            return false; // Geçersiz karakter
        }
    }

    return (parantezSayaci == 0 && !sonKarakterOperator); // Parantez eþitliði ve son karakter kontrolü
}

int main() {
    string infix, postfix;
    setlocale(LC_ALL, "Turkish");
    jump:
    cout << "Infix ifadeyi girin: ";
    getline(cin, infix); // Birden fazla kelime giriþi için getline kullan

    // Kullanýcýnýn ifadesini kontrol et
    if (!kontrol(infix)) {
        cout << "Geçersiz ifade! Lütfen geçerli bir infix ifade girin." << endl;
        goto jump;
    }

    postfix = infix_to_postfix(infix);
    postfix_cozum_algoritmasi(postfix);

    return 0;
}

