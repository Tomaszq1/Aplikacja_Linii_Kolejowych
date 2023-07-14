// Created by A1398 on 14/04/2023.
#ifndef APLIKACJA_LINII_KOLEJOWYCHX_DEFNICJA_CLASS_2_H
#define APLIKACJA_LINII_KOLEJOWYCHX_DEFNICJA_CLASS_2_H
#include "Definicja_Class.h"
class Osoba {
    int id_kasjera;
    int telefon;
    string imie_kasjera;
    string nazwisko_kasjera;
    string email;
    string login;
    string haslo;
public:
    Osoba(int id_kasjera, string imie_kasjera, string nazwisko_kasjera, string email, int telefon, string login, string haslo) {
        this->id_kasjera = id_kasjera;
        this -> imie_kasjera = imie_kasjera;
        this -> nazwisko_kasjera = nazwisko_kasjera;
        this -> email = email;
        this -> telefon = telefon;
        this -> login = login;
        this -> haslo = haslo;
    }
    int getIdKasjera() const {
        return id_kasjera;
    }
    string getImieKasjera() const {
        return imie_kasjera;
    }
    string getNazwiskoKasjera() const {
        return nazwisko_kasjera;
    }
    void setIdKasjera(int id_kasjera) {
        this->id_kasjera=id_kasjera;
    }
    void setImieKasjera(string imie_kasjera) {
        this->imie_kasjera=imie_kasjera;
    }
    void setNazwiskoKasjera(string nazwisko_kasjera) {
        this->nazwisko_kasjera=nazwisko_kasjera;
    }
};
class Kasjer : public Osoba
{
    double kasa;
    sql::Connection* con;
public:
    Kasjer(int id_kasjera =0,string imie = "", string nazwisko = "", string email = "", int telefon = 0, string login = "", string haslo = "")
            : Osoba(id_kasjera, imie, nazwisko, email, telefon, login, haslo) {
        this->kasa = 0.0;
    }
    bool sprawdzAktywnoscKasjera(sql::Connection *con);
    void wczytajKasjerow(sql::Connection* con, std::list<Kasjer>& listaKasjerow);
};
class SystemWyszukiwaniaBiletow {
    Pociag pociag;
public:
    list<Pociag> wyszukajBilety(sql::Connection *con,const string& stacja_poczatkowa, const string& stacja_koncowa,
                                const string& godzina_odjazdu, const string& godzina_przyjazd,
                                const string& data_odjazdu, const string& data_przyjazdu);
};
class SystemTransakcji {
    Pociag pociag;
    Kasjer* kasjer;
    Bilet bilet;
    string rodzaj_platnosci;
    Kasjer* zalogowanyKasjer;
    list<Kasjer> listaKasjerow;
public:
    void dodajDoListyZalogowanychKasjerow(Kasjer* kasjer) {
        listaKasjerow.push_back(*kasjer);
    }
    void wczytajKasjerowZBazyDanych(sql::Connection* con);
    void usunZalogowanegoKasjera() {
        zalogowanyKasjer = nullptr;
    }
    int generateUniqueTicketID(sql::Connection *con);
    bool sprzedajBilet(sql::Connection *con, const Bilet& bilet,const Pociag&pociag, int id_kasjera, string rodzaj_platnosci);
    int generateUniqueTrainID(sql::Connection* con);
};
class Aplikacja_Linii_Kolejowych
{
    sql::Driver *driver;
    sql::Connection* con;
public:
    sql::Connection* getDBConnection() {
        return con;
    }
    Aplikacja_Linii_Kolejowych();
    ~Aplikacja_Linii_Kolejowych();
    SystemTransakcji systemTransakcji;
    SystemWyszukiwaniaBiletow systemWyszukiwaniaBiletow;
    void wyloguj(Kasjer* zalogowanyKasjer,sql::Connection *con);
    void wyswietlMenu(Aplikacja_Linii_Kolejowych* aplikacja);
    void logowanie(Kasjer*& zalogowanyKasjer, sql::Connection *con);
    void createTable(sql::Connection *con);
};
#endif //APLIKACJA_LINII_KOLEJOWYCHX_DEFNICJA_CLASS_2_H

