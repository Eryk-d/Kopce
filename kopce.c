#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void KOPIEC_WYSWIETL(int* A, int heap_size);
int PARENT(int i);
int LEFT(int i);
int RIGHT(int i);
void KOPIEC_PRZYWR(int* A, int head_size, int i);
void KOPIEC_BUDUJ(int* A, int n, int* heap_size);
int KOPIEC_USUN_MAX(int* A, int* heap_size);
int* KOPIEC_WSTAW(int* A, int* heap_size, int key);
void KOPIEC_SORTUJ(int* A, int n);

int main()
{
    int d = 0;
    char z;
    int* tab;
    int rozmiar_kopca = 10;
    tab = malloc(rozmiar_kopca * sizeof(*tab));
    int wynik;
    int* wynik_ptr;

    *tab = 16;
    *(tab + 1) = 14;
    *(tab + 2) = 10;
    *(tab + 3) = 8;
    *(tab + 4) = 7;
    *(tab + 5) = 9;
    *(tab + 6) = 3;
    *(tab + 7) = 2;
    *(tab + 8) = 4;
    *(tab + 9) = 1;

    while (1)
    {
        system("CLS");
        printf("Co chcesz zrobic?\n");
        printf("w - wyswietl wartosci z kopca\n");
        printf("p - wyswietl indeks rodzica dla podanego indeksu\n");
        printf("r - wyswietl indeks prawego syna dla podanego indeksu\n");
        printf("l - wyswietl indeks lewego syna dla podanego indeksu\n");
        printf("k - przywroc kopiec\n");
        printf("b - buduj kopiec\n");
        printf("u - usun maksymalna wartosc w kopcu\n");
        printf("d - dodaj wartosc do kopca\n");
        printf("s - sortuj kopiec\n");
        printf("q - Koniec\n");
        fflush(stdin);
        z = getchar();

        switch (z)
        {
        case 'w': printf("Wartosci w kopcu\n");
            KOPIEC_WYSWIETL(tab, rozmiar_kopca);
             break;
        case 'p': printf("podaj indeks\n");
            scanf("%d", &d);
            wynik = PARENT(d);
            if (wynik) printf("rodzic ma indeks %d\n", wynik);
            else printf("dla podanego indeksu nie istnieje rodzic\n");
            system("pause");
            break;
        case 'l': printf("podaj indeks\n");
            scanf("%d", &d);
            wynik = LEFT(d);
            if (wynik) printf("lewy syn ma indeks %d\n", wynik);
            else printf("dla podanego indeksu nie istnieje lewy syn\n");
            system("pause");
            break;
        case 'r': printf("podaj indeks\n");
            scanf("%d", &d);
            wynik = RIGHT(d);
            if (wynik) printf("prawy syn ma indeks %d\n", wynik);
            else printf("dla podanego indeksu nie istnieje prawy syn\n");
            system("pause");
            break;
        case 'k': printf("podaj indeks\n");
            scanf("%d", &d);
            KOPIEC_PRZYWR(tab, rozmiar_kopca, d);
            printf("kopiec zostal przywrocony\n");
            system("pause");
            break;
        case 'b': KOPIEC_BUDUJ(tab, rozmiar_kopca, &rozmiar_kopca);
            printf("zbudowano kopiec\n");
            system("pause");
            break;
        case 'u': wynik = KOPIEC_USUN_MAX(tab, &rozmiar_kopca);
            printf("usunieto element o wartosci %d\nkopiec po usunieciu najwiekszej wartosci:\n", wynik);
            KOPIEC_WYSWIETL(tab, rozmiar_kopca);
            system("pause");
            break;
        case 'd': printf("podaj wartosc do wstawienia\n");
            scanf("%d", &d);
            wynik_ptr = KOPIEC_WSTAW(tab, &rozmiar_kopca, d);
            printf("wartosc zostala wstawiona do kopca\n");
            printf("wskaznik do powiekszonego kopca %d\n", wynik_ptr);
            system("pause");
            break;
        case 's': KOPIEC_SORTUJ(tab, rozmiar_kopca);
            printf("Posortowano kopiec\n");
            for (int i = 1; i <= rozmiar_kopca; i++)
            {
                printf("indeks %d --- wartosc: %d\n", i-1 , *(tab + i-1));
            }
            system("pause");
            break;
        case 'q': free(tab);
            printf("zwolniono cala pamiec kopca\n");
            return 0;
        }
    }
}

void KOPIEC_WYSWIETL(int* A, int heap_size)
{
    int x = 1;
    for( int i = 0; i < heap_size ; i++)
    {
        if (x == 1 || x == 2 || x == 4 || x == 8 || x == 16) printf("\n");
        printf("  %d  ", *(A + i));
        x++;
    }
    printf("\n");
    system("pause");
}

int PARENT(int i)
{
    int w = i / 2;
    if (w > 10) return(NULL);
    else return (w);
}

int LEFT(int i)
{
    int w = (2 * i);
    if (w > 10) return(NULL);
    else return (w);

}

int RIGHT(int i)
{
    int w = 2 * i + 1;
    if (w > 10) return(NULL);
    else return (w);
}

void KOPIEC_PRZYWR(int* A, int head_size, int i)
{
    int naj = 0;
    int x = 0;
    int l = LEFT(i);
    int r = RIGHT(i);
    if ((l <= head_size) && (*(A+l-1) > *(A+i-1))) naj = l;
    else naj = i;
    if ((r <= head_size) && (*(A+r-1) > *(A+naj-1))) naj = r;
    if (naj != i)
    {
        x = *(A+i-1);
        *(A+i-1) = *(A+naj-1);
        *(A+naj-1) = x;
        KOPIEC_PRZYWR(A, head_size, naj);
    }
}

void KOPIEC_BUDUJ(int* A, int n, int* heap_size)
{
    *heap_size = n;
    for (int i = n / 2; i >= 1; i--) KOPIEC_PRZYWR(A, n, i);
}

int KOPIEC_USUN_MAX(int* A, int* heap_size)
{
    int max = 0;
    int ptr = *heap_size;
    if (heap_size < 1) printf("kopiec pusty");
    max = *A;
    *A = *(A + ptr - 1);
    *heap_size = --ptr;
    A = realloc(A, *heap_size * sizeof(*A));
    KOPIEC_PRZYWR(A,heap_size, 1);
    return(max);
}

int* KOPIEC_WSTAW(int* A, int* heap_size, int key)
{
    int i = 0;
    int w = 0;
    int x = 0;
    *heap_size = *heap_size + 1;
    i = *heap_size;
    A = realloc(A, i * sizeof(*A));
    x = PARENT(i);
    while ((i>1) && (*(A + x) < key)) 
    {
        *(A + i) = *(A + x);
        i = x;
        x = PARENT(i);
    }
    i--;
    *(A + i) = key;
    return (A);
}

void KOPIEC_SORTUJ(int* A, int n)
{
    int x = 0;
    KOPIEC_BUDUJ(A , n, &n);
    for (int i = n-1; i >= 1; i--)
    {
        x = *(A + i);
        *(A + i) = *A;
        *A = x;
        n--;
        KOPIEC_PRZYWR(A, n, 1);
    }
}
