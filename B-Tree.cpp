#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

//Uzylem Cormen et al. w celu zapoznania się z B-drzewami

struct Wezel {
    int ilosc_kluczy;
    int* klucze;
    Wezel **dzieci;
    bool czy_lisc;
};

void stworz_B_drzewo(Wezel** korzen)
{
    *korzen = new Wezel;
    (*korzen)->czy_lisc = true;
    (*korzen)->ilosc_kluczy = 0;
    (*korzen)->klucze = nullptr;
    (*korzen)->dzieci = nullptr;
}

void dodajPoladzicekukorzenia(Wezel** korzen, Wezel** dziecko, int porzadek)
{
    if ((*korzen)->czy_lisc)
    {
        (*dziecko)->czy_lisc = true;
    }
    else
    {
        (*dziecko)->czy_lisc = false;
    }
    (*dziecko)->ilosc_kluczy = porzadek - 1;
    (*dziecko)->klucze = new int[porzadek - 1];
    if (!(*dziecko)->czy_lisc)
    {
        (*dziecko)->dzieci = new Wezel * [porzadek];
    }
    else
    {
        (*dziecko)->dzieci = nullptr;
    }
}

void przedziel_dziecko(Wezel** wezel, int punkt_tabeli, int porzadek)
{
    Wezel* wezel_dzielony = (*wezel)->dzieci[punkt_tabeli];
    Wezel* prawe = new Wezel;
    Wezel* lewe = new Wezel;
    dodajPoladzicekukorzenia(&wezel_dzielony, &lewe, porzadek);
    dodajPoladzicekukorzenia(&wezel_dzielony, &prawe, porzadek);
    if (!(lewe->czy_lisc))
    {
        lewe->dzieci[0] = wezel_dzielony->dzieci[0];
        prawe->dzieci[0] = wezel_dzielony->dzieci[porzadek];
    }
    for (int i = 0; i < ((2 * porzadek) - 1); i++)
    {
        if (i < (porzadek - 1))
        {
            lewe->klucze[i] = wezel_dzielony->klucze[i];
            if (wezel_dzielony->czy_lisc == false)
            {
                lewe->dzieci[i + 1] = wezel_dzielony->dzieci[i + 1];
            }
        }
        if (i >= porzadek)
        {
            prawe->klucze[i - porzadek] = wezel_dzielony->klucze[i];
            if (wezel_dzielony->czy_lisc == false)
            {
                prawe->dzieci[(i - porzadek) + 1] = wezel_dzielony->dzieci[i + 1];
            }
        }
    }
    int* pom_tab = new int[(*wezel)->ilosc_kluczy + 1];
    Wezel** pom_dzi = new Wezel * [((*wezel)->ilosc_kluczy) + 2];
    bool czy_wstawiono_klucz = false;
    int wstawiany_klucz = (*wezel)->dzieci[punkt_tabeli]->klucze[porzadek - 1];
    for (int i = 0; i < (*wezel)->ilosc_kluczy; i++)
    {
        if ((*wezel)->klucze[i] < wstawiany_klucz)
        {
            pom_tab[i] = (*wezel)->klucze[i];
            pom_dzi[i] = (*wezel)->dzieci[i];
        }
        else if (!czy_wstawiono_klucz)
        {
            pom_tab[i] = wstawiany_klucz;
            pom_dzi[i] = lewe;
            pom_dzi[i + 1] = prawe;
            czy_wstawiono_klucz = true;
        }
        else if (czy_wstawiono_klucz)
        {
            pom_tab[i] = (*wezel)->klucze[i - 1];
            pom_dzi[i + 1] = (*wezel)->dzieci[i];
        }
    }
    if (!czy_wstawiono_klucz)
    {
        pom_tab[(*wezel)->ilosc_kluczy] = wstawiany_klucz;
        pom_dzi[(*wezel)->ilosc_kluczy] = lewe;
        pom_dzi[(*wezel)->ilosc_kluczy + 1] = prawe;
    }
    else if (czy_wstawiono_klucz)
    {
        pom_tab[(*wezel)->ilosc_kluczy] = (*wezel)->klucze[(*wezel)->ilosc_kluczy-1];
        pom_dzi[(*wezel)->ilosc_kluczy + 1] = (*wezel)->dzieci[(*wezel)->ilosc_kluczy];
    }
    delete[](*wezel)->klucze;
    delete[](*wezel)->dzieci;
    (*wezel)->ilosc_kluczy += 1;
    (*wezel)->klucze = new int[(*wezel)->ilosc_kluczy];
    (*wezel)->dzieci = new Wezel * [(*wezel)->ilosc_kluczy + 1];
    for (int i = 0; i < (*wezel)->ilosc_kluczy; i++)
    {
        (*wezel)->klucze[i] = pom_tab[i];
        (*wezel)->dzieci[i] = pom_dzi[i];
    }
    (*wezel)->dzieci[(*wezel)->ilosc_kluczy] = pom_dzi[(*wezel)->ilosc_kluczy];
    delete[] pom_dzi;
    delete[] pom_tab;
    delete[] wezel_dzielony;
}


void dodaj_do_dziecka(Wezel** dziecko, int klucz, int porzadek)
{
    if ((*dziecko)->czy_lisc)
    {
        int* pom_tab = new int[((*dziecko)->ilosc_kluczy) + 1];
        bool czy_wstawiono_klucz = false;
        for (int i = 0; i < (*dziecko)->ilosc_kluczy; i++)
        {
            if ((*dziecko)->klucze[i] < klucz)
            {
                pom_tab[i] = (*dziecko)->klucze[i];
            }
            else if (!czy_wstawiono_klucz)
            {
                pom_tab[i] = klucz;
                czy_wstawiono_klucz = true;
            }
            else if (czy_wstawiono_klucz)
            {
                pom_tab[i] = (*dziecko)->klucze[i-1];
            }
        }
        if (!czy_wstawiono_klucz)
        {
            pom_tab[(*dziecko)->ilosc_kluczy] = klucz;
        }
        else if (czy_wstawiono_klucz)
        {
            pom_tab[(*dziecko)->ilosc_kluczy] = (*dziecko)->klucze[(*dziecko)->ilosc_kluczy - 1];
        }
        delete[](*dziecko)->klucze;
        (*dziecko)->ilosc_kluczy += 1;
        (*dziecko)->klucze = new int[(*dziecko)->ilosc_kluczy];
        for (int i = 0; i < (*dziecko)->ilosc_kluczy; i++)
        {
            (*dziecko)->klucze[i] = pom_tab[i];
        }
        delete[] pom_tab;
    }
    else if (!((*dziecko)->czy_lisc))
    {
        bool czy_znaleziono_mniejsze_miejsce = false;
        for (int i = 0; i < (*dziecko)->ilosc_kluczy; i++)
        {
            if ((*dziecko)->klucze[i] < klucz)
            {
                if ((*dziecko)->dzieci[i]->ilosc_kluczy == ((2 * porzadek) - 1))
                {
                    przedziel_dziecko(dziecko, i, porzadek);
                    if ((*dziecko)->klucze[i] > klucz)
                    {
                        dodaj_do_dziecka(dziecko, i, porzadek);
                    }
                    else
                    {
                        dodaj_do_dziecka(dziecko, i + 1, porzadek);
                    }
                }
                else 
                {
                    dodaj_do_dziecka(&((*dziecko)->dzieci[i]), klucz, porzadek);
                }
                czy_znaleziono_mniejsze_miejsce = true;
                break;
            }
        }
        if (!czy_znaleziono_mniejsze_miejsce)
        {
            int miejsce = (*dziecko)->ilosc_kluczy;
            if ((*dziecko)->dzieci[miejsce]->ilosc_kluczy == ((2 * porzadek) - 1))
            {
                przedziel_dziecko(dziecko, miejsce, porzadek);
                if ((*dziecko)->klucze[miejsce] > klucz)
                {
                    dodaj_do_dziecka(dziecko, miejsce, porzadek);
                }
                else
                {
                    dodaj_do_dziecka(dziecko, miejsce + 1, porzadek);
                }
            }
            dodaj_do_dziecka(&((*dziecko)->dzieci[miejsce]), klucz, porzadek);
        }
    }
}

void dodaj_klucz(Wezel** korzen, int klucz, int porzadek)
{
    if ((*korzen)->ilosc_kluczy == ((2 * porzadek) - 1))
    {
        Wezel* temp = (*korzen);
        Wezel* nowy_korzen = new Wezel;
        nowy_korzen->ilosc_kluczy = 1;
        nowy_korzen->klucze = new int[1];
        nowy_korzen->dzieci = new Wezel * [2];
        nowy_korzen->czy_lisc = false;
        nowy_korzen->klucze[0] = (*korzen)->klucze[porzadek - 1];
        Wezel* prawe = new Wezel;
        Wezel* lewe = new Wezel;
        dodajPoladzicekukorzenia(korzen, &lewe, porzadek);
        dodajPoladzicekukorzenia(korzen, &prawe, porzadek);
        if (!(lewe->czy_lisc))
        {
            lewe->dzieci[0] = (*korzen)->dzieci[0];
            prawe->dzieci[0] = (*korzen)->dzieci[porzadek];
        }
        for (int i = 0; i < ((2 * porzadek) - 1); i++)
        {
            if (i < (porzadek - 1))
            {
                lewe->klucze[i] = (*korzen)->klucze[i];
                if ((*korzen)->czy_lisc == false)
                {
                    lewe->dzieci[i + 1] = (*korzen)->dzieci[i + 1];
                }
            }
            if (i >= porzadek)
            {
                prawe->klucze[i - porzadek] = (*korzen)->klucze[i];
                if ((*korzen)->czy_lisc == false)
                {
                    prawe->dzieci[(i - porzadek) + 1] = (*korzen)->dzieci[i + 1];
                }
            }
        }
        nowy_korzen->dzieci[0] = lewe;
        nowy_korzen->dzieci[1] = prawe;
        (*korzen) = nowy_korzen;
        delete[] temp->dzieci;
        delete[] temp->klucze;
        delete temp;
    }
    if ((*korzen)->czy_lisc)
    {
        bool czy_wstawiono_korzen = false;
        int* pom_tab = new int[((*korzen)->ilosc_kluczy) + 1];
        for (int i = 0; i < ((*korzen)->ilosc_kluczy); i++)
        {
            if ((*korzen)->klucze[i] < klucz)
            {
                pom_tab[i] = (*korzen)->klucze[i];
            }
            else if (!czy_wstawiono_korzen)
            {
                pom_tab[i] = klucz;
                czy_wstawiono_korzen = true;
            }
            else if (czy_wstawiono_korzen)
            {
                pom_tab[i] = (*korzen)->klucze[i-1];
            }
        }
        if (!czy_wstawiono_korzen)
        {
            pom_tab[(*korzen)->ilosc_kluczy] = klucz;
        }
        else if (czy_wstawiono_korzen)
        {
            pom_tab[(*korzen)->ilosc_kluczy] = (*korzen)->klucze[(*korzen)->ilosc_kluczy - 1];
        }
        if ((*korzen)->klucze != nullptr)
        {
            delete[](*korzen)->klucze;
        }
        (*korzen)->ilosc_kluczy += 1;
        (*korzen)->klucze = new int[(*korzen)->ilosc_kluczy];
        for (int i = 0; i < (*korzen)->ilosc_kluczy; i++)
        {
            (*korzen)->klucze[i] = pom_tab[i];
        }
        delete[] pom_tab;
    }
    else if (!((*korzen)->czy_lisc))
    {
        bool czy_znaleziono_mniejsze_miejsce = false;
        for (int i = 0; i < (*korzen)->ilosc_kluczy; i++)
        {
            if (klucz < (*korzen)->klucze[i])
            {
                czy_znaleziono_mniejsze_miejsce = true;
                if ((*korzen)->dzieci[i]->ilosc_kluczy == ((2 * porzadek) - 1))
                {
                    przedziel_dziecko(korzen, i, porzadek);
                    if ((*korzen)->klucze[i] > klucz)
                    {
                        dodaj_do_dziecka(&((*korzen)->dzieci[i]), klucz, porzadek);
                    }
                    else
                    {
                        dodaj_do_dziecka(&((*korzen)->dzieci[i+1]), klucz, porzadek);
                    }
                }
                else
                {
                    dodaj_do_dziecka(&((*korzen)->dzieci[i]), klucz, porzadek);
                }
                break;
            }
        }
        if (czy_znaleziono_mniejsze_miejsce == false)
        {
            int ile_kl = (*korzen)->ilosc_kluczy;
            if ((*korzen)->dzieci[ile_kl]->ilosc_kluczy == ((2 * porzadek) - 1))
            {
                przedziel_dziecko(korzen, ile_kl, porzadek);
                if ((*korzen)->klucze[ile_kl] > klucz)
                {
                    dodaj_do_dziecka(&((*korzen)->dzieci[ile_kl]), klucz, porzadek);
                }
                else
                {
                    dodaj_do_dziecka(&((*korzen)->dzieci[ile_kl + 1]), klucz, porzadek);
                }
            }
            else
            {
                dodaj_do_dziecka(&((*korzen)->dzieci[ile_kl]), klucz, porzadek);
            }
        }
    }
}

bool szukaj(Wezel* wezel, int klucz)
{
    if (wezel->czy_lisc)
    {
        for (int i = 0; i < wezel->ilosc_kluczy; i++)
        {
            if (wezel->klucze[i] == klucz)
            {
                return true;
            }
            else if (wezel->klucze[i] > klucz)
            {
                return false;
            }
        }
        if (true)
        {
            return false;
        }
    }
    else
    {
        for (int i = 0; i < wezel->ilosc_kluczy; i++)
        {
            if (wezel->klucze[i] == klucz)
            {
                return true;
            }
            else if (wezel->klucze[i] > klucz)
            {
                return szukaj(wezel->dzieci[i], klucz);
            }
        }
        if(true)
        {
            return szukaj(wezel->dzieci[wezel->ilosc_kluczy], klucz);
        }
    }
}

int main()
{
    char operacja;
    int porzadek;
    int klucz;
    Wezel* korzen = nullptr;
    while (scanf(" %c", &operacja) > 0)
    {
        if (operacja == 'I')
        {
            if (scanf(" %d", &porzadek))
            {
                stworz_B_drzewo(&korzen);
            }
        }
        if (operacja == 'A')
        {
            if (scanf(" %d", &klucz))
            {
                dodaj_klucz(&korzen, klucz, porzadek);
            }
        }
        if (operacja == '\?')
        {
            if (scanf(" %d", &klucz))
            {
                bool czy_znaleziono = szukaj(korzen, klucz);
                printf("%d ", klucz);
                if (czy_znaleziono)
                {
                    printf("+\n");
                }
                else
                {
                    printf("-\n");
                }
            }
        }
    }
}
