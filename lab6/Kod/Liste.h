#ifndef LISTE_H
#define LISTE_H

#include "SvePotrebno.h"

struct Racun;
typedef struct Racun *RacunPos;
typedef struct Racun{
    char Artikl[MAX_NUM_OF_CHAR];
    int Kolicina;
    float Cijena;
    RacunPos next;
}racun;

struct ListarRacuna;
typedef struct ListaRacuna *RacuniPos;
typedef struct ListaRacuna {
    char Racun_ID[MAX_NUM_OF_CHAR];
    int Godina;
    int Mjesec;
    int Dan;
    RacunPos Sadrzaj;
    RacuniPos next;
}racuni;

int readFromFile(RacuniPos, char*);
int readBillContent(RacuniPos, char*);
int printWithRecursionBillContent(RacunPos);
int printWithRecursionDateAndName(RacuniPos);
int freeMemoryWithRecursion(RacuniPos);
int freeContent(RacunPos);
int comparison(RacuniPos, RacuniPos);
int moneySpent(RacuniPos, char*, int, int, int, int, int, int);
RacunPos sortArticles(RacuniPos);

#endif