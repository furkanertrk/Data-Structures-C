#include <iostream>
#include <cctype>
#include <string>
using namespace std;

int main() {
    string karakter;

    cout << "Bir karakter girin: ";
    getline(cin,karakter);

    if (isdigit(karakter)) {
        cout << karakter << " bir rakamd�r." << endl;
    } else {
        cout << karakter << " bir rakam de�ildir." << endl;
    }

    return 0;
}
