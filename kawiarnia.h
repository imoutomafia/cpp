#ifndef KAWIARNIA_H
#define KAWIARNIA_H

#include <string>
using namespace std;

const int MAKS_GOSCI = 4;

enum StatusStolika {
    WOLNY,
    ZAJETY,
    OBECNY
};

struct Gosc {
    string imie;
    StatusStolika status;
};

struct Stolik {
    int id;
    StatusStolika status;
    int liczba_gosci;
    Gosc goscie[MAKS_GOSCI];
};

void inicjalizuj_kawiarnie(Stolik*& stoliki, int& liczba_stolikow, int liczba);
void dodaj_goscia(Stolik& stolik, const string& imie);
void usun_goscia(Stolik& stolik, const string& imie);
void pokaz_stoliki(const Stolik* stoliki, int liczba_stolikow);

struct Dane_osobowe {
    int wiek;
    string godnosc;
};

struct Pozycja_menu;

struct Kelner {
    int id;
    Dane_osobowe osoba;
    Pozycja_menu** zamowienia;
    int liczba_zamowien;
    int liczba_pozycji_w_menu;
    int** zbior_zamowien; // macierz zamowien
};

struct Pozycja_menu {
    string nazwa;
    int liczba_zamowien;
    Kelner** kelnerzy_przypisani_do_pozycji;
};

struct Menedzer {
    Dane_osobowe osoba;
    int liczba_pozycji;
    Pozycja_menu* menu;
};

struct Kawiarnia {
    int liczba_menedzerow;
    int liczba_kelnerow;
    Menedzer** menedzerowie;
    Kelner** kelnerzy;
    Stolik* stoliki;
    int liczba_stolikow;
};

void stworz(Menedzer**& menedzerowie, const int& liczba);
void stworz(Kelner**& kelnerzy, const int& liczba);
void pokaz(const Kawiarnia& kawiarnia);
void pokaz(const Menedzer& menedzer);
void pokaz(const Pozycja_menu& pozycja);
void dodaj(Kelner**& kelnerzy, int& liczba_kelnerow);
void dodaj(Menedzer**& menedzerowie, int& liczba_menedzerow);
void usun(Kelner**& kelnerzy, int& liczba_kelnerow);
void oblicz_srednia(const Menedzer& menedzer);

#endif // KAWIARNIA_H
