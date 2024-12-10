#include "Liste.h"

int readFromFile(RacuniPos p, char *fileName) {

    FILE *fp = NULL;
    char buffer[MAX_NUM_OF_CHAR] = { 0 }, BillFileName[MAX_NUM_OF_CHAR] = { 0 };
    char racuni_s[MAX_NUM_OF_CHAR] = { 0 };
    int i = 1;
    RacuniPos start = NULL, tmp = NULL, comp = NULL;

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Error occurred while opening file!\n");
        return ERROR;
    }

    start = tmp = p;

    while (1) {

        if (fgets(buffer, MAX_NUM_OF_CHAR, fp) == NULL)
            break;
        buffer[strcspn(buffer, "\n")] = 0;

        if (readBillContent(p, buffer) == ERROR) {
            free(p);
            return ERROR;
        }

        p = p->next;
        while (tmp->next != NULL) {
            if (comparison(tmp->next, p) < 0) {
                comp = p;
                p = tmp;
                tmp = comp;
            } else
                tmp = tmp->next;
        }
        tmp = start;
    }

    fclose(fp);
    return END;
}

int readBillContent(RacuniPos P, char *BillFileName) {

    FILE *fp = NULL;
    char buffer[MAX_NUM_OF_CHAR] = { 0 };
    char *p = NULL;
    int n = 0, i = 0;
    static int racun_br = 1;
    RacunPos q = NULL;
    RacuniPos q_r = NULL;
    racun Head = {.Artikl = {0}, .Kolicina = 0, .Cijena = 0.0, .next = NULL};

    fp = fopen(BillFileName, "r");
    if (fp == NULL) {
        printf("Error occurred while opening bill file!\n");
        return ERROR;
    }

    q_r = (RacuniPos)malloc(sizeof(racuni));
    fgets(buffer, MAX_NUM_OF_CHAR, fp);
    p = buffer;
    while (strlen(p) > 0) {
        if (i == 0)
            sscanf(p, "%d-%n", &q_r->Godina, &n);
        else if (i == 1)
            sscanf(p, "%d-%n", &q_r->Mjesec, &n);
        else
            sscanf(p, "%d-%n", &q_r->Dan, &n);
        i++;
        p += n;
    }
    snprintf(q_r->Racun_ID, MAX_NUM_OF_CHAR, "Racun_%d", racun_br);
    racun_br++;

    while (1) {

        if (fgets(buffer, MAX_NUM_OF_CHAR, fp) == NULL)
            break;

        q = (RacunPos)malloc(sizeof(racun));
        p = buffer;

        sscanf(p, "%s %n", q->Artikl, &n);
        p += n;
        sscanf(p, "%d %n", &q->Kolicina, &n);
        p += n;
        sscanf(p, "%f %n", &q->Cijena, &n);
        p += n;

        q->next = q_r->Sadrzaj;
        q_r->Sadrzaj = q;
    }

    q = (RacunPos)malloc(sizeof(racun));
    strcpy(q->Artikl, "\0");
    q->Cijena = 0.0;
    q->Kolicina = 0;
    q->next = NULL;

    q->next = q_r->Sadrzaj;
    q_r->Sadrzaj = q;

    q_r->Sadrzaj = sortArticles(q_r);

    q_r->next = P->next;
    P->next = q_r;

    fclose(fp);
    return END;
}

int printWithRecursionDateAndName(RacuniPos p) {

    if (p == NULL) {
        line_Print();
        return END;
    }

    line_Print();
    printf("\t%s\n", p->Racun_ID);
    printf("\t%d-%d-%d\n", p->Godina, p->Mjesec, p->Dan);
    printWithRecursionBillContent(p->Sadrzaj);
    printf("\n");
    return printWithRecursionDateAndName(p->next);

}

int printWithRecursionBillContent(RacunPos p) {

    if (p->next == NULL)
        return END;

    printf("\t%s %d %.2f €\n", p->next->Artikl, p->next->Kolicina, p->next->Cijena);
    return printWithRecursionBillContent(p->next);

}

int freeMemoryWithRecursion(RacuniPos p) {

    if (p->next == NULL)
        return END;

    RacuniPos temp = NULL;
    freeContent(p->next->Sadrzaj);
    temp = p->next;
    p->next = p->next->next;
    free(temp);
    return freeMemoryWithRecursion(p);
}

int freeContent(RacunPos p) {

    if (p->next == NULL)
        return END;

    RacunPos temp = NULL;
    temp = p->next;
    p->next = p->next->next;
    free(temp);
    return freeContent(p);
}

int comparison(RacuniPos p1, RacuniPos p2) {

    int comp = 0;
    comp = p1->Godina - p2->Godina;

    if (comp == 0) {
        comp = p1->Mjesec - p2->Mjesec;
        if (comp == 0) {
            comp = p1->Dan - p2->Dan;
        }
    }

    return comp;
}

int moneySpent(RacuniPos p, char *artikl, int year_1, int month_1, int day_1, int year_2, int month_2, int day_2) {

    if (p == NULL) {
        printf("The list doesn't exist!\n");
        return ERROR;
    }

    if (p->Godina > year_2) {
        printf("There aren't any bills in that time period!");
        return ERROR;
    }

    float total_amount_of_Money = 0.0;
    int total_amount = 0;
    RacunPos q = NULL;

    while (p != NULL) {
        q = p->Sadrzaj;
        if (p->Godina >= year_1 || p->Godina <= year_2 || p->Mjesec >= month_1 || p->Mjesec <= month_2 || p->Dan >= day_1 || p->Dan <= day_2) {
            while (p->Sadrzaj != NULL) {
                if (strcmp(p->Sadrzaj->Artikl, artikl) == 0) {
                    total_amount_of_Money += p->Sadrzaj->Cijena * p->Sadrzaj->Kolicina;
                    total_amount += p->Sadrzaj->Kolicina;
                }
                p->Sadrzaj = p->Sadrzaj->next;
            }
        }
        p->Sadrzaj = q;
        p = p->next;
    }

    if (total_amount > 0)
        printf("\nMoney spent on %s is: %.2f KN\nThe total amount of %s sold is: %d\n", artikl, total_amount_of_Money, artikl, total_amount);
    else
        printf("%s was not sold from %d-%d-%d to %d-%d-%d!\n", artikl, year_1, month_1, day_1, year_2, month_2, day_2);

    return END;
}

RacunPos sortArticles(RacuniPos P) {

    if (P == NULL) {
        printf("Can't sort list. The list is empty!\n");
        return NULL;
    }

    RacunPos curr = NULL, prev = NULL, temp = NULL, end = NULL;
    RacunPos p = NULL;
    p = P->Sadrzaj;

    while (p->next != end) {
        prev = p;
        curr = p->next;
        while (curr->next != end) {
            if (strcmp(curr->Artikl, curr->next->Artikl) > 0) {
                temp = curr->next;
                prev->next = temp;
                curr->next = temp->next;
                temp->next = curr;

                curr = temp;
            }
            prev = curr;
            curr = curr->next;
        }
        end = curr;
    }

    return p;
}
