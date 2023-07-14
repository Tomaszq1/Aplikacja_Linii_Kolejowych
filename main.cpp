#include "Defnicja_Class_2.h"
int main() {
    Aplikacja_Linii_Kolejowych aplikacja;
    aplikacja.systemTransakcji.wczytajKasjerowZBazyDanych(aplikacja.getDBConnection());
    aplikacja.wyswietlMenu(&aplikacja);
    return 0;
}