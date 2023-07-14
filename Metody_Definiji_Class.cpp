// Created by A1398 on 14/04/2023.
#include "Definicja_Class.h"
#include "Defnicja_Class_2.h"
string reformatDate(const string& inputDate) {
    cout << "Oryginalna data: " << inputDate << endl;
    if (inputDate.empty()) {
        cout << "Pusta data." << endl;
        return "";
    }
    std::istringstream input(inputDate);
    std::ostringstream output;
    std::tm tmDate = {};
    input >> std::get_time(&tmDate, "%d.%m.%Y");
    if (input.fail()) {
        cout << "Błąd w parsowaniu daty." << endl;
        return "";
    }
    output << put_time(&tmDate, "%Y-%m-%d");
    string reformattedDate = output.str();
    cout << "Sformatowana data: " << reformattedDate << endl;

    return reformattedDate;
}
string reformatTime(const string& inputTime) {
    istringstream input(inputTime);
    ostringstream output;
    tm tmTime = {};
    input >> get_time(&tmTime, "%H:%M");
    if (input.fail()) {
        return "";
    }
    time_t now = time(nullptr);
    tm* tmNow = localtime(&now);
    tmTime.tm_sec = tmNow->tm_sec;
    output << put_time(&tmTime, "%H:%M:%S");
    return output.str();
}
Aplikacja_Linii_Kolejowych::Aplikacja_Linii_Kolejowych()
{
    // łączenie z bazą danych
    try {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
        if (con->isValid()) {
            cout << "Connected to database" << endl;
            con->setSchema("Aplikacja_Linii_KolejowychX");
        } else {
            cout << "Could not connect to server" << endl;
            exit(1);
        }
    } catch (sql::SQLException &e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        exit(1);
    }
}
Aplikacja_Linii_Kolejowych::~Aplikacja_Linii_Kolejowych() {
    delete con;
}

int Bilet::pobierzIdStawkiZUlga(sql::Connection* con, const string& typUlgi) const
{
    int id_stawki = 0;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT Id_stawki FROM Stawki WHERE Typ_Ulgi = ?");
        pstmt->setString(1, typUlgi);
        sql::ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            id_stawki = res->getInt("Id_stawki");
        } else {
            cout << "Nie znaleziono Id_stawki dla podanego typu ulgi: " << typUlgi << endl;
        }
        delete res;
        delete pstmt;
    }
    catch (const sql::SQLException &e) {
        cerr << "Błąd SQL: " << e.what() << endl;
        cerr << "Kod błędu: " << e.getErrorCode() << endl;
        throw std::runtime_error("Błąd SQL podczas pobierania Id_stawki z ulgą");
    }
    return id_stawki;
}
void Bilet::setUlgaBiletowa(sql::Connection* con, const string& ulga_biletowa) {
    stawki.setNazwaUlgi(ulga_biletowa);
    stawki.setIdStawki(pobierzIdStawkiZUlga(con, ulga_biletowa));
}
double Bilet::pobierzStawkeZUlga(sql::Connection* con, const string& typUlgi) const
{
    double stawka = 0.0;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT Stawka_W_Km, Ulga FROM Stawki WHERE Id_stawki = ?");
        int id_stawki = pobierzIdStawkiZUlga(con, typUlgi); // Pobieramy Id_stawki na podstawie typu ulgi
        pstmt->setInt(1, id_stawki);
        sql::ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            double stawka_w_km = res->getDouble("Stawka_W_Km");
            double ulga = res->getDouble("Ulga");
            stawka = stawka_w_km * ulga;
        } else {
            cout << "Nie znaleziono stawki dla podanego id_stawki: " << id_stawki << endl;
        }
        delete res;
        delete pstmt;
    }
    catch (const sql::SQLException &e) {
        cerr << "Błąd SQL: " << e.what() << endl;
        cerr << "Kod błędu: " << e.getErrorCode() << endl;
        throw std::runtime_error("Błąd SQL podczas pobierania stawki z ulgą");
    }
    return stawka;
}
double Bilet::pobierzOdleglosc(sql::Connection* con, int id_trasy) const
{
    double odleglosc = 0.0;
    try {


        std::string sqlQuery = "SELECT Trasa.Dystans_KM FROM Trasa "
                               "INNER JOIN Pociag ON Trasa.Id_Trasy = Pociag.Id_Trasy "
                               "WHERE Pociag.Id_Trasy = ?";
        cout << "Debug: Zapytanie SQL: " << sqlQuery << endl;

        sql::PreparedStatement* pstmt = con->prepareStatement(sqlQuery);
        pstmt->setInt(1, id_trasy);
        sql::ResultSet* res = pstmt->executeQuery();

        if(res->next()) {
            odleglosc = res->getDouble("Dystans_KM");
            cout << "Debug: odleglosc!!!! = " << odleglosc << endl;
        }
        delete res;
        delete pstmt;
    }
    catch (const sql::SQLException &e) {
        cerr << "Błąd SQL w metodzie 'pobierzOdleglosc': " << e.what() << endl;
        cerr << "Kod błędu: " << e.getErrorCode() << endl;
        cerr << "Zapytanie SQL: SELECT Trasa.Dystans_KM FROM Trasa "
             << "INNER JOIN Pociag ON Trasa.Id_Trasy = Pociag.Id_Trasy "
             << "WHERE Pociag.Id_Trasy = " << id_trasy << endl;
    }
    return odleglosc;
}
double Bilet::obliczKosztBiletu(sql::Connection* con) const {

    int id_trasy = 1;
    Trasa trasa = pociag.getTrasa();
    trasa.setId_Trasy(id_trasy);
    //int id_trasy = pociag.getTrasa().getIdTrasy();
    cout << "Debug: id_trasy####### = " << id_trasy << endl;
    double odleglosc = pobierzOdleglosc(con, id_trasy);
    double stawka = pobierzStawkeZUlga(con, getUlgaBiletowa());
    // Dodajemy debugowanie
    cout << "Debug: odleglosc = " << odleglosc << ", stawka = " << stawka << ", liczba_osob = " << getLiczbaOsob() << endl;
    double koszt = odleglosc * stawka;
    koszt *= getLiczbaOsob();
    // Debugowanie kosztu
    cout << "Debug: koszt = " << koszt << endl;

    return koszt;
}

int SystemTransakcji::generateUniqueTrainID(sql::Connection* con)
{
    std::string sql = "SELECT MAX(Id_Biletu) AS max_id FROM Sprzedane_Bilety";
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery(sql);

    int uniqueID = 0;
    if (res->next()) {
        uniqueID = res->getInt(1) + 1;
    }

    delete res;
    delete stmt;
    return uniqueID;
}
int SystemTransakcji::generateUniqueTicketID(sql::Connection *con) {
    try {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT MAX(Id_Biletu) AS max_id FROM Sprzedane_Bilety");

        if (res->next()) {
            int max_id = res->getInt("max_id");
            delete res;
            delete stmt;
            return max_id + 1;
        } else {
            delete res;
            delete stmt;
            return 1; // Jeśli tabela jest pusta, zwracamy 1 jako pierwsze ID
        }

    } catch (const sql::SQLException &e) {
        cerr << "Błąd SQL: " << e.what() << endl;
        cerr << "Kod błędu: " << e.getErrorCode() << endl;
        return -1; // zwracamy -1 w przypadku błędu
    }
}


list<Pociag> SystemWyszukiwaniaBiletow::wyszukajBilety(sql::Connection *con,const string& stacja_poczatkowa, const string& stacja_koncowa,
                                              const string& godzina_odjazdu, const string& godzina_przyjazdu, const string& data_odjazdu,
                                              const string& data_przyjazdu) {
    list<Pociag> znalezioneTrasy;

    try {
        sql::Statement *stmt = con->createStatement();
        stringstream query;

        cout << "stacja_poczatkowa: " << stacja_poczatkowa << endl;
        cout << "stacja_koncowa: " << stacja_koncowa << endl;
        cout << "data_odjazdu: " << data_odjazdu << endl;
        cout << "data_przyjazdu: " << data_przyjazdu << endl;
        cout << "godzina_odjazdu: " << godzina_odjazdu << endl;
        cout << "godzina_przyjazdu: " << godzina_przyjazdu << endl;

        query << "SELECT Trasa.*, Przewoznik.*, Pociag.* FROM Trasa"
              << " JOIN Pociag ON Trasa.Id_Trasy = Pociag.Id_Trasy"
              << " JOIN Przewoznik ON Pociag.Id_Przewoznika = Przewoznik.Id_Przewoznika"
              << " WHERE Stacja_Poczatkowa = '" << stacja_poczatkowa << "' AND Stacja_koncowa = '" << stacja_koncowa
              << "' AND ((Data_Odjazdu = '" << data_odjazdu << "' AND Godzina_Odjazdu >= '" << godzina_odjazdu << "') OR (Data_Odjazdu > '"
              << data_odjazdu << "') OR (Data_Odjazdu = '" << data_odjazdu << "' AND Godzina_Odjazdu <= '" << godzina_odjazdu << "')) AND ((Data_Przyjazdu = '"
              << data_przyjazdu << "' AND Godzina_Przyjazdu <= '" << godzina_przyjazdu << "') OR (Data_Przyjazdu < '" << data_przyjazdu << "') OR (Data_Przyjazdu = '"
              << data_przyjazdu << "' AND Godzina_Przyjazdu >= '" << godzina_przyjazdu << "')) ORDER BY Data_Odjazdu, Godzina_Odjazdu";


        cout << "Executing query: " << query.str() << endl;

        sql::ResultSet *res = stmt->executeQuery(query.str());

        while (res->next()) {
            Trasa trasa(res->getInt("Id_Trasy"), res->getString("Stacja_Poczatkowa"), res->getString("Data_Odjazdu"), res->getString("Godzina_Odjazdu"), res->getString("Stacja_Koncowa"), res->getString("Data_Przyjazdu"), res->getString("Godzina_Przyjazdu"), res->getDouble("Dystans_KM"));
            Przewoznik przewoznik(res->getInt("Id_Przewoznika"), res->getString("Nazwa_Przewoznika"));
            Pociag pociag(res->getInt("Id_Pociagu"), trasa, przewoznik, res->getString("Nazwa_Pociagu"));

            // Dodaj te linie debugowania
            cout << "Wczytano Nazwa_Przewoznika: " << przewoznik.getNazwaPrzewoznika() << endl;
            cout << "Wczytano Nazwa_Pociagu: " << pociag.getNazwaPociagu() << endl;
            cout << "Wczytano Liczbe KM: " << trasa.getDystans_KM() << endl;
            cout << "Wczytano Date odjazdu: " << trasa.getDataOdjazdu() << endl;
            cout << "Wczytano Date przyjazdy: " << trasa.getDataPrzyjazdu() << endl;
            cout << "Wczytano Id Pociagu: " << pociag.getIdPociagu() << endl;
            cout << "Wczytano Id Trasy: " << trasa.getIdTrasy() << endl;
            cout << "Wycztano godzina odjazdu: " << trasa.getGodzinaOdjazdu() << endl;
            cout << "Wycztano godzina przyjazdu: " << trasa.getGodzinaPrzyjazdu() << endl;

            znalezioneTrasy.push_back(pociag);
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        cerr << "ERROR: SQLException in " << __FILE__;
        cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
        cerr << "ERROR: " << e.what();
        cerr << " (MySQL error code: " << e.getErrorCode() << ")" << endl;
    }
    return znalezioneTrasy;
}


bool SystemTransakcji::sprzedajBilet(sql::Connection *con, const Bilet& bilet,const Pociag& pociag, int id_kasjera, string rodzaj_platnosci) {



    int unique_id = generateUniqueTicketID(con);
    if (unique_id == -1) {
        cerr << "Nie można wygenerować unikalnego ID biletu." << endl;
        return false;
    }

    sql::PreparedStatement *pstmt_kasjer = con->prepareStatement(
            "SELECT * FROM Lista_Zalogowanych_Kasjerow WHERE Id = ?");
    pstmt_kasjer->setInt(1, id_kasjera);
    sql::ResultSet *res_kasjer = pstmt_kasjer->executeQuery();

    if (!res_kasjer->next()) {
        cout << "Kasjer o podanym ID nie istnieje." << endl;
        delete res_kasjer;
        delete pstmt_kasjer;
        return false;
    }
    delete res_kasjer;
    delete pstmt_kasjer;

    std::string dataOdjazdu = reformatDate(pociag.getTrasa().getDataOdjazdu());
    std::string dataPrzyjazdu = reformatDate(pociag.getTrasa().getDataPrzyjazdu());
    std::string godzinaOdjazdu =reformatTime(pociag.getTrasa().getGodzinaOdjazdu());
    std::string godzinaPrzyjazdu =reformatTime(pociag.getTrasa().getGodzinaPrzyjazdu());

    try {
        std::string sql = "INSERT INTO Sprzedane_Bilety (Id_biletu, Id_pociagu, Data_Odjazdu, Data_Przyjazdu, Godzina_Odjazdu, Godzina_Przyjazdu, Liczba_Osob, Id_stawki, Cena_Biletu, Rodzaj_Platnosci, Data_Sprzedazy, Godzina_Sprzedazy, Id_Kasjera) "
                          "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

        // Debug: Sprawdzamy wartość bilet.getStawki().getIdStawki() na początku funkcji sprzedajBilet()
        cout << "Debug: W sprzedajBilet()" << endl;
        cout << "Debug: Wartość bilet.getStawki().getIdStawki(): " << bilet.getStawki().getIdStawki() << endl;

        sql::PreparedStatement *pstmt = con->prepareStatement(sql);
        pstmt->setInt(1, unique_id); // Id_biletu
        pstmt->setInt(2, pociag.getIdPociagu()); // Id_pociagu
        pstmt->setString(3, dataOdjazdu);
        pstmt->setString(4, dataPrzyjazdu);
        pstmt->setString(5, godzinaOdjazdu);
        pstmt->setString(6, godzinaPrzyjazdu);
        pstmt->setInt(7, bilet.getLiczbaOsob());

        int idStawki = bilet.getStawki().getIdStawki();
        cout << "Identyfikator stawki to: " << idStawki << endl;
        pstmt->setInt(8, idStawki);

        pstmt->setDouble(9, bilet.obliczKosztBiletu(con)); // Cena_Biletu

        pstmt->setString(10, rodzaj_platnosci);
        pstmt->setString(11, getCurrentDate()); // Data_Sprzedazy
        pstmt->setString(12, getCurrentTime()); // Godzina_Sprzedazy
        pstmt->setInt(13, id_kasjera); // Id_Kasjera

        int id_trasy = pociag.getTrasa().getIdTrasy();
        cout << "Identyfikator trasy: " << id_trasy << endl;
        double odleglosc = bilet.pobierzOdleglosc(con, id_trasy);
        cout << "Odległosc: " << odleglosc << endl;
        cout << "unikalne id biletu: " << unique_id << endl;// to dziala poprawnie
        cout << "Stawka: " << bilet.pobierzStawkeZUlga(con, bilet.getUlgaBiletowa()) << endl;// to dziala poprawnie
        cout << "Data sprzedazy: " << getCurrentDate() << endl;  // to dziala poprawnie
        cout << "Godzina sprzedazy: " << getCurrentTime() << endl;// to dziala poprawnie

        cout<< "cena biletu: " <<  bilet.obliczKosztBiletu(con) << endl;

        pstmt->executeUpdate();
        delete pstmt;

    } catch (const sql::SQLException &e) {
        cerr << "Błąd SQL w metodzie 'sprzedajBilet': " << e.what() << endl;
        cerr << "Kod błędu SQL: " << e.getErrorCode() << endl;
        cerr << "Stan SQL: " << e.getSQLState() << endl;
        return false;
    }
    return true;
}





