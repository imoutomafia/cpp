#include <iostream>
#include "kawiarnia.h"
using namespace std;

int main() {
    Kawiarnia kawiarnia;
    kawiarnia.liczba_kelnerow = 0;
    kawiarnia.liczba_menedzerow = 0;
    kawiarnia.kelnerzy = nullptr;
    kawiarnia.menedzerowie = nullptr;

    inicjalizuj_kawiarnie(kawiarnia.stoliki, kawiarnia.liczba_stolikow, 5);

    int wybor;
    while(true) {
        cout << "Menu: " << endl;
        cout << "1. Dodaj kelnera" << endl;
        cout << "2. Dodaj menedzera" << endl;
        cout << "3. Pokaz informacje o kawiarni" << endl;
        cout << "4. Oblicz srednie zamowienia dla menedzera" << endl;
        cout << "5. Dodaj goscia do stolika" << endl;
        cout << "6. Usun goscia ze stolika" << endl;
        cout << "7. Pokaz stoliki" << endl;
        cout << "8. Wyjscie" << endl;
        cin >> wybor;
        int stolik_id;
        string imie;
        int index;
        switch(wybor) {
            case 1:
                dodaj(kawiarnia.kelnerzy, kawiarnia.liczba_kelnerow);
                break;
            case 2:
                dodaj(kawiarnia.menedzerowie, kawiarnia.liczba_menedzerow);
                break;
            case 3:
                pokaz(kawiarnia);
                break;
            case 4:
                cout << "Podaj indeks menedzera: ";
                cin >> index;
                if(index >= 0 && index < kawiarnia.liczba_menedzerow) {
                    oblicz_srednia(*kawiarnia.menedzerowie[index]);
                } else {
                    cout << "Niepoprawny indeks!" << endl;
                }
                break;
            case 5:
                cout << "Podaj ID stolika: ";
                cin >> stolik_id;
                if(stolik_id > 0 && stolik_id <= kawiarnia.liczba_stolikow) {
                    cout << "Podaj imie goscia: ";
                    cin >> imie;
                    dodaj_goscia(kawiarnia.stoliki[stolik_id - 1], imie);
                } else {
                    cout << "Niepoprawny ID stolika!" << endl;
                }
                break;
            case 6:
                cout << "Podaj ID stolika: ";
                cin >> stolik_id;
                if(stolik_id > 0 && stolik_id <= kawiarnia.liczba_stolikow) {
                    cout << "Podaj imie goscia: ";
                    cin >> imie;
                    usun_goscia(kawiarnia.stoliki[stolik_id - 1], imie);
                } else {
                    cout << "Niepoprawny ID stolika!" << endl;
                }
                break;
            case 7:
                pokaz_stoliki(kawiarnia.stoliki, kawiarnia.liczba_stolikow);
                break;
            case 8:
                usun(kawiarnia.kelnerzy, kawiarnia.liczba_kelnerow);
                delete[] kawiarnia.stoliki;
                return 0;
            default:
                cout << "Niepoprawny wybor!" << endl;
        }
    }
}
