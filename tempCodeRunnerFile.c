#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX (50)
#define ERROR (-1)
typedef struct _osoba* head;
typedef struct _osoba {
    char ime[MAX];
    char prezime[MAX];
    int godina;
    head next;
}osoba;
int Ispis(head h);
int UnosP(head h);
int UnosK(head h);
int Trazi(head h);
int Brisi(head h);
int main() {
    osoba HEAD;
    HEAD.next = NULL;
    int izbor1 = 0, izbor2 = 0;
    do {
        printf("Zelite li raditi nesto sa listom ? ");
        printf("\nUnesite broj 1 za odgovor DA");
        printf("\nUnesite broj 2 za odgovor NE\n");
        printf("\nUnesite broj: ");
        scanf("%d", &izbor1);
        if (izbor1 == 1) {
            printf("\nIzaberite sto zelite napraviti:\n");
            printf("Unesite broj 1 za dodavanje osobe na pocetak liste\n");
            printf("Unesite broj 2 za dodavanje osobe na kraj liste\n");
            printf("Unesite broj 3 za trazenje osobe u listi(po prezimenu)\n");
            printf("Unesite broj 4 za brisanje osobe iz liste\n");
            printf("Unesite broj 5 za ispis liste\n");
            printf("\nUnesite broj: ");
            scanf("%d", &izbor2);
            printf("\n");
            if (izbor2 == 1) {
                UnosP(&HEAD);
            }
            if (izbor2 == 2) {
                UnosK(&HEAD);
            }
            if (izbor2 == 3) {
                Trazi(HEAD.next);
            }
            if (izbor2 == 4) {
                Brisi(&HEAD);
            }
            if (izbor2 == 5) {
                Ispis(HEAD.next);
            }
        }
    } while (izbor1 == 1);
}
int UnosP(head h) {
    head p = NULL;
    p = (head)malloc(sizeof(osoba));
    if (p == NULL) {
        printf("\nNeuspjesna alokacija memorije!");
        return ERROR;
    }
    printf("Unesite ime osobe: ");
    scanf("%s", p->ime);
    printf("Unesite prezime osobe: ");
    scanf("%s", p->prezime);
    printf("Unesite godinu rodenja osobe: ");
    scanf("%d", &(p->godina));
    p->next = h->next;
    h->next = p;
    return 0;
}
int UnosK(head h) {
    while (h->next != NULL)
    {
        h = h->next;
    }

    head p = NULL;
    p = (head)malloc(sizeof(osoba));

    if (p == NULL)
    {
        printf("\nNeuspjesna alokacija memorije!");
        return ERROR;
    }

    printf("\nUnesite ime osobe: ");
    scanf(" %s", p->ime);
    printf("Unesite prezime osobe: ");
    scanf(" %s", p->prezime);
    printf("Unesite godinu rodenja osobe: ");
    scanf("%d", &p->godina);
    printf("\n");
    p->next = h->next;
    h->next = p;
    return 0;
}
int Trazi(head h) {
    char prez[MAX];
    printf("Unesite prezime osobe koju zelite pronaci: ");
    scanf("%s", &prez);
    printf("\n");
    while (h != NULL && strcmp(prez, h->prezime) != 0); {
        h = h->next;
    }
    if (h == NULL)
        printf("Osoba ne postoji!\n");
    else
        printf("Adresa trazene odobe je: %p", h);
    return 0;
}
int Brisi(head h) {
    head pret = NULL;
    char prez[MAX];
    printf("Unesite prezime osobe koju zelite izbrisati: ");
    scanf("%s", &prez);
    printf("\n");
    while (h->next != NULL && strcmp(prez, h->prezime) != 0)
    {
        pret = h;
        h = h->next;
    }
    if (pret != NULL && strcmp(prez, h->prezime) == 0)
    {
        h = pret->next;
        pret->next = h->next;
    }
    return 0;
}
int Ispis(head h) {
    while (h != NULL) {
        printf("%s %s %d\n", h->ime, h->prezime, h->godina);
        h = h->next;
    }
}