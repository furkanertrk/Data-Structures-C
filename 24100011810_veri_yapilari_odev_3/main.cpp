#include <iostream>
#include <stack>
#include <string>
#include <cctype>    // isdigit i�in
#include <clocale> //t�rk�e karakterleri yazd�rmak i�in gereken k�t�phane
using namespace std;

// Operat�r �nceliklerini kontrol eden fonksiyon
int oncelik(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Operat�r olup olmad���n� kontrol eden fonksiyon
bool operatorMu(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Her ad�mda devam etmek i�in Enter'a basmay� bekler
void bekle() {
    cout << "Devam etmek i�in Enter'a bas�n...";
    cin.get();  // Enter tu�unu bekle
}

// Infix to Postfix (�ok basamakl� say�lar i�in)
string infix_to_postfix(const string &infix) {
    stack<char> stk;
    string postfix = "";
    int i = 0;

    cout << "\nInfix to Postfix d�n��t�rme ad�mlar�:\n";

    while (i < infix.length()) {
        if (isdigit(infix[i])) {
            // �ok basamakl� say�lar� i�le
            while (i < infix.length() && isdigit(infix[i])) {
                postfix += infix[i];
                i++;
            }
            postfix += ' '; // Say�lar aras�nda bo�luk koy
            cout << "Operand (" << postfix << ") eklendi.\n";
            bekle();  // Enter'a basmay� bekle
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
                cout << "Operat�r stack'ten postfix'e eklendi.\n";
                bekle();
            }
            stk.pop(); // '(''yi de stack'ten ��kar
            cout << "Parantez ')' stack'ten ��kar�ld�.\n";
            bekle();
        } else if (operatorMu(infix[i])) {
            while (!stk.empty() && oncelik(stk.top()) >= oncelik(infix[i])) {
                postfix += stk.top();
                postfix += ' ';
                stk.pop();
                cout << "Operat�r stack'ten postfix'e eklendi.\n";
                bekle();
            }
            stk.push(infix[i]);
            cout << "Operat�r (" << infix[i] << ") stack'e eklendi.\n";
            bekle();
        }
        i++;
    }

    // Kalan operat�rleri de postfix'e ekle
    while (!stk.empty()) {
        postfix += stk.top();
        postfix += ' ';
        stk.pop();
        cout << "Kalan operat�r stack'ten postfix'e eklendi.\n";
        bekle();
    }

    cout << "Postfix d�n���m tamamland�: " << postfix << endl;
    return postfix;
}

// Postfix ��z�m algoritmas� (�ok basamakl� say�lar i�in)
void postfix_cozum_algoritmasi(const string &postfix) {
    stack<int> stk;
    int i = 0;

    cout << "\nPostfix ��z�mleme ad�mlar�:\n";

    while (i < postfix.length()) {
        if (isdigit(postfix[i])) {
            int operand = 0;
            // �ok basamakl� say�lar� i�leyelim
            while (i < postfix.length() && isdigit(postfix[i])) {
                operand = operand * 10 + (postfix[i] - '0');
                i++;
            }
            stk.push(operand);
            cout << operand << " operand� stack'e eklendi.\n";
            bekle();  // Enter'a basmay� bekle
        } else if (operatorMu(postfix[i])) {
            // Operat�r ile i�lem yapal�m
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
            cout << operand1 << " " << postfix[i] << " " << operand2 << " i�lemi yap�ld�. Sonu�: " << sonuc << endl;
            bekle();  // Enter'a basmay� bekle
        }

        // Bo�luklar� atla
        while (i < postfix.length() && postfix[i] == ' ') {
            i++;
        }
    }

    cout << "\nSonu�: " << stk.top() << endl;
}

// �fadenin ge�erli olup olmad���n� kontrol eden fonksiyon
bool kontrol(const string &infix) {
    int parantezSayaci = 0; // A��k parantez say�s�n� saymak i�in
    bool sonKarakterOperator = false; // Son karakterin operat�r olup olmad���n� kontrol etmek i�in

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
                return false; // �ki operat�r yan yana
            }
            sonKarakterOperator = true; // Son karakter operat�r
        } else if (isdigit(ch)) {
            sonKarakterOperator = false; // Son karakter say�
        } else if (ch != ' ') {
            return false; // Ge�ersiz karakter
        }
    }

    return (parantezSayaci == 0 && !sonKarakterOperator); // Parantez e�itli�i ve son karakter kontrol�
}

int main() {
    string infix, postfix;
    setlocale(LC_ALL, "Turkish");
    jump:
    cout << "Infix ifadeyi girin: ";
    getline(cin, infix); // Birden fazla kelime giri�i i�in getline kullan

    // Kullan�c�n�n ifadesini kontrol et
    if (!kontrol(infix)) {
        cout << "Ge�ersiz ifade! L�tfen ge�erli bir infix ifade girin." << endl;
        goto jump;
    }

    postfix = infix_to_postfix(infix);
    postfix_cozum_algoritmasi(postfix);

    return 0;
}

