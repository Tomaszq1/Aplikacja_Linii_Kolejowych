// Created by A1398 on 29/04/2023.
#include "Definicja_Class.h"
#include "Defnicja_Class_2.h"

void Aplikacja_Linii_Kolejowych::wyswietlMenu(Aplikacja_Linii_Kolejowych* aplikacja)
{
    int wybor = -1;
    Kasjer* zalogowanyKasjer = nullptr;
    list<Pociag> znalezioneTrasy;
    while (wybor != 0) {
        cout << "MENU:" << endl;
        cout << "1. Logowanie" << endl;
        cout << "2. Wylogowanie" << endl;
        cout << "3. Wyszukaj bilet" << endl;
        cout << "4. Sprzedaj bilet" << endl;
        cout << "0. Wyjście" << endl;
        cout << "Wybierz opcję: ";
        cin >> wybor;

        if (zalogowanyKasjer != nullptr)
        {
            if (std::cin.rdbuf()->in_avail() > 0) {
                int timeout_choice = getChoiceWithTimeout(maks_czas_bezczynnosci.count());
                if (timeout_choice == -1) {
                    wyloguj(zalogowanyKasjer, con);
                    continue;
                } else if (timeout_choice > 0) {
                    wybor = timeout_choice;
                }
            }
        }

        switch (wybor)
        {
            case 1: // logowanie
            {
                //createTable(con);
                logowanie(zalogowanyKasjer, con);
                break;
            }
            case 2: // wylogowanie
            {
                if(zalogowanyKasjer == nullptr) {
                    cout << "Nie jesteś zalogowany!" << endl;
                    break;
                }
                wyloguj(zalogowanyKasjer, con);
                break;
            }
            case 3: //Wyszukaj bilet
            {
                if(zalogowanyKasjer == nullptr) {
                    cout << "Nie jesteś zalogowany!" << endl;
                    break;
                }
                string stacja_poczatkowa, stacja_koncowa, godzina_odjazdu, godzina_przyjazdu, data_odjazdu, data_przyjazdu;
                cout << "Podaj stację początkową: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, stacja_poczatkowa);
                cout << "Podaj Date Odjazdu: ";
                cin >> data_odjazdu;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Podaj godzine odjazdu: ";
                cin >> godzina_odjazdu;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Podaj stację końcową: ";
                getline(cin, stacja_koncowa);
                cout << "Podaj Date Przyjazdu: ";
                cin >> data_przyjazdu;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Podaj godzine przyjazdu: ";
                cin >> godzina_przyjazdu;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                //zastosowalismy walidacje danych, czyli musi sie roznic stacja poczatkowa od stacji koncowej nie mozemy wprwadzac Warszawa - Warszawa np
                if (stacja_poczatkowa == stacja_koncowa) {
                    cout << "Stacja początkowa musi się różnić od stacji końcowej." << endl;
                    break;
                }
                if (godzina_odjazdu == godzina_przyjazdu) {
                    cout << "Godzina odjazdu musi się różnić od godzina przyjazdu." << endl;
                    break;
                }

                //Bilet bilet;
                //Trasa trasa;
                //Przewoznik przewoznik;
                Pociag pociag;

                pociag.getTrasa().setStacjaPoczatkowa(stacja_poczatkowa);
                pociag.getTrasa().setDataOdjazdu(data_odjazdu);
                pociag.getTrasa().setGodzinaOdjazdu(godzina_odjazdu);
                pociag.getTrasa().setStacjaKoncowa(stacja_koncowa);
                pociag.getTrasa().setDataPrzyjazdu(data_przyjazdu);
                pociag.getTrasa().setGodzinaPrzyjazdu(godzina_przyjazdu);

                // wyszukaj bilet
                znalezioneTrasy = systemWyszukiwaniaBiletow.wyszukajBilety(con,stacja_poczatkowa, stacja_koncowa,godzina_odjazdu,godzina_przyjazdu,data_odjazdu,
                                                                                data_przyjazdu);
                if (znalezioneTrasy.empty())
                {
                    cout << "Brak dostępnych biletów na trasie " << stacja_poczatkowa << " - " << stacja_koncowa << "."
                         << endl;
                } else {
                    cout << "Dostępne bilety na trasie " << stacja_poczatkowa << " - " << stacja_koncowa << ":" << endl;
                    for (const Pociag &pociag: znalezioneTrasy) {
                        cout << "Trasa ID: " << pociag.getTrasa().getIdTrasy()
                             << ", odjazd: " << pociag.getTrasa().getGodzinaOdjazdu()
                             << ", przyjazd: " << pociag.getTrasa().getGodzinaPrzyjazdu() << endl;
                    }
                    break;
                }
            }

            case 4: // sprzedaj bilet
            {
                cout << "Próba logowania..." << endl;
                logowanie(zalogowanyKasjer, con);
                cout << "Logowanie zakończone." << endl;
                if (zalogowanyKasjer == nullptr) {
                    cout << "Nie jesteś zalogowany jako kasjer." << endl;
                    break;
                }
                if (!zalogowanyKasjer->sprawdzAktywnoscKasjera(con)) {
                    cout << "Twoje konto jest nieaktywne. Zaloguj się." << endl;
                    break;
                }
                if(znalezioneTrasy.empty())
                {
                    cout << "Brak dostępnych biletów do sprzedaży. Najpierw wyszukaj bilety." << endl;
                    break;
                }

                int idTrasy;
                cout << "Podaj ID trasy do sprzedaży: ";
                cin >> idTrasy;

                auto it = find_if(znalezioneTrasy.begin(), znalezioneTrasy.end(),
                                  [idTrasy](const Pociag& pociag) { return pociag.getTrasa().getIdTrasy() == idTrasy; });

                if (it != znalezioneTrasy.end())
                {
                    Pociag pociag = *it;
                    Bilet bilet;

                    string ulga_biletowa;
                    while (true) {
                        cout << "Podaj rodzaj ulgi (np. student, senior, uczen, brak): ";
                        cin >> ulga_biletowa;
                        if (ulga_biletowa == "student" || ulga_biletowa == "senior" || ulga_biletowa == "uczen" ||
                            ulga_biletowa == "brak") {
                            bilet.setUlgaBiletowa(con, ulga_biletowa);
                            break;
                        } else {
                            cout << "Niepoprawna wartość, spróbuj ponownie." << endl;
                        }
                    }
                    int liczba_osob;
                    while (true) {
                        cout << "Podaj liczbę osób na ten bilet: ";
                        cin >> liczba_osob;
                        if (cin.fail() || liczba_osob <= 0) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Niepoprawna wartość, spróbuj ponownie." << endl;
                        } else {
                            bilet.setLiczbaOsob(liczba_osob);
                            break;
                        }
                    }
                    string rodzaj_platnosci;
                    do {
                        cout << "Podaj rodzaj płatności (gotówka/karta): ";
                        cin >> rodzaj_platnosci;
                        if (rodzaj_platnosci == "gotówka" || rodzaj_platnosci == "karta") {
                            break;
                        } else {
                            cout << "Niepoprawna wartość, spróbuj ponownie." << endl;
                        }
                    } while (true);
                    // Debug: Sprawdzamy wartość bilet.getStawki().getIdStawki() przed wywołaniem sprzedajBilet()
                    cout << "Debug: Przed wywołaniem sprzedajBilet()" << endl;
                    cout << "Debug: Wartość bilet.getStawki().getIdStawki(): " << bilet.getStawki().getIdStawki() << endl;
                    if (systemTransakcji.sprzedajBilet(con, bilet, pociag, zalogowanyKasjer->getIdKasjera(), rodzaj_platnosci)) {
                        cout << "Bilet sprzedany." << endl;
                        znalezioneTrasy.erase(it); // Usuń bilet z listy znalezionych biletów
                    } else {
                        cout << "Nie udało się sprzedać biletu." << endl;
                    }

                }
                else {
                    // Bilet nie znaleziony
                    cout << "Nie znaleziono biletu o podanym ID." << endl;
                }
                break;
            }

            case 0: {
                exit(0); // wyjscie
                break;
            }
            default: {
                cout << "Nieznana opcja. Spróbuj ponownie." << endl;
                break;
            }}}}
