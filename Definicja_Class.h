// Created by A1398 on 14/04/2023.
#ifndef APLIKACJA_LINII_KOLEJOWYCHX_DEFINICJA_CLASS_H
#define APLIKACJA_LINII_KOLEJOWYCHX_DEFINICJA_CLASS_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <random>
#include <map>
#include <set>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <list>
#include <thread>
#include <sstream>
#include <limits>
#include <jdbc/cppconn/prepared_statement.h>
#include "jdbc/mysql_connection.h"
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>


using namespace std;
const string server = "tcp://127.0.0.1:3307";
const string username = "root";
const string password = "root123";
inline string getCurrentDate() {
    time_t now = time(nullptr);
    char buf[11];  // Rozmiar bufora na datę
    strftime(buf, sizeof(buf), "%Y-%m-%d", localtime(&now));
    return buf;
}
inline string getCurrentTime() {
    time_t now = time(nullptr);
    char buf[80];
    strftime(buf, sizeof(buf), "%H:%M:%S", localtime(&now));
    return buf;
}
inline int getChoiceWithTimeout(int timeout_seconds) {
    int choice;
    auto start = std::chrono::steady_clock::now();
    auto end = start;

    while ((end - start) < std::chrono::seconds(timeout_seconds)) {
        if (std::cin.rdbuf()->in_avail() > 0) {
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        end = std::chrono::steady_clock::now();
    }
    return -1;
}
const auto maks_czas_bezczynnosci = std::chrono::minutes(5);


class Trasa {
    int id_trasy;
    string stacja_poczatkowa;
    string stacja_koncowa;
    double Dystans_KM;
    string data_odjazdu;
    string data_przyjazdu;
    string godzina_odjazdu;
    string godzina_przyjazdu;
public:
    Trasa(int id_trasy, string stacja_poczatkowa,string data_odjazdu,
          string godzina_odjazdu,string stacja_koncowa,string data_przyjazdu,string godzina_przyjazdu,double Dystans_KM) {
        this->id_trasy = id_trasy;
        this->stacja_poczatkowa=stacja_poczatkowa;
        this->data_odjazdu=data_odjazdu;
        this->godzina_odjazdu=godzina_odjazdu;
        this->stacja_koncowa=stacja_koncowa;
        this->data_przyjazdu=data_przyjazdu;
        this->godzina_przyjazdu=godzina_przyjazdu;
        this->Dystans_KM = Dystans_KM;
    }
    int getIdTrasy() const {
        return id_trasy;
    }
    void setId_Trasy(int id_trasy) {
        this->id_trasy = id_trasy;
    }
    string getStacjaPoczatkowa() const {
        return stacja_poczatkowa;
    }
    void setStacjaPoczatkowa(string stacja_poczatkowa) {
        this->stacja_poczatkowa = stacja_poczatkowa;
    }
    string getStacjaKoncowa() const {
        return stacja_koncowa;
    }
    void setStacjaKoncowa(string stacja_koncowa) {
        this->stacja_koncowa = stacja_koncowa;
    }
    double getDystans_KM() const {
        return Dystans_KM;
    }
    void setDystans_KM(double Dystans_KM) {
        this->Dystans_KM=Dystans_KM;
    }
    string getDataOdjazdu() const {
        return data_odjazdu;;
    }
    void setDataOdjazdu(string data_odjazdu) {
        this->data_odjazdu = data_odjazdu;
    }
    string getDataPrzyjazdu() const {
        return data_przyjazdu;
    }
    void setDataPrzyjazdu(string data_przyjazdu) {
        this->data_przyjazdu = data_przyjazdu;
    }
    string getGodzinaOdjazdu() const {
        return godzina_odjazdu;
    }
    void setGodzinaOdjazdu(string godzina_odjazdu) {
        this->godzina_odjazdu = godzina_odjazdu;
    }
    string getGodzinaPrzyjazdu() const {
        return godzina_przyjazdu;
    }
    void setGodzinaPrzyjazdu(string godzina_przyjazdu) {
        this->godzina_przyjazdu = godzina_przyjazdu;
    }
};

class Przewoznik {
    int id_przewoznika;
    string Nazwa_Przewoznika;
public:
    Przewoznik(int id_przewoznika, string Nazwa_Przewoznika) {
        this->id_przewoznika=id_przewoznika;
        this->Nazwa_Przewoznika=Nazwa_Przewoznika;
    }
    int getId_Przewozniaka() const {
        return id_przewoznika;
    }
    void setId_Przewoznika(int id_przewoznika) {
        this->id_przewoznika=id_przewoznika;
    }
    string getNazwaPrzewoznika() const {
        return Nazwa_Przewoznika;
    }
    void setNazwaPrzewoznika(const string &value) {
        Nazwa_Przewoznika = value;
    }
};

class Pociag {
    int id_pociagu;
    Trasa trasa;
    Przewoznik przewoznik;
    string Nazwa_Pociagu;
public:
    Pociag(int id_pociagu, Trasa trasa, Przewoznik przewoznik, string Nazwa_Pociagu)
            : id_pociagu(id_pociagu), trasa(trasa), przewoznik(przewoznik), Nazwa_Pociagu(Nazwa_Pociagu) {
        this->id_pociagu=id_pociagu;
        this->Nazwa_Pociagu=Nazwa_Pociagu;
    }
    int getIdPociagu() const {
        return id_pociagu;
    }
    void setIdPociagu(int id_pociagu) {
        this->id_pociagu=id_pociagu;
    }
    string getNazwaPociagu() const {
        return Nazwa_Pociagu;
    }
    void setNazwaPociagu(const string& value) {
        Nazwa_Pociagu = value;
    }
    const Trasa& getTrasa() const {
        return trasa;
    }
    Trasa& getTrasa() {
        return trasa;
    }
    Pociag() : id_pociagu(0),
               trasa(0, "", "", "", "", "", "",0),
               przewoznik(0, ""),
               Nazwa_Pociagu("") {}
};

class Stawki {
    int id_stawki;
    string nazwaUlgi;
public:
    Stawki(int id_stawki, string nazwaUlgi)
    {
        this->id_stawki=id_stawki;
        this->nazwaUlgi=nazwaUlgi;
    }
    int getIdStawki() const {
        return id_stawki;
    }
    void setIdStawki(int id_stawki){
        this->id_stawki=id_stawki;
    }
    string getNazwaUlgi() const {
        return nazwaUlgi;
    }
    void setNazwaUlgi(string nazwaUlgi){
        this->nazwaUlgi=nazwaUlgi;
    }
    void setIDStawki(int id_stawki) {
        this->id_stawki = id_stawki;
    }
    Stawki() : id_stawki(0), nazwaUlgi("") {}
};

class Bilet {
    int id_biletu;
    Pociag pociag;
    Stawki stawki;
    int liczbaOsob;
    double cena;
public:
    Bilet(int id_biletu, int liczbaOsob, double cena, Pociag pociag, int id_stawki, string nazwaUlgi)
            : pociag(pociag), stawki(id_stawki, nazwaUlgi), id_biletu(id_biletu), liczbaOsob(liczbaOsob), cena(cena) {
        this->id_biletu = id_biletu;
        this->liczbaOsob = liczbaOsob;
        this->cena = cena;
    }
    const Pociag& getPociag() const {
        return pociag;
    }
    Pociag& getPociag() {
        return pociag;
    }
    int getIdBiletu() const {
        return id_biletu;
    }
    void setIdBiletu(int id_biletu) {
        this->id_biletu = id_biletu;
    }
    int getLiczbaOsob() const {
        return liczbaOsob;
    }
    void setLiczbaOsob(int liczbaOsob) {
        this->liczbaOsob = liczbaOsob;
    }
    string getUlgaBiletowa() const {
        return stawki.getNazwaUlgi();
    }
    int getIdStawkiNaBilecie() const {
        return stawki.getIdStawki();
    }
    Stawki getStawki() const {
        return stawki;
    }

    int pobierzIdStawkiZUlga(sql::Connection* con, const string& typUlgi) const;
    void setUlgaBiletowa(sql::Connection* con, const string& ulga_biletowa);
    double pobierzStawkeZUlga(sql::Connection *con, const string& typUlgi) const;
    double pobierzOdleglosc(sql::Connection *con, int id_trasy) const;

    double obliczKosztBiletu(sql::Connection *con) const;

    bool operator==(const Bilet &other) const {
        return id_biletu == other.id_biletu &&
               liczbaOsob == other.liczbaOsob &&
               cena == other.cena;
    }
    Bilet() : id_biletu(0) {}
};




#endif //APLIKACJA_LINII_KOLEJOWYCHX_DEFINICJA_CLASS_H
