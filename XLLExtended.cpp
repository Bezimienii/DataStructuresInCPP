#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

struct Elem {
    int war;
    struct Elem* xorek;
};

void nastepny_elem(struct Elem** aktua, struct Elem** poprz, struct Elem** konie, struct Elem** pocza)
{
    if ((*aktua) == (*konie))
    {
        (*poprz) = (*konie);
        (*aktua) = (*pocza);
    }
    else if ((*poprz) == (*konie))
    {
        (*poprz) = (*pocza);
        (*aktua) = (*pocza)->xorek;
    }
    else
    {
        struct Elem* naste = (struct Elem*)((uintptr_t)((*aktua)->xorek) ^ (uintptr_t)(*poprz));
        struct Elem* temp = (*aktua);
        *aktua = naste;
        *poprz = temp;
    }
}

void poprzedni_elem(struct Elem** aktua, struct Elem** poprz, struct Elem** konie, struct Elem** pocza)
{
    if ((*aktua) == (*pocza))
    {
        (*aktua) = (*konie);
        (*poprz) = (*konie)->xorek;
    }
    else if ((*poprz) == (*pocza))
    {
        (*aktua) = (*pocza);
        (*poprz) = (*konie);
    }
    else
    {
        struct Elem* temp = *poprz;
        *poprz = (struct Elem*)((uintptr_t)((*poprz)->xorek) ^ (uintptr_t)(*aktua));
        *aktua = temp;
    }
}

void obsluga_wskaznikow_kolejki(struct Elem** el_pocz, struct Elem** prev_el_pocz, struct Elem** el_konc, struct Elem** prev_el_konc,
    bool czy_dodano_na_poczatku, struct Elem** pocza, struct Elem** konie)
{
    if (czy_dodano_na_poczatku)
    {
        if ((*pocza)->xorek == (*el_pocz))
        {
            (*prev_el_pocz) = (*pocza);
        }
        else if ((*pocza)->xorek == (*el_konc))
        {
            (*prev_el_konc) = (*pocza);
        }
    }
    else
    {
        if ((*pocza) == (*el_pocz))
        {
            (*prev_el_pocz) = (*konie);
        }
        else if ((*pocza) == (*el_konc))
        {
            (*prev_el_konc) = (*konie);
        }
    }
}

void dodaj_na_poczatek(struct Elem** aktua, struct Elem** poprz, struct Elem** pocza, struct Elem** konie, int wartosc,
    struct Elem** el_pocz, struct Elem** prev_el_pocz, struct Elem** el_konc, struct Elem** prev_el_konc, bool czy_wywolanie_nie_z_pusha)
{
    //sytuacja 0 elementów
    if (*aktua == NULL)
    {
        *aktua = new struct Elem;
        (*aktua)->war = wartosc;
        (*aktua)->xorek = (struct Elem*)(0);
        (*pocza) = (*aktua);
        (*konie) = (*aktua);
    }
    //sytuacja 1 elementu
    else if ((*pocza) == (*konie))
    {
        *poprz = new struct Elem;
        (*poprz)->war = wartosc;
        (*pocza) = (*poprz);
        (*poprz)->xorek = (*aktua);
        (*aktua)->xorek = (*poprz);
        if ((*el_konc) != NULL && (*el_pocz) != NULL && czy_wywolanie_nie_z_pusha)
        {
            obsluga_wskaznikow_kolejki(el_pocz, prev_el_pocz, el_konc, prev_el_konc, true, pocza, konie);
        }
    }
    else
    {
        struct Elem* nowy = new struct Elem;
        nowy->war = wartosc;
        if ((*pocza) == (*aktua))
        {
            *poprz = nowy;
        }
        (*pocza)->xorek = (struct Elem*)((uintptr_t)((*pocza)->xorek) ^ (uintptr_t)(nowy));
        nowy->xorek = *pocza;
        *pocza = nowy;
        if ((*el_konc) != NULL && (*el_pocz) != NULL && czy_wywolanie_nie_z_pusha)
        {
            obsluga_wskaznikow_kolejki(el_pocz, prev_el_pocz, el_konc, prev_el_konc, true, pocza, konie);
        }
    }
}

void dodaj_na_koniec(struct Elem** aktua, struct Elem** poprz, struct Elem** pocza, struct Elem** konie, int wartosc, 
    struct Elem** el_pocz, struct Elem** prev_el_pocz, struct Elem** el_konc, struct Elem** prev_el_konc, bool czy_wywolanie_nie_z_pusha)
{
    //sytuacja 0 elementów
    if (*aktua == NULL)
    {
        *aktua = new struct Elem;
        (*aktua)->war = wartosc;
        (*aktua)->xorek = (struct Elem*)(0);
        (*pocza) = (*aktua);
        (*konie) = (*aktua);
    }
    //sytuacja 1 elementu
    else if ((*pocza) == (*konie))
    {
        *poprz = new struct Elem;
        (*poprz)->war = wartosc;
        (*konie) = (*poprz);
        (*poprz)->xorek = (*aktua);
        (*aktua)->xorek = (*poprz);
        if ((*el_konc) != NULL && (*el_pocz) != NULL && czy_wywolanie_nie_z_pusha)
        {
            obsluga_wskaznikow_kolejki(el_pocz, prev_el_pocz, el_konc, prev_el_konc, false, pocza, konie);
        }
    }
    else
    {
        struct Elem* nowy = new struct Elem;
        nowy->war = wartosc;
        if ((*konie) == (*poprz))
        {
            *poprz = nowy;
        }
        (*konie)->xorek = (struct Elem*)((uintptr_t)((*konie)->xorek) ^ (uintptr_t)(nowy));
        nowy->xorek = *konie;
        *konie = nowy;
        if ((*el_konc) != NULL && (*el_pocz) != NULL && czy_wywolanie_nie_z_pusha)
        {
            obsluga_wskaznikow_kolejki(el_pocz, prev_el_pocz, el_konc, prev_el_konc, false, pocza, konie);
        }
    }
}

void dodaj_przed_aktualny(struct Elem** aktua, struct Elem** poprz, struct Elem** pocza, struct Elem** konie, int wartosc,
    struct Elem** el_pocz, struct Elem** prev_el_pocz, struct Elem** el_konc, struct Elem** prev_el_konc)
{
    if (*aktua == NULL || (*pocza) == (*konie) || (*aktua) == (*pocza))
    {
        dodaj_na_poczatek(aktua, poprz, pocza, konie, wartosc, el_pocz, prev_el_pocz, el_konc, prev_el_konc, false);
    }
    else
    {
        struct Elem* nowy = new struct Elem;
        nowy->war = wartosc;

        (*aktua)->xorek = (struct Elem*)((uintptr_t)((*aktua)->xorek) ^ (uintptr_t)(*poprz));
        (*poprz)->xorek = (struct Elem*)((uintptr_t)((*poprz)->xorek) ^ (uintptr_t)(*aktua));

        (*aktua)->xorek = (struct Elem*)((uintptr_t)((*aktua)->xorek) ^ (uintptr_t)(nowy));
        (*poprz)->xorek = (struct Elem*)((uintptr_t)((*poprz)->xorek) ^ (uintptr_t)(nowy));
        nowy->xorek = (struct Elem*)((uintptr_t)((*aktua)) ^ (uintptr_t)(*poprz));
        *poprz = nowy;
    }
}

//Przez wskazywany ma być rozumiane aktualny bądź poprzedni
void przesun_wskazywany_element_z_brzegu(struct Elem** aktua, struct Elem** poprz, struct Elem** pocza, struct Elem** konie)
{
    if ((*aktua) == (*pocza))
    {
        (*aktua) = (*konie);
        (*poprz) = (*konie)->xorek;
    }
    else if ((*poprz) == (*pocza))
    {
        (*poprz) = (*konie);
    }
    else
    {
        if ((*konie) == (*aktua))
        {
            (*poprz) = (struct Elem*)((uintptr_t)(*konie) ^ (uintptr_t)((*konie)->xorek->xorek));
            (*aktua) = (*konie)->xorek;
        }
        else if ((*konie) == (*poprz))
        {
            (*poprz) = (*konie)->xorek;
        }
    }
}

void przestawenie_wskaznikow_kolejki_dla_ponad_dwoch_elementow(struct Elem** usuwany_brzeg, struct Elem** drugi_brzeg,
    struct Elem** el_pocz, struct Elem** prev_el_pocz, struct Elem** el_konc, struct Elem** prev_el_konc)
{
    //element ostatni kolejki jest na początku listy
    if ((*el_konc) == (*usuwany_brzeg) && (*prev_el_konc) == (*drugi_brzeg))
    {
        nastepny_elem(el_konc, prev_el_konc, drugi_brzeg, usuwany_brzeg);
        (*prev_el_konc) = (*drugi_brzeg);
    }
    //jeśli element poprzedzający ostatni element kolejki jest na początku listy
    else if ((*prev_el_konc) == (*usuwany_brzeg) && (*el_konc) == (*usuwany_brzeg)->xorek)
    {
        (*prev_el_konc) = (*drugi_brzeg);
    }
    //jeśli pierwszy element kolejki jest na początku tabeli
    else if ((*el_pocz) == (*usuwany_brzeg) && (*prev_el_pocz) == (*drugi_brzeg))
    {
        poprzedni_elem(el_pocz, prev_el_pocz, drugi_brzeg, usuwany_brzeg);
    }
    //jeśli element poprzedzający pierwszy element kolejki jest na początku listy
    else if ((*prev_el_pocz) == (*usuwany_brzeg) && (*el_pocz) == (*usuwany_brzeg)->xorek)
    {
        (*prev_el_pocz) = (*drugi_brzeg);
    }
    //jeśli element ostatni kolejki jest na końcu listy
    else if ((*el_konc) == (*usuwany_brzeg) && (*prev_el_konc) == (*usuwany_brzeg)->xorek)
    {
        nastepny_elem(el_konc, prev_el_konc, usuwany_brzeg, drugi_brzeg);
        (*prev_el_konc) = (*usuwany_brzeg)->xorek;
    }
    //jeśli element poprzedzający ostatni element kolejki jest na końcu listy
    else if ((*prev_el_konc) == (*usuwany_brzeg) && (*el_konc) == (*drugi_brzeg))
    {
        (*prev_el_konc) = (*usuwany_brzeg)->xorek;
    }
    //jeśli element pierwszy kolejki jest na końcu listy
    else if ((*el_pocz) == (*usuwany_brzeg) && (*prev_el_pocz) == (*usuwany_brzeg)->xorek)
    {
        poprzedni_elem(el_pocz, prev_el_pocz, usuwany_brzeg, drugi_brzeg);
    }
    //jeśli element przed pierwszym elementem jest na końcu listy
    else if ((*prev_el_pocz) == (*usuwany_brzeg) && (*el_pocz) == (*drugi_brzeg))
    {
        (*prev_el_pocz) = (*usuwany_brzeg)->xorek;
    }
}

//dla początku badz dla konca
void usuniecie_dla_brzegow(struct Elem** aktua, struct Elem** poprz, struct Elem** usuwany_brzeg, struct Elem** drugi_brzeg,
    struct Elem** el_pocz, struct Elem** prev_el_pocz, struct Elem** el_konc, struct Elem** prev_el_konc)
{
    if ((*usuwany_brzeg) != NULL)
    {
        if ((*poprz) == NULL && (*aktua) == (*usuwany_brzeg))
        {
            (*poprz) = (*drugi_brzeg);
        }
        struct Elem* temp = (*usuwany_brzeg);
        //sytuacja jednego elementu
        if ((*usuwany_brzeg) == (*drugi_brzeg))
        {
            if ((*el_pocz))
            {
                *el_pocz = NULL;
                *el_konc = NULL;
            }
            *usuwany_brzeg = NULL;
            *drugi_brzeg = NULL;
            *aktua = NULL;
        }
        //sytuacja dwóch elementów
        else if ((*usuwany_brzeg)->xorek == (*drugi_brzeg))
        {
            if ((*el_pocz))
            {
                if ((*el_pocz) == (*usuwany_brzeg))
                {
                    (*el_pocz) = (*el_konc);
                }
                else
                {
                    (*el_konc) = (*el_pocz);
                }
                (*prev_el_pocz) = NULL;
                (*prev_el_konc) = NULL;
            }
            if ((*usuwany_brzeg) == (*aktua))
            {
                (*aktua) = (*drugi_brzeg);
            }
            *poprz = NULL;
            (*usuwany_brzeg) = (*drugi_brzeg);
        }
        //else jest w sytuacji gdy istnieje więcej niż dwa elementy
        else {
            if ((*el_pocz))
            {
                przestawenie_wskaznikow_kolejki_dla_ponad_dwoch_elementow(usuwany_brzeg, drugi_brzeg, el_pocz, prev_el_pocz,
                    el_konc, prev_el_konc);
            }
            //if jest dla usuwany_brzeg to początek
            if (((*poprz) != NULL && (*poprz)->xorek == (*aktua)) || ((*aktua) == (*usuwany_brzeg) && (*poprz) == (*drugi_brzeg)))
            {
                przesun_wskazywany_element_z_brzegu(aktua, poprz, usuwany_brzeg, drugi_brzeg);
            }
            //else jest dla końca
            else if ((*aktua)->xorek == (*poprz) || ((*poprz) == (*usuwany_brzeg) && (*aktua) == (*drugi_brzeg)))
            {
                przesun_wskazywany_element_z_brzegu(aktua, poprz, drugi_brzeg, usuwany_brzeg);
            }
            if (*usuwany_brzeg)
            {
                struct Elem* nowy_brzeg = (*usuwany_brzeg)->xorek;
                struct Elem* nowy_xor = (struct Elem*)((uintptr_t)(*usuwany_brzeg) ^ (uintptr_t)(nowy_brzeg->xorek));
                nowy_brzeg->xorek = nowy_xor;
                *usuwany_brzeg = nowy_brzeg;
            }
        }
        delete temp;
    }
}

void usun_pocz(struct Elem** aktua, struct Elem** poprz, struct Elem** pocza, struct Elem** konie,
    struct Elem** el_pocz, struct Elem** prev_el_pocz, struct Elem** el_konc, struct Elem** prev_el_konc)
{
    usuniecie_dla_brzegow(aktua, poprz, pocza, konie, el_pocz, prev_el_pocz, el_konc, prev_el_konc);
}

void usun_kon(struct Elem** aktua, struct Elem** poprz, struct Elem** pocza, struct Elem** konie,
    struct Elem** el_pocz, struct Elem** prev_el_pocz, struct Elem** el_konc, struct Elem** prev_el_konc)
{
    usuniecie_dla_brzegow(aktua, poprz, konie, pocza, el_pocz, prev_el_pocz, el_konc, prev_el_konc);
}

//brak wskaznika na poczatek branego jako parametr bierze się ze sprawdzenia czy poprz == NULL
void usun_akt(struct Elem** aktua, struct Elem** poprz, struct Elem** pocza, struct Elem** konie,
    struct Elem** el_pocz, struct Elem** prev_el_pocz, struct Elem** el_konc, struct Elem** prev_el_konc)
{
    if (*aktua != NULL)
    {
        if ((*pocza) == (*konie))
        {
            usun_pocz(aktua, poprz, pocza, konie, el_pocz, prev_el_pocz, el_konc, prev_el_konc);
        }
        else if ((*aktua) == (*pocza))
        {
            usun_pocz(aktua, poprz, pocza, konie, el_pocz, prev_el_pocz, el_konc, prev_el_konc);
        }
        else if ((*aktua) == (*konie))
        {
            usun_kon(aktua, poprz, pocza, konie, el_pocz, prev_el_pocz, el_konc, prev_el_konc);
        }
        else
        {
            //dodanie tymczasowo nastepnego elementu
            struct Elem* naste = (struct Elem*)((uintptr_t)((*aktua)->xorek) ^ (uintptr_t)(*poprz));
            naste->xorek = (struct Elem*)((uintptr_t)(*aktua) ^ (uintptr_t)(naste->xorek));
            naste->xorek = (struct Elem*)((uintptr_t)(*poprz) ^ (uintptr_t)(naste->xorek));
            struct Elem* temp1 = *aktua;
            //zmiana aktualnego elementu i poprzedniego na o jeden krok wstecz
            *(aktua) = *(poprz);
            *(poprz) = (struct Elem*)((uintptr_t)((*aktua)->xorek) ^ (uintptr_t)(temp1));
            //ustawienie nowego xora
            (*aktua)->xorek = (struct Elem*)((uintptr_t)(*poprz) ^ (uintptr_t)(naste));
            delete temp1;
        }
    }
}

void drukuj(struct Elem** el_pier, struct Elem** el_osta)
{
    if ((*el_pier) == (*el_osta))
    {
        printf("%d\n", (*el_pier)->war);
    }
    else
    {
        struct Elem* temp_poprz;
        struct Elem* temp_aktua;
        struct Elem* schowek;
        printf("%d", (*el_pier)->war);
        temp_aktua = (*el_pier)->xorek;
        temp_poprz = (*el_pier);
        while (temp_aktua != (*el_osta))
        {
            printf(" %d", temp_aktua->war);
            schowek = temp_aktua;
            temp_aktua = (struct Elem*)((uintptr_t)(schowek->xorek) ^ (uintptr_t)(temp_poprz));
            temp_poprz = schowek;
        }
        //drukowanie ostatniego elementu
        printf(" %d\n", (*el_osta)->war);
    }
}

//Funkcja obsługuje zarówno kolejkę jak i listę
int wylicz_elementy(struct Elem** el_pocz, struct Elem** prev_el_pocz, struct Elem** el_konc, struct Elem** pocza, struct Elem** konie)
{
    struct Elem* aktua = *el_pocz;
    struct Elem* poprz = *prev_el_pocz;
    int ilosc_elementow = 0;
    while (aktua != (*el_konc))
    {
        ilosc_elementow += 1;
        poprzedni_elem(&aktua, &poprz, konie, pocza);
    }
    ilosc_elementow += 1;
    return ilosc_elementow;
}

int ilosc_elementow_w_liscie(struct Elem** pocza, struct Elem** konie)
{
    if (*pocza == NULL)
    {
        return 0;
    }
    else if (*pocza == *konie)
    {
        return 1;
    }
    else {
        return wylicz_elementy(konie, &((*konie)->xorek), pocza, pocza, konie);
    }
}

int ilosc_elementow_w_kolejce(struct Elem** el_pocz, struct Elem** prev_el_pocz, struct Elem** el_konc, struct Elem** pocza, struct Elem** konie)
{
    if (*pocza == NULL || *el_pocz == NULL)
    {
        return 0;
    }
    else
    {
        return wylicz_elementy(el_pocz, prev_el_pocz, el_konc, pocza, konie);
    }
}

void wydrukuj_kolejke(struct Elem** el_pocz, struct Elem** prev_el_pocz, struct Elem** el_konc, struct Elem** pocza, struct Elem** konie)
{
    struct Elem* aktua = *el_pocz;
    struct Elem* poprz = *prev_el_pocz;
    printf("%d", aktua->war);
    if (el_pocz == el_konc)
    {
        printf("\n");
    }
    else
    {
        while (aktua != *el_konc)
        {
            poprzedni_elem(&aktua, &poprz, konie, pocza);
            printf(" %d", aktua->war);
        }
        printf("\n");
    }
}

void usun_wezly_niekolejkowe(struct Elem** el_pocz, struct Elem** prev_el_pocz, struct Elem** el_konc, struct Elem** prev_el_konc,
    struct Elem** pocza, struct Elem** konie, struct Elem** poprz, struct Elem** aktua, int czy_ustawic_zera)
{
    //if: jeśli kolejka nie istnieje
    if ((*el_pocz) == NULL)
    {
        if (czy_ustawic_zera)
        {
            struct Elem* poczat = *pocza;
            struct Elem* przed_poczat = *konie;
            while (poczat != (*konie))
            {
                poczat->war = 0;
                nastepny_elem(&poczat, &przed_poczat, pocza, konie);
            }
            poczat->war = 0;
        }
        else
        {
            while (*pocza)
            {
                usun_pocz(aktua, poprz, pocza, konie, el_pocz, prev_el_pocz, el_konc, prev_el_konc);
            }
        }
    }
    else
    {
        //el_usuwany - zerowany bądź usuwany
        struct Elem* el_usuwany = *el_konc;
        struct Elem* przed_el_usuwany = *prev_el_konc;
        if (czy_ustawic_zera)
        {
            poprzedni_elem(&el_usuwany, &przed_el_usuwany, konie, pocza);
            while (el_usuwany != (*el_pocz))
            {
                el_usuwany->war = 0;
                poprzedni_elem(&el_usuwany, &przed_el_usuwany, pocza, konie);
            }
        }
        else
        {
            poprzedni_elem(&el_usuwany, &przed_el_usuwany, konie, pocza);
            while (el_usuwany != (*el_pocz))
            {
                if (el_usuwany == (*aktua))
                {
                    (*aktua) = (*el_pocz);
                    (*poprz) = (*prev_el_pocz);
                }
                else if (el_usuwany == (*poprz))
                {
                    (*poprz) = (*el_pocz);
                }
                usun_akt(&el_usuwany, &przed_el_usuwany, pocza, konie, el_pocz, prev_el_pocz, el_konc, prev_el_konc);
            }
        }
    }
}

//Funkcja push listy
void pchnij(struct Elem** el_pocz, struct Elem** prev_el_pocz, struct Elem** el_konc, struct Elem** prev_el_konc,
    struct Elem** pocza, struct Elem** konie, struct Elem** poprz, struct Elem** aktua, int wartosc)
{
    //jeśli LISTA nie istnieje
    if ((*pocza) == NULL)
    {
        dodaj_na_poczatek(aktua, poprz, pocza, konie, wartosc, el_pocz, prev_el_pocz, el_konc, prev_el_konc, false);
        (*el_pocz) = (*pocza);
        (*el_konc) = (*konie);
    }
    else
    {
        if (((*el_pocz) != NULL) && (*prev_el_pocz == NULL))
        {
            (*prev_el_pocz) = (*poprz);
        }
        if (((*el_konc) != NULL) && (*prev_el_konc == NULL))
        {
            (*prev_el_konc) = (*poprz);
        }
        //jeśli kolejka jest pusta
        if ((*el_pocz) == NULL)
        {
            (*el_pocz) = (*aktua);
            (*el_konc) = (*aktua);
            if ((*poprz) != NULL)
            {
                (*prev_el_pocz) = (*poprz);
                (*prev_el_konc) = (*poprz);
            }
            (*el_konc)->war = wartosc;
        }
        else if (ilosc_elementow_w_kolejce(el_pocz, prev_el_pocz, el_konc, pocza, konie) < ilosc_elementow_w_liscie(pocza, konie))
        {
            poprzedni_elem(el_konc, prev_el_konc, konie, pocza);
            (*el_konc)->war = wartosc;
        }
        else if (ilosc_elementow_w_kolejce(el_pocz, prev_el_pocz, el_konc, pocza, konie) == ilosc_elementow_w_liscie(pocza, konie))
        {
            dodaj_przed_aktualny(el_konc, prev_el_konc, pocza, konie, wartosc, el_pocz, prev_el_pocz, el_konc, prev_el_konc);
            poprzedni_elem(el_konc, prev_el_konc, konie, pocza);

            if ((*pocza)->xorek == (*konie))
            {
                (*prev_el_pocz) = (*pocza);
                (*poprz) = (*pocza);
            }
            if ((*el_pocz) == (*poprz))
            {
                (*aktua) = (*el_konc);
            }
        }
    }
}

//Funkcja pop lsity
void wyciagnij(struct Elem** el_pocz, struct Elem** prev_el_pocz, struct Elem** el_konc, struct Elem** prev_el_konc,
    struct Elem** pocza, struct Elem** konie)
{
    if ((*el_pocz) == NULL)
    {
        printf("NULL\n");
    }
    else if ((*el_pocz) == (*el_konc))
    {
        printf("%d\n", (*el_pocz)->war);
        (*el_pocz) = NULL;
        (*el_konc) = NULL;
        (*prev_el_pocz) = NULL;
        (*prev_el_konc) = NULL;
    }
    else
    {
        printf("%d\n", (*el_pocz)->war);
        poprzedni_elem(el_pocz, prev_el_pocz, konie, pocza);
    }
}

int main()
{
    char* wejscie = new char[15];
    int liczba = 0;
    struct Elem* aktu = NULL;
    struct Elem* popr = NULL;
    struct Elem* pocz = NULL;
    struct Elem* kon = NULL;
    //kol - kolejka
    //popr - element przed
    struct Elem* kol_pocz = NULL;
    struct Elem* kol_popr_pocz = NULL;
    struct Elem* kol_kon = NULL;
    struct Elem* kol_popr_kon = NULL;
    while (scanf("%s", wejscie) > 0)
    {
        //ADDY
        if (wejscie[0] == 'A')
        {
            if (wejscie[1] == 'D')
            {
                if (scanf("%d", &liczba))
                {
                    if (wejscie[4] == 'B')
                    {
                        dodaj_na_poczatek(&aktu, &popr, &pocz, &kon, liczba, &kol_pocz, &kol_popr_pocz, &kol_kon, &kol_popr_kon, true);
                    }
                    else if (wejscie[4] == 'E')
                    {
                        dodaj_na_koniec(&aktu, &popr, &pocz, &kon, liczba, &kol_pocz, &kol_popr_pocz, &kol_kon, &kol_popr_kon, true);
                    }
                }
            }
        }
        //DELE
        if (wejscie[0] == 'D')
        {
            if (wejscie[4] == 'B')
            {
                usun_pocz(&aktu, &popr, &pocz, &kon, &kol_pocz, &kol_popr_pocz, &kol_kon, &kol_popr_kon);
            }
            else if (wejscie[4] == 'E')
            {
                usun_kon(&aktu, &popr, &pocz, &kon, &kol_pocz, &kol_popr_pocz, &kol_kon, &kol_popr_kon);
            }
        }
        //PRINTY, PUSH i POP
        if (wejscie[0] == 'P')
        {
            if (wejscie[1] == 'U')
            {
                if (scanf("%d", &liczba)) 
                {
                    pchnij(&kol_pocz, &kol_popr_pocz, &kol_kon, &kol_popr_kon, &pocz, &kon, &popr, &aktu, liczba);
                }
            }
            else if (wejscie[1] == 'O')
            {
                wyciagnij(&kol_pocz, &kol_popr_pocz, &kol_kon, &kol_popr_kon, &pocz, &kon);
            }
            else {
                if (wejscie[2] == 'I')
                {
                    if (aktu == NULL)
                    {
                        printf("NULL\n");
                    }
                    else if (wejscie[6] == 'B')
                    {
                        drukuj(&kon, &pocz);
                    }
                    else if (wejscie[6] == 'F')
                    {
                        drukuj(&pocz, &kon);
                    }
                    else if (wejscie[6] == 'Q')
                    {
                        if (kol_pocz == NULL)
                        {
                            printf("NULL\n");
                        }
                        else
                        {
                            wydrukuj_kolejke(&kol_pocz, &kol_popr_pocz, &kol_kon, &pocz, &kon);
                        }
                    }
                }
            }
        }
        if (wejscie[0] == 'S')
        {
            liczba = ilosc_elementow_w_liscie(&pocz, &kon);
            printf("%d\n", liczba);
        }
        if (wejscie[0] == 'C')
        {
            liczba = ilosc_elementow_w_kolejce(&kol_pocz, &kol_popr_pocz, &kol_kon, &pocz, &kon);
            printf("%d\n", liczba);
        }
        if (wejscie[0] == 'G')
        {
            //warunki sprawdzają czy lista istnieje i czy elementów w kolejce jest mniej niż w liście
            if (!(pocz == NULL) && (ilosc_elementow_w_kolejce(&kol_pocz, &kol_popr_pocz, &kol_kon, &pocz, &kon) <
                ilosc_elementow_w_liscie(&pocz, &kon)))
            {
                //tu liczba oznacza wybór odśmiecania
                if (wejscie[8] == 'S')
                {
                    liczba = 1;
                }
                else if (wejscie[8] == 'H')
                {
                    liczba = 0;
                }
                usun_wezly_niekolejkowe(&kol_pocz, &kol_popr_pocz, &kol_kon, &kol_popr_kon, &pocz, &kon, &popr, &aktu, liczba);
            }
        }
    }
    delete[] wejscie;
    while (aktu)
    {
        usun_pocz(&aktu, &popr, &pocz, &kon, &kol_pocz, &kol_popr_pocz, &kol_kon, &kol_popr_kon);
    }
}
