// Created by A1398 on 14/04/2023.
#include "Definicja_Class.h"
#include "Defnicja_Class_2.h"

/*
void Aplikacja_Linii_Kolejowych::createTable(sql::Connection *con) {
    sql::Statement *stmt = con->createStatement();
    stmt->execute("CREATE TABLE IF NOT EXISTS Bilety_Dostepne11 ("
                  "Id INT NOT NULL AUTO_INCREMENT,"
                  "Stacja_Poczatkowa VARCHAR(255) NOT NULL,"
                  "Data_Odjazdu DATE NOT NULL,"
                  "Godzina_Odjazdu TIME NOT NULL,"
                  "Stacja_Koncowa VARCHAR(255) NOT NULL,"
                  "Data_Przyjazdu DATE NOT NULL,"
                  "Godzina_Przyjazdu TIME NOT NULL,"
                  "Nazwa_Przewoznika VARCHAR(255) NOT NULL,"
                  "Nazwa_Pociagu VARCHAR(255) NOT NULL,"
                  "Dystans_KM DECIMAL(5, 2) NOT NULL,"
                  "PRIMARY KEY (Id)"
                  ")");
    delete stmt;
}
*/

/*
void Aplikacja_Linii_Kolejowych::createTable(sql::Connection *con) {
    sql::Statement *stmt = con->createStatement();
    stmt->execute("CREATE TABLE IF NOT EXISTS Trasa ("
                  "Id_Trasy INT NOT NULL AUTO_INCREMENT,"
                  "Stacja_Poczatkowa VARCHAR(255) NOT NULL,"
                  "Data_Odjazdu DATE NOT NULL,"
                  "Godzina_Odjazdu TIME NOT NULL,"
                  "Stacja_Koncowa VARCHAR(255) NOT NULL,"
                  "Data_Przyjazdu DATE NOT NULL,"
                  "Godzina_Przyjazdu TIME NOT NULL,"
                  "Dystans_KM DECIMAL(5, 2) NOT NULL,"
                  "PRIMARY KEY (Id_Trasy)"
                  ")");
    delete stmt;
}
*/
/*
void Aplikacja_Linii_Kolejowych::createTable(sql::Connection *con) {
    sql::Statement *stmt = con->createStatement();
    stmt->execute("CREATE TABLE IF NOT EXISTS Przewozik ("
                  "Id_Przewoznika INT NOT NULL AUTO_INCREMENT,"
                  "Nazwa_Przewoznika VARCHAR(255) NOT NULL,"
                  "PRIMARY KEY (Id_Przewoznika)"
                  ")");
    delete stmt;
}
*/
/*
void Aplikacja_Linii_Kolejowych::createTable(sql::Connection *con) {
    sql::Statement *stmt = con->createStatement();
    stmt->execute("CREATE TABLE IF NOT EXISTS Pociag ("
                  "Id_Pociagu INT NOT NULL AUTO_INCREMENT,"
                  "Id_Trasy INT NOT NULL,"
                  "Id_Przewoznika INT NOT NULL,"
                  "Nazwa_Pociagu VARCHAR(255) NOT NULL,"
                  "PRIMARY KEY (Id_Pociagu)"
                  ")");
    delete stmt;
}

*/
/*
void Aplikacja_Linii_Kolejowych::createTable(sql::Connection *con) {
    sql::Statement *stmt = con->createStatement();
    stmt->execute("CREATE TABLE IF NOT EXISTS Historia_Transakcji ("
                  "Id_biletu INT NOT NULL AUTO_INCREMENT,"
                  "Stacja_Poczatkowa VARCHAR(255) NOT NULL,"
                  "Stacja_Koncowa VARCHAR(255) NOT NULL,"
                  "Data_Odjazdu DATE NOT NULL,"
                  "Data_Przyjazdu DATE NOT NULL,"
                  "Godzina_Odjazdu TIME NOT NULL,"
                  "Godzina_Przyjazdu TIME NOT NULL,"
                  "Nazwa_Przewoznika VARCHAR(255) NOT NULL,"
                  "Nazwa_Pociagu VARCHAR(255) NOT NULL,"
                  "Nr_Pociagu INT NOT NULL,"
                  "Liczba_Osob INT NOT NULL,"
                  "Ulga_Biletowa VARCHAR(255) NOT NULL,"
                  "Cena_Biletu DOUBLE NOT NULL,"
                  "Dystans_KM DECIMAL(5, 2) NOT NULL,"
                  "Rodzaj_Platnosci VARCHAR(255) NOT NULL,"
                  "Data_Sprzedazy DATE NOT NULL,"
                  "Godzina_Sprzedazy TIME NOT NULL,"
                  "Id_Kasjera INT NOT NULL,"
                  "PRIMARY KEY (id_biletu)"
                  ")");
    delete stmt;
}
*/
/*

void Aplikacja_Linii_Kolejowych::createTable(sql::Connection *con) {
    sql::Statement *stmt = con->createStatement();
    stmt->execute("CREATE TABLE IF NOT EXISTS Sprzedane_Bilety ("
                  "Id_biletu INT NOT NULL AUTO_INCREMENT,"
                  "Id_pociagu INT NOT NULL,"
                  "Data_Odjazdu DATE NOT NULL,"
                  "Data_Przyjazdu DATE NOT NULL,"
                  "Godzina_Odjazdu TIME NOT NULL,"
                  "Godzina_Przyjazdu TIME NOT NULL,"
                  "Liczba_Osob INT NOT NULL,"
                  "Id_stawki INT NOT NULL,"
                  "Cena_Biletu DOUBLE NOT NULL,"
                  "Rodzaj_Platnosci VARCHAR(255) NOT NULL,"
                  "Data_Sprzedazy DATE NOT NULL,"
                  "Godzina_Sprzedazy TIME NOT NULL,"
                  "Id_Kasjera INT NOT NULL,"
                  "PRIMARY KEY (id_biletu)"
                  ")");
    delete stmt;
}
*/
/*
void Aplikacja_Linii_Kolejowych::createTable(sql::Connection *con) {
    sql::Statement *stmt = con->createStatement();
    stmt->execute("CREATE TABLE IF NOT EXISTS Stawki1 ("
                  "Id_stawki INT NOT NULL AUTO_INCREMENT,"
                  "Stawka_W_Km DOUBLE NOT NULL,"
                  "Ulga_Student DOUBLE NOT NULL,"
                  "Ulga_Uczen DOUBLE NOT NULL,"
                  "Ulga_Senior DOUBLE NOT NULL,"
                  "PRIMARY KEY (Id_stawki)"
                  ")");
    delete stmt;
}
*/
/*
void Aplikacja_Linii_Kolejowych::createTable(sql::Connection *con) {
    sql::Statement *stmt = con->createStatement();
    stmt->execute("CREATE TABLE IF NOT EXISTS Stawki ("
                  "Id_stawki INT NOT NULL AUTO_INCREMENT,"
                  "Stawka_W_Km DOUBLE NOT NULL,"
                  "Ulga DOUBLE NOT NULL,"
                  "Typ_Ulgi VARCHAR(10) NOT NULL,"
                  "PRIMARY KEY (Id_stawki)"
                  ")");
    delete stmt;
}
*/
/*
void Aplikacja_Linii_Kolejowych::createTable(sql::Connection *con) {
    sql::Statement *stmt = con->createStatement();
    stmt->execute("CREATE TABLE IF NOT EXISTS Kasjer1 ("
                  "Id INT(11) NOT NULL AUTO_INCREMENT,"
                  "Imie VARCHAR(255) NOT NULL,"
                  "Nazwisko VARCHAR(255) NOT NULL,"
                  "Email VARCHAR(255) NOT NULL,"
                  "Telefon INT(9) NOT NULL,"
                  "Login VARCHAR(255) NOT NULL,"
                  "Haslo VARCHAR(255) NOT NULL,"
                  "PRIMARY KEY (Id)"
                  ")");
    delete stmt;
}
*/
/*
void Aplikacja_Linii_Kolejowych::createTable(sql::Connection *con) {
    sql::Statement *stmt = con->createStatement();
    stmt->execute("CREATE TABLE IF NOT EXISTS Lista_Zalogowanych_Kasjerow ("
                  "Id INT(11) NOT NULL AUTO_INCREMENT,"
                  "Imie VARCHAR(255) NOT NULL,"
                  "Nazwisko VARCHAR(255) NOT NULL,"
                  "Czas_Logowania TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,"
                  "Czas_Wylogowania TIMESTAMP DEFAULT NULL,"
                  "PRIMARY KEY (Id)"
                  ")");
    delete stmt;
}
*/

void Aplikacja_Linii_Kolejowych::logowanie(Kasjer*& zalogowanyKasjer, sql::Connection *con) {
    while (zalogowanyKasjer == nullptr) {
        string login, haslo;
        cout << "Podaj login kasjera: ";
        cin >> login;
        cout << "Podaj haslo kasjera: ";
        cin >> haslo;
// sprawdzenie danych logowania w bazie danych

        sql::PreparedStatement *pstmt;
        pstmt = con->prepareStatement("SELECT * FROM Kasjer WHERE Login=? AND Haslo=?");
        pstmt->setString(1, login);
        pstmt->setString(2, haslo);
        sql::ResultSet *res = pstmt->executeQuery();
        if (res->next()) {
            cout << "Zalogowano jako: " << res->getString("Imie") << " " << res->getString("Nazwisko") << endl;
            // tworzenie obiektu Kasjer na podstawie danych z bazy danych
            zalogowanyKasjer = new Kasjer(res->getInt("Id"), res->getString("Imie"), res->getString("Nazwisko"),
                                          res->getString("Email"), res->getInt("Telefon"), res->getString("Login"),
                                          res->getString("Haslo"));
            // dodanie zalogowanego kasjera do listy zalogowanych kasjerów
            systemTransakcji.dodajDoListyZalogowanychKasjerow(zalogowanyKasjer);

            // Usunięcie poprzedniego wpisu zalogowania dla tego kasjera
            sql::PreparedStatement *pstmt2;
            pstmt2 = con->prepareStatement("DELETE FROM Lista_Zalogowanych_Kasjerow WHERE Imie=? AND Nazwisko=?");
            pstmt2->setString(1, zalogowanyKasjer->getImieKasjera());
            pstmt2->setString(2, zalogowanyKasjer->getNazwiskoKasjera());
            pstmt2->executeUpdate();
            delete pstmt2;

            // Dodanie zalogowanego kasjera do bazy danych
            sql::PreparedStatement *pstmt3;
            pstmt3 = con->prepareStatement(
                    "INSERT INTO Lista_Zalogowanych_Kasjerow (Id, Imie, Nazwisko, Czas_Logowania) VALUES (?,?,?, NOW())");
            pstmt3->setInt(1, zalogowanyKasjer->getIdKasjera());
            pstmt3->setString(2, zalogowanyKasjer->getImieKasjera());
            pstmt3->setString(3, zalogowanyKasjer->getNazwiskoKasjera());
            pstmt3->executeUpdate();
            delete pstmt3;

        } else {
            cout << "Nieprawidłowy login lub hasło." << endl;
        }
        delete res;
        delete pstmt;
    }
}

void Aplikacja_Linii_Kolejowych::wyloguj(Kasjer* zalogowanyKasjer, sql::Connection *con) {
    if (zalogowanyKasjer == nullptr) {
        cout << "Nie jesteś zalogowany." << endl;
        return;
    }
    string odpowiedz;
    while (true) {
        cout << "Czy na pewno chcesz się wylogować? (t/n)" << endl;
        cin >> odpowiedz;
        if (odpowiedz == "t")
        {
            // usunięcie zalogowanego kasjera z listy zalogowanych kasjerów w systemie rezerwacji
            systemTransakcji.usunZalogowanegoKasjera();
            // usunięcie zalogowanego kasjera z bazy danych
            sql::PreparedStatement *pstmt;
            pstmt = con->prepareStatement("UPDATE Lista_Zalogowanych_Kasjerow SET Czas_Wylogowania = NOW() WHERE Imie = ? AND Nazwisko = ?");
            pstmt->setString(1, zalogowanyKasjer->getImieKasjera());
            pstmt->setString(2, zalogowanyKasjer->getNazwiskoKasjera());
            pstmt->executeUpdate();
            delete pstmt;
            zalogowanyKasjer = nullptr;
            cout << "Wylogowano." << endl;
            return;
        }
        else if (odpowiedz == "n") {
            return;
        }
        else {
            cout << "Nieprawidłowa odpowiedź. Spróbuj ponownie." << endl;
        }
    }
}








