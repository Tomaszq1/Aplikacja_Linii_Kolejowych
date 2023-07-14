// Created by A1398 on 29/04/2023.
#include "Definicja_Class.h"
#include "Defnicja_Class_2.h"
bool Kasjer::sprawdzAktywnoscKasjera(sql::Connection *con) {
    sql::PreparedStatement *pstmt;
    pstmt = con->prepareStatement("SELECT TIMESTAMPDIFF(SECOND, Czas_Logowania, NOW()) AS Czas FROM Lista_Zalogowanych_Kasjerow WHERE Id=?");
    pstmt->setInt(1, this->getIdKasjera());
    sql::ResultSet *res = pstmt->executeQuery();

    bool aktywny = false;
    if (res->next() && res->getInt("Czas") < (maks_czas_bezczynnosci.count() * 60)) {
        aktywny = true;
    }

    delete res;
    delete pstmt;

    return aktywny;
}

void Kasjer::wczytajKasjerow(sql::Connection* con, std::list<Kasjer>& listaKasjerow) {
    try {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM Kasjer"));

        while (res->next()) {
            int id_kasjera = res->getInt("Id");
            std::string imie = res->getString("Imie");
            std::string nazwisko = res->getString("Nazwisko");
            std::string email = res->getString("Email");
            int telefon = res->getInt("Telefon");
            std::string login = res->getString("Login");
            std::string haslo = res->getString("Haslo");

            // Tworzenie obiektu Kasjer z wczytanymi danymi
            Kasjer kasjer(id_kasjera, imie, nazwisko, email, telefon, login, haslo);
            listaKasjerow.push_back(kasjer);
        }

    } catch (sql::SQLException& e) {
        std::cerr << "Error executing query: " << e.what() << std::endl;
    }
}

void SystemTransakcji::wczytajKasjerowZBazyDanych(sql::Connection* con) {
    Kasjer kasjer;
    kasjer.wczytajKasjerow(con, listaKasjerow);
}


