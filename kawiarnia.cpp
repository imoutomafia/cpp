#include <iostream>
#include <string>
#include "kawiarnia.h"
using namespace std;

void inicjalizuj_kawiarnie(Stolik*& stoliki, int& liczba_stolikow, int liczba) {
    liczba_stolikow = liczba;
    stoliki = new Stolik[liczba];
    for (int i = 0; i < liczba; ++i) {
        stoliki[i].id = i + 1;
        stoliki[i].status = WOLNY;
        stoliki[i].liczba_gosci = 0;
    }
}

void dodaj_goscia(Stolik& stolik, const string& imie) {
    if (stolik.liczba_gosci < MAKS_GOSCI) {
        stolik.goscie[stolik.liczba_gosci].imie = imie;
        stolik.goscie[stolik.liczba_gosci].status = OBECNY;
        stolik.liczba_gosci++;
    } else {
        cout << "Stolik pelny!" << endl;
    }
}

void usun_goscia(Stolik& stolik, const string& imie) {
    for (int i = 0; i < stolik.liczba_gosci; ++i) {
        if (stolik.goscie[i].imie == imie) {
            for (int j = i; j < stolik.liczba_gosci - 1; ++j) {
                stolik.goscie[j] = stolik.goscie[j + 1];
            }
            stolik.liczba_gosci--;
            return;
        }
    }
    cout << "Gosc o imieniu " << imie << " nie znaleziony!" << endl;
}

void pokaz_stoliki(const Stolik* stoliki, int liczba_stolikow) {
    for (int i = 0; i < liczba_stolikow; ++i) {
        cout << "Stolik " << stoliki[i].id << ": " << stoliki[i].liczba_gosci << " gosci" << endl;
    }
}

// Nowe funkcje
void stworz(Menedzer**& menedzerowie, const int& liczba) {
    menedzerowie = new Menedzer*[liczba];
    for(int i = 0; i < liczba; ++i) {
        menedzerowie[i] = new Menedzer;
    }
}

void stworz(Kelner**& kelnerzy, const int& liczba) {
    kelnerzy = new Kelner*[liczba];
    for(int i = 0; i < liczba; ++i) {
        kelnerzy[i] = new Kelner;
    }
}

void usun(Kelner**& kelnerzy, int& liczba_kelnerow) {
    for(int i = 0; i < liczba_kelnerow; ++i) {
        delete kelnerzy[i];
    }
    delete[] kelnerzy;
    kelnerzy = nullptr;
    liczba_kelnerow = 0;
}

void dodaj(Kelner**& kelnerzy, int& liczba_kelnerow) {
    Kelner** nowi_kelnerzy = new Kelner*[liczba_kelnerow + 1];
    for(int i = 0; i < liczba_kelnerow; ++i) {
        nowi_kelnerzy[i] = kelnerzy[i];
    }
    nowi_kelnerzy[liczba_kelnerow] = new Kelner;
    delete[] kelnerzy;
    kelnerzy = nowi_kelnerzy;
    ++liczba_kelnerow;
    cout << "Dodano kelnera. Liczba kelnerow: " << liczba_kelnerow << endl;
}

void dodaj(Menedzer**& menedzerowie, int& liczba_menedzerow) {
    Menedzer** nowi_menedzerowie = new Menedzer*[liczba_menedzerow + 1];
    for(int i = 0; i < liczba_menedzerow; ++i) {
        nowi_menedzerowie[i] = menedzerowie[i];
    }
    nowi_menedzerowie[liczba_menedzerow] = new Menedzer;
    delete[] menedzerowie;
    menedzerowie = nowi_menedzerowie;
    ++liczba_menedzerow;
    cout << "Dodano menedzera. Liczba menedzerow: " << liczba_menedzerow << endl;
}

void pokaz(const Kawiarnia& kawiarnia) {
    cout << "Liczba menedzerow: " << kawiarnia.liczba_menedzerow << endl;
    cout << "Liczba kelnerow: " << kawiarnia.liczba_kelnerow << endl;
}

void pokaz(const Menedzer& menedzer) {
    cout << "Menedzer: " << menedzer.osoba.godnosc << ", Wiek: " << menedzer.osoba.wiek << endl;
}

void pokaz(const Pozycja_menu& pozycja) {
    cout << "Pozycja menu: " << pozycja.nazwa << ", Liczba zamowien: " << pozycja.liczba_zamowien << endl;
}

void oblicz_srednia(const Menedzer& menedzer) {
    for(int i = 0; i < menedzer.liczba_pozycji; ++i) {
        Pozycja_menu& pozycja = menedzer.menu[i];
        cout << "Pozycja: " << pozycja.nazwa << endl;
        for(int j = 0; j < pozycja.liczba_zamowien; ++j) {
            Kelner* kelner = pozycja.kelnerzy_przypisani_do_pozycji[j];
            double suma_zamowien = 0;
            int liczba_zamowien = 0;
            for(int k = 0; k < kelner->liczba_pozycji_w_menu; ++k) {
                for(int l = 0; l < kelner->liczba_zamowien; ++l) {
                    suma_zamowien += kelner->zbior_zamowien[k][l];
                    ++liczba_zamowien;
                }
            }
            double srednia = suma_zamowien / liczba_zamowien;
            cout << "Kelner ID: " << kelner->id << ", Srednia zamowien: " << srednia << endl;
        }
    }
}
