#include <iostream>
#include <string>
#include <random>
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

// Generowanie losowych danych
void generuj_losowe_dane(Kawiarnia& kawiarnia) {
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> dist_id(1, 1000);
    uniform_int_distribution<int> dist_wiek(20, 60);
    uniform_int_distribution<int> dist_pozycji(2, 5);
    uniform_int_distribution<int> dist_kelnerow(50, 100);
    uniform_int_distribution<int> dist_menedzerow(10, 20);

    int liczba_kelnerow = dist_kelnerow(eng);
    int liczba_menedzerow = dist_menedzerow(eng);

    stworz(kawiarnia.kelnerzy, liczba_kelnerow);
    kawiarnia.liczba_kelnerow = liczba_kelnerow;
    stworz(kawiarnia.menedzerowie, liczba_menedzerow);
    kawiarnia.liczba_menedzerow = liczba_menedzerow;

    for (int i = 0; i < liczba_kelnerow; ++i) {
        kawiarnia.kelnerzy[i]->id = dist_id(eng);
        kawiarnia.kelnerzy[i]->osoba.wiek = dist_wiek(eng);
        kawiarnia.kelnerzy[i]->osoba.godnosc = "Kelner_" + to_string(kawiarnia.kelnerzy[i]->id);
    }

    for (int i = 0; i < liczba_menedzerow; ++i) {
        kawiarnia.menedzerowie[i]->osoba.wiek = dist_wiek(eng);
        kawiarnia.menedzerowie[i]->osoba.godnosc = "Menedzer_" + to_string(i + 1);
        kawiarnia.menedzerowie[i]->liczba_pozycji = dist_pozycji(eng);
    }
}

// Generowanie rekordow
void generuj_rekordy(vector<string>& rekordy, int rozmiar) {
    static const vector<string_view> imiona = {"Jan", "Anna", "Marek", "Ewa", "Piotr", "Maria"};
    static const vector<string_view> nazwiska = {"Kowalski", "Nowak", "Wisniewski", "Wojcik", "Kowalczyk", "Kaminski"};
    static const vector<string_view> przedmioty = {"Kawa", "Herbata", "Ciasto", "Kanapka", "Zupa"};

    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> dist_imie(0, imiona.size() - 1);
    uniform_int_distribution<int> dist_nazwisko(0, nazwiska.size() - 1);
    uniform_int_distribution<int> dist_przedmiot(0, przedmioty.size() - 1);
    uniform_int_distribution<int> dist_id(100, 999);

    for (int i = 0; i < rozmiar; ++i) {
        string imie = string(imiona[dist_imie(eng)]);
        string nazwisko = string(nazwiska[dist_nazwisko(eng)]);
        string przedmiot = string(przedmioty[dist_przedmiot(eng)]);
        string rekord = "Kelner " + imie + " " + nazwisko + " serwuje " + przedmiot + " przy stoliku " + to_string(dist_id(eng));
        rekordy.push_back(rekord);
    }
}

void pokaz_rekordy(const vector<string>& rekordy) {
    for (const auto& rekord : rekordy) {
        cout << rekord << endl;
    }
}

void parsuj_rekordy(const vector<string>& rekordy) {
    for (const auto& rekord : rekordy) {
        size_t pos1 = rekord.find("Kelner ");
        size_t pos2 = rekord.find(" serwuje ");
        size_t pos3 = rekord.find(" przy stoliku ");
        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string imie_nazwisko = rekord.substr(pos1 + 7, pos2 - (pos1 + 7));
            string przedmiot = rekord.substr(pos2 + 9, pos3 - (pos2 + 9));
            string stolik = rekord.substr(pos3 + 14);
            cout << "Imie i nazwisko: " << imie_nazwisko << ", Pozycja menu: " << przedmiot << ", Stolik: " << stolik << endl;
        }
    }
}
