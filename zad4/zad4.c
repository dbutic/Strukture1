/*Napisati program za zbrajanje i množenje polinoma.Koeficijenti i eksponenti se
èitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE (1024)

typedef struct Poly {
    int coeff;
    int exp;
    struct Poly* next;
} Poly;

typedef Poly* Position;

Position createTerm(int coeff, int exp);
int insertSorted(Position head, Position nE);
int loadPolyFromFile(Position p1, Position p2);
void insertAfter(Position position, Position nE);
void deleteAfter(Position position);
int parseStringIntoList(Position p, char buffer[MAX_LINE]);
int addPoly(Position p1, Position p2, Position result);
int multiplyPoly(Position result, Position p1, Position p2);
int printPoly(Position head);

int main() {
    Poly p1 = { 0, 0, NULL }, p2 = { 0, 0, NULL }, sum = { 0, 0, NULL }, product = { 0, 0, NULL };
    if (loadPolyFromFile(&p1, &p2) == EXIT_SUCCESS) {
        printf("Prvi polinom: ");
        printPoly(p1.next);
        printf("Drugi polinom: ");
        printPoly(p2.next);
    }
    addPoly(p1.next, p2.next, &sum);
    printf("Suma polinoma: ");
    printPoly(sum.next);
    multiplyPoly(&product, p1.next, p2.next);
    printf("Umnozak polinoma: ");
    printPoly(product.next);
    return EXIT_SUCCESS;
}

Position createTerm(int coeff, int exp) {
    Position newT = (Position)malloc(sizeof(Poly));
    if (!newT) {
        printf("Greska pri alokaciji\n");
        return NULL;
    }
    newT->coeff = coeff;
    newT->exp = exp;
    newT->next = NULL;
    return newT;
}

int insertSorted(Position head, Position nE) {
    Position temp = head;
    while (temp->next && temp->next->exp < nE->exp) {
        temp = temp->next;
    }
    if (temp->next == NULL || temp->next->exp != nE->exp) {
        insertAfter(temp, nE);
    }
    else {
        int resultCoeff = temp->next->coeff + nE->coeff;
        if (resultCoeff == 0) {
            deleteAfter(temp);
            free(nE);
        }
        else {
            temp->next->coeff = resultCoeff;
            free(nE);
        }
    }
    return EXIT_SUCCESS;
}

int loadPolyFromFile(Position p1, Position p2) {
    FILE* file = fopen("polinomi.txt", "r");
    char buffer[MAX_LINE] = { 0 };
    int status = EXIT_SUCCESS;
    if (!file) {
        printf("Greska pri otvaranju datoteke\n");
        return EXIT_FAILURE;
    }

    fgets(buffer, MAX_LINE, file);
    status = parseStringIntoList(p1, buffer);
    if (status != EXIT_SUCCESS) {
        fclose(file);
        return EXIT_FAILURE;
    }

    fgets(buffer, MAX_LINE, file);
    status = parseStringIntoList(p2, buffer);
    if (status != EXIT_SUCCESS) {
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);
    return EXIT_SUCCESS;
}

void insertAfter(Position position, Position nE) {
    nE->next = position->next;
    position->next = nE;
}

void deleteAfter(Position position) {
    Position temp = position->next;
    if (temp != NULL) {
        position->next = temp->next;
        free(temp);
    }
}

int parseStringIntoList(Position p, char buffer[MAX_LINE]) {
    int coeff = 0, exp = 0, numBytes = 0;
    int status = EXIT_SUCCESS;
    Position nE = NULL;

    char* current = buffer;
    while (sscanf(current, " %dx^%d %n", &coeff, &exp, &numBytes) == 2) {
        nE = createTerm(coeff, exp);
        if (!nE)
            return EXIT_FAILURE;
        insertSorted(p, nE);
        current += numBytes;
    }

    return EXIT_SUCCESS;
}

int addPoly(Position p1, Position p2, Position result) {
    Position temp1 = p1;
    Position temp2 = p2;
    Position nE = NULL;
    int coeff = 0, exp = 0;

    while (temp1 != NULL) {
        nE = createTerm(temp1->coeff, temp1->exp);
        insertSorted(result, nE);
        temp1 = temp1->next;
    }

    while (temp2 != NULL) {
        nE = createTerm(temp2->coeff, temp2->exp);
        insertSorted(result, nE);
        temp2 = temp2->next;
    }
    return EXIT_SUCCESS;
}

int multiplyPoly(Position result, Position p1, Position p2) {
    Position temp1 = p1;
    Position temp2 = p2;
    Position nE = NULL;
    int newCoeff = 0, newExp = 0;
    while (temp1) {
        temp2 = p2;
        while (temp2) {
            newCoeff = temp1->coeff * temp2->coeff;
            newExp = temp1->exp + temp2->exp;
            nE = createTerm(newCoeff, newExp);
            insertSorted(result, nE);
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return EXIT_SUCCESS;
}

int printPoly(Position p) {
    printf("\n");

    while (p != NULL) {
        if (p->coeff > 0)
            printf(" %dx^%d", p->coeff, p->exp);
        else
            printf(" %dx^%d", p->coeff, p->exp);
        p = p->next;
    }

    printf("\n");
    return EXIT_SUCCESS;
}
