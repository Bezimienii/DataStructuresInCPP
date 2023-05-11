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
        printf("%d\n", (*pocza)->war);
        (*poprz) = (*konie);
        (*aktua) = (*pocza);
    }
    else if ((*poprz) == (*konie))
    {
        printf("%d\n", (*pocza)->xorek->war);
        (*poprz) = (*pocza);
        (*aktua) = (*pocza)->xorek;
    }
    else
    {
        struct Elem* naste = (struct Elem*)((uintptr_t)((*aktua)->xorek) ^ (uintptr_t)(*poprz));
        printf("%d\n", naste->war);
        struct Elem* temp = (*aktua);
        *aktua = naste;
        *poprz = temp;
    }
}

void poprzedni_elem(struct Elem** aktua, struct Elem** poprz, struct Elem** konie, struct Elem** pocza)
{
    if ((*aktua) == (*pocza))
    {
        printf("%d\n", (*konie)->war);
        (*aktua) = (*konie);
        (*poprz) = (*konie)->xorek;
    }
    else if ((*poprz) == (*pocza))
    {
        printf("%d\n", (*pocza)->war);
        (*aktua) = (*pocza);
        (*poprz) = (*konie);
    }
    else
    {
        printf("%d\n", (*poprz)->war);
        struct Elem* temp = *poprz;
        *poprz = (struct Elem*)((uintptr_t)((*poprz)->xorek) ^ (uintptr_t)(*aktua));
        *aktua = temp;
    }
}

void dodaj_na_poczatek(struct Elem** aktua, struct Elem** poprz, struct Elem** pocza, struct Elem** konie, int wartosc)
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
    }
}

void dodaj_na_koniec(struct Elem** aktua, struct Elem** poprz, struct Elem** pocza, struct Elem** konie, int wartosc)
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
    }
}

void dodaj_przed_aktualny(struct Elem** aktua, struct Elem** poprz, struct Elem** pocza, struct Elem** konie, int wartosc)
{
    if (*aktua == NULL || (*pocza) == (*konie) || (*aktua) == (*pocza))
    {
        dodaj_na_poczatek(aktua, poprz, pocza, konie, wartosc);
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

//dla początku badz dla konca
void usuniecie_dla_brzegow(struct Elem** aktua, struct Elem** poprz, struct Elem** usuwany_brzeg, struct Elem** drugi_brzeg)
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
            *usuwany_brzeg = NULL;
            *drugi_brzeg = NULL;
            *aktua = NULL;
        }
        //sytuacja dwóch elementów
        else if ((*usuwany_brzeg)->xorek == (*drugi_brzeg))
        {
            if ((*usuwany_brzeg) == (*aktua))
            {
                (*aktua) = (*drugi_brzeg);
            }
            *poprz = NULL;
            (*usuwany_brzeg) = (*drugi_brzeg);
        }
        //else jest w sytuacji gdy istnieje więcej niż dwa elementy
        else {
            //if jest dla usuwany_brzeg to początek
            if (((*poprz) != NULL && (*poprz)->xorek == (*aktua)) || ((*aktua) == (*usuwany_brzeg) && (*poprz) == (*drugi_brzeg)))
            {
                przesun_wskazywany_element_z_brzegu(aktua, poprz, usuwany_brzeg, drugi_brzeg);
            }
            //else jest dla końca
            else if((*aktua)->xorek == (*poprz) || ((*poprz) == (*usuwany_brzeg) && (*aktua) == (*drugi_brzeg)))
            {
                przesun_wskazywany_element_z_brzegu(aktua, poprz, drugi_brzeg, usuwany_brzeg);
            }
            struct Elem* nowy_brzeg = (*usuwany_brzeg)->xorek;
            struct Elem* nowy_xor = (struct Elem*)((uintptr_t)(*usuwany_brzeg) ^ (uintptr_t)(nowy_brzeg->xorek));
            nowy_brzeg->xorek = nowy_xor;
            *usuwany_brzeg = nowy_brzeg;
        }
        delete temp;
    }
}

void usun_pocz(struct Elem** aktua, struct Elem** poprz, struct Elem** pocza, struct Elem** konie)
{
    usuniecie_dla_brzegow(aktua, poprz, pocza, konie);
}

void usun_kon(struct Elem** aktua, struct Elem** poprz, struct Elem** pocza, struct Elem** konie)
{
    usuniecie_dla_brzegow(aktua, poprz, konie, pocza);
}

//brak wskaznika na poczatek branego jako parametr bierze się ze sprawdzenia czy poprz == NULL
void usun_akt(struct Elem** aktua, struct Elem** poprz, struct Elem** pocza, struct Elem** konie)
{
    if (*aktua != NULL)
    {
        if ((*pocza) == (*konie))
        {
            usun_pocz(aktua, poprz, pocza, konie);
        }
        else if ((*aktua) == (*pocza))
        {
            usun_pocz(aktua, poprz, pocza, konie);
        }
        else if ((*aktua) == (*konie))
        {
            usun_kon(aktua, poprz, pocza, konie);
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

void usun_war(struct Elem** aktua, struct Elem** poprz, struct Elem** pocza, struct Elem** konie,int warto)
{
    if (pocza != NULL)
    {
        //sytuacja jednego elementu
        if ((*pocza) == (*konie))
        {             
            if ((*pocza)->war == warto)
            {
                struct Elem* temp = (*pocza);
                *aktua = NULL;
                *pocza = NULL;
                *konie = NULL;
                delete temp;
            }
        }
        //sytuacja dwoch elementow
        else if ((*pocza)->xorek == (*konie))
        {
            struct Elem* temp_pocz = (*pocza);
            struct Elem* temp_kon = (*konie);
            if ((*pocza)->war == warto)
            {
                *poprz = NULL;
                (*pocza) = (*konie);
                if (temp_pocz == (*aktua))
                {
                    (*aktua) = (*konie);                       
                }
                delete temp_pocz;
            }
            if ((*konie)->war == warto)
            {
                *poprz = NULL;
                if ((*pocza) == (*konie))
                {
                    *aktua = NULL;
                    *pocza = NULL;
                    *konie = NULL;
                }
                else 
                {
                    (*konie) = (*pocza);
                    if ((*konie) == (*aktua))
                    {
                        (*aktua) = (*pocza);
                    }
                }
                delete temp_kon;
            }
        }
        //wiecej niz dwa elementy
        else
        {
            int poczatek = 1;
            struct Elem* temp_poprz;
            struct Elem* temp_aktua;
            temp_poprz = (*pocza);
            temp_aktua = (*pocza)->xorek;
            //dopoki usuwany element jest na poczatku
            while (poczatek)
            {
                if ((*pocza)->war == warto)
                {
                    usun_pocz(aktua, poprz, pocza, konie);
                }
                else
                {
                    poczatek = 0;
                    temp_poprz = (*pocza);
                    temp_aktua = (*pocza)->xorek;
                }
            }
            struct Elem* schowek;

            //elementy nie będące ani poczatkiem ani koncem
            while (temp_poprz != temp_aktua->xorek)
            {
                if (temp_aktua->war == warto)
                {
                    //gdy podczas przechodzenia trafiono na aktualny element
                    if (temp_aktua == (*aktua))
                    {
                        usun_akt(aktua, poprz, pocza, konie);
                        temp_aktua = (struct Elem*)((uintptr_t)((*aktua)->xorek) ^ (uintptr_t)(*poprz));
                        temp_poprz = (*aktua);
                    }
                    //sytuacja gdy element jest poprzednikiem albo nie jest ani poprzednim ani aktualnym
                    else
                    {
                        if (temp_aktua == (*poprz))
                        {
                            (*poprz) = temp_poprz;
                        }
                        struct Elem* temp = temp_aktua;
                        temp_aktua = (struct Elem*)((uintptr_t)(temp_aktua->xorek) ^ (uintptr_t)(temp_poprz));
                        //"od-xorowanie" elementów
                        temp_poprz->xorek = (struct Elem*)((uintptr_t)(temp_poprz->xorek) ^ (uintptr_t)(temp));
                        temp_aktua->xorek = (struct Elem*)((uintptr_t)(temp_aktua->xorek) ^ (uintptr_t)(temp));
                        //dodanie nowych wartości
                        temp_poprz->xorek = (struct Elem*)((uintptr_t)(temp_poprz->xorek) ^ (uintptr_t)(temp_aktua));
                        temp_aktua->xorek = (struct Elem*)((uintptr_t)(temp_aktua->xorek) ^ (uintptr_t)(temp_poprz));
                        delete temp;
                    }
                }
                else
                {
                    schowek = temp_aktua;
                    temp_aktua = (struct Elem*)((uintptr_t)(temp_aktua->xorek) ^ (uintptr_t)(temp_poprz));
                    temp_poprz = schowek;
                }
            }
            //element bedacy koncem
            if (temp_aktua == (*konie))
            {
                if (temp_aktua->war == warto)
                {
                    usun_kon(aktua, poprz, pocza, konie);
                }
            }
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

int main()
{
    char* wejscie = new char[15];
    int liczba = 0;
    struct Elem* aktu = NULL;
    struct Elem* popr = NULL;
    struct Elem* pocz = NULL;
    struct Elem* kon = NULL;
    while (scanf("%s", wejscie) > 0)
    {
        //ACTUAL i ADDY
        if (wejscie[0] == 'A')
        {
            if (wejscie[1] == 'C')
            {
                if (aktu == NULL)
                {
                    printf("NULL\n");
                }
                else
                {
                    printf("%d\n", aktu->war);
                }
            }
            else if (wejscie[1] == 'D')
            {
                if (scanf("%d", &liczba))
                {
                    if (wejscie[4] == 'A')
                    {
                        dodaj_przed_aktualny(&aktu, &popr, &pocz, &kon, liczba);
                    }
                    else if (wejscie[4] == 'B')
                    {
                        dodaj_na_poczatek(&aktu, &popr, &pocz, &kon, liczba);
                    }
                    else if (wejscie[4] == 'E')
                    {
                        dodaj_na_koniec(&aktu, &popr, &pocz, &kon, liczba);
                    }
                }
            }
        }
        //DELE
        if (wejscie[0] == 'D')
        {
            if (wejscie[4] == 'A')
            {
                usun_akt(&aktu, &popr, &pocz, &kon);
            }
            else if (wejscie[4] == 'B')
            {
                usun_pocz(&aktu, &popr, &pocz, &kon);
            }
            else if (wejscie[4] == 'E')
            {
                usun_kon(&aktu, &popr, &pocz, &kon);
            }
            else if (wejscie[4] == 'V')
            {
                if (scanf("%d", &liczba))
                {
                    usun_war(&aktu, &popr, &pocz, &kon, liczba);
                }
            }
        }
        //NEXT
        if (wejscie[0] == 'N')
        {
            if (aktu == NULL)
            {
                printf("NULL\n");
            }
            else if (pocz == kon)
            {
                printf("%d\n", aktu->war);
            }
            else
            {
                nastepny_elem(&aktu, &popr, &kon, &pocz);
            }
        }
        //PREV i PRINTY
        if (wejscie[0] == 'P')
        {
            if (aktu == NULL)
            {
                printf("NULL\n");
            }
            else {
                if (wejscie[2] == 'E')
                {
                    if (pocz == kon)
                    {
                        printf("%d\n", aktu->war);
                    }
                    else
                    {
                        poprzedni_elem(&aktu, &popr, &kon, &pocz);
                    }
                }
                if (wejscie[2] == 'I')
                {
                    if (wejscie[6] == 'B')
                    {
                        drukuj(&kon, &pocz);
                    }
                    if (wejscie[6] == 'F')
                    {
                        drukuj(&pocz, &kon);
                    }
                }
            }
        }
    }
    delete[] wejscie;
    while (aktu)
    {
        usun_pocz(&aktu, &popr, &pocz, &kon);
    }
}
