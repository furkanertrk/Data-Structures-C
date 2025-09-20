#include <iostream>
#include <cctype>
#include <string>
using namespace std;

int main() {
    string karakter;

    cout << "Bir karakter girin: ";
    getline(cin,karakter);

    if (isdigit(karakter)) {
        cout << karakter << " bir rakamdýr." << endl;
    } else {
        cout << karakter << " bir rakam deðildir." << endl;
    }

    return 0;
}
